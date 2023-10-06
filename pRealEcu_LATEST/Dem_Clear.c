#include "Std_Types.hpp"

#include "Dem_Dcm.hpp"
#include "Rte_Dem.hpp"
#include "Dem_Clear.hpp"
#include "Dem_ClientBaseHandling.hpp"
#include "Dem_ClientClearMachine.hpp"
#include "Dem_ClientRequestDispatcher.hpp"
#include "Dem_Events.hpp"
#include "Dem_EventRecheck.hpp"
#include "Dem_StorageCondition.hpp"
#include "Dem_EvMem.hpp"
#include "Dem_DTCs.hpp"
#include "Dem_DTCGroup.hpp"
#include "Dem_DTCStatusByte.hpp"
#include "Dem_Cfg.hpp"
#include "Dem_EventStatus.hpp"
#include "Dem_EvMemGen.hpp"
#include "DemAppInterfaceX.hpp"
#include "Rte_Dem.hpp"
#include "FiM.hpp"
#include "Dem_Lok_J1939Dcm.hpp"

#define DEM_START_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.hpp"
static Std_ReturnType Dem_ClearResult = DEM_CLEAR_PENDING;
#define DEM_STOP_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

static Std_ReturnType Dem_ClearDTCBody(Dem_ClientSelectionType Selection, Dem_DTCOriginType DTCOrigin)
{
#if(DEM_CFG_CLEAR_DTC_LIMITATION == DEM_CFG_CLEAR_DTC_LIMITATION_ALL_SUPPORTED_DTCS)
    Dem_DtcIdType dtcId;
    Dem_DTCGroupIdType DTCGroupId;
#endif

    Dem_ClientClearMachine.IsClearInterrupted = FALSE;
    Dem_ClientClearMachine.NumberOfEventsProcessed = 0;

   if(Dem_ClientSelectionType_isSelectionDTCGroupAll(Selection))
   {

        Dem_ClearAllDTCs(DTCOrigin, &Dem_ClientClearMachine);

        if(!Dem_ClientClearMachine.IsClearInterrupted)
        {
            Dem_EvMemGenClearDtcByOccurrenceTime(DTCOrigin);
            Dem_EvMemGenClearOverflow(DTCOrigin);
#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
            rba_DemObdBasic_Clear(DTCOrigin);
#endif
            return DEM_CLEAR_OK;
        }
        return DEM_CLEAR_PENDING;
   }

#if(DEM_CFG_CLEAR_DTC_LIMITATION == DEM_CFG_CLEAR_DTC_LIMITATION_ALL_SUPPORTED_DTCS)

   if(Dem_ClientSelectionType_isSelectionDTCGroup(Selection))
   {
        DTCGroupId = (uint8)Dem_ClientSelectionType_getSelectionDtcIndex (Selection);

        Dem_DtcsClearDtcInGroup(DTCGroupId, DTCOrigin, &Dem_ClientClearMachine);
        if(!Dem_ClientClearMachine.IsClearInterrupted)
        {
            return DEM_CLEAR_OK;
        }
        return DEM_CLEAR_PENDING;
   }
   else if(Dem_ClientSelectionType_isSelectionSingleDTC(Selection))
   {
        dtcId = Dem_ClientSelectionType_getSelectionDtcIndex (Selection);

        Dem_ClearSingleDTC(dtcId, DTCOrigin, &Dem_ClientClearMachine);

        if(!Dem_ClientClearMachine.IsClearInterrupted)
        {
            return DEM_CLEAR_OK;
        }
        return DEM_CLEAR_PENDING;
   }
   else{
        return DEM_CLEAR_WRONG_DTC;
   }

#else
    return DEM_CLEAR_FAILED;
#endif
}

void Dem_ClearMainFunction(void){
    Dem_ClientRequestType tempRequest;
    Dem_ClientIdType tempClientId;

   if(Dem_ClientClearMachine_GetMachineState() != DEM_CLEAR_DTC_MACHINE_STATE_IDLE)
   {
        tempClientId = Dem_ClientClearMachine_GetMachineActiveClient();
        tempRequest = Dem_Client_getClient(tempClientId)->request;

        if(!Dem_ClientRequestType_isCancelRequested(tempRequest))
        {
            if(Dem_ClientClearMachine_GetMachineState() == DEM_CLEAR_DTC_MACHINE_STATE_EXEC)
            {
#if(DEM_CFG_J1939DCM_CLEAR_SUPPORT != DEM_CFG_J1939DCM_OFF)
                if(tempClientId == DEM_CLIENTID_J1939)
                {
                    Dem_ClearResult = Dem_J1939DcmClearDTCBody(Dem_Client_getClient(tempClientId)->J1939DTCTypeFilter
   ,     Dem_Client_getClient(tempClientId)->J1939node);
                }
                else
#endif
                {
                    if(Dem_ClientClearMachine.IsNewClearRequest)
                    {

                        Dem_ClearDtcNotificationStartCallbacks(Dem_Client_getClient(tempClientId)->DTC
   ,     Dem_Client_getClient(tempClientId)->DTCFormat
   ,     Dem_Client_getClient(tempClientId)->DTCOrigin);
                    }

                    Dem_ClearResult = Dem_ClearDTCBody(Dem_Client_getClient(tempClientId)->selection
   ,     Dem_Client_getClient(tempClientId)->DTCOrigin);
                }

                Dem_ClientClearMachine.IsNewClearRequest = FALSE;

                if(Dem_ClearResult != DEM_CLEAR_PENDING)
                {
                    Dem_ClientClearMachine_SetClientRequest(tempClientId, DEM_CLEAR_DTC_MACHINE_STATE_WAITINGFORNVM);
                }
            }

            if(Dem_ClientClearMachine_GetMachineState() == DEM_CLEAR_DTC_MACHINE_STATE_WAITINGFORNVM)
            {

                if(((DEM_CFG_CLEAR_DTC_BEHAVIOR == DEM_CFG_CLEAR_DTC_BEHAVIOR_NONVOLATILE_FINISH)
                        && (Dem_ClearResult == DEM_CLEAR_OK) && Dem_NvMIsClearPending())
#if(DEM_CFG_TRIGGERMONITORINITBEFORECLEAROK == TRUE)
                        || Dem_EvtIsAnyInitMonitoringRequestedClear()
#endif
                        )
                {

                }
                else{
                    if((DEM_CFG_CLEAR_DTC_BEHAVIOR == DEM_CFG_CLEAR_DTC_BEHAVIOR_NONVOLATILE_FINISH)
                            && (Dem_NvMIsClearFailed()))
                    {
                        Dem_ClearResult = DEM_CLEAR_MEMORY_ERROR;
                    }

                    if(!Dem_ClientClearMachine_isProcessingClient(DEM_CLIENTID_J1939))
                    {

                        Dem_ClearDtcNotificationFinishCallbacks(Dem_Client_getClient(tempClientId)->DTC
   ,     Dem_Client_getClient(tempClientId)->DTCFormat
   ,     Dem_Client_getClient(tempClientId)->DTCOrigin);
                    }
                    Dem_ClientResultType_setResult(&Dem_Client_getClient(tempClientId)->result, tempRequest
   ,     Dem_ClearResult);
                    Dem_ClientClearMachine_SetClientRequest(tempClientId, DEM_CLEAR_DTC_MACHINE_STATE_IDLE);
                }
            }
        }
        else{
            Dem_ClientResultType_confirmCancel(&Dem_Client_getClient(tempClientId)->result, tempRequest);
            Dem_ClientClearMachine_SetClientRequest(tempClientId, DEM_CLEAR_DTC_MACHINE_STATE_IDLE);
        }
   }
}

Dem_ReturnClearDTCType Dem_DcmCheckClearParameter (uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin)
{
    Dem_DtcIdType dtcId;
    Dem_DTCGroupIdType DTCGroupId;

   if(!Dem_EvMemIsDtcOriginValid(&DTCOrigin))
   {
        return DEM_CLEAR_WRONG_DTCORIGIN;
   }

   if(   (DTCFormat != DEM_DTC_FORMAT_UDS)

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
         && (DTCFormat != DEM_DTC_FORMAT_OBD)
#endif

        )
   {
        return DEM_CLEAR_WRONG_DTC;
   }

   if(DTC == DEM_DTC_GROUP_ALL_DTCS)
   {
        return DEM_CLEAR_OK;
   }
   else{

        if( Dem_LibGetParamUI8(DEM_CFG_CLEAR_DTC_LIMITATION) == Dem_LibGetParamUI8(DEM_CFG_CLEAR_DTC_LIMITATION_ONLY_CLEAR_ALL_DTCS) )
        {
            DEM_DET(DEM_DET_APIID_CLEARDTC, DEM_E_WRONG_CONFIGURATION);
            return DEM_CLEAR_WRONG_DTC;
        }
        else{
            DTCGroupId = Dem_DtcGroupIdFromDtcGroupCode(DTC);
            if(DTCGroupId != DEM_DTCGROUPID_INVALID)
            {
                return DEM_CLEAR_OK;
            }
            else{
                dtcId = Dem_DtcIdFromDtcCode(DTC);
                if((!Dem_DtcIsSupported(dtcId)) || (DTCFormat == DEM_DTC_FORMAT_OBD))
                {

                    return DEM_CLEAR_WRONG_DTC;
                }
                return DEM_CLEAR_OK;
            }
        }
   }
}

static boolean Dem_Client_AreParametersAlreadyRequested(uint8 ClientId, uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin)
{

   if(DTCOrigin == DEM_DTC_ORIGIN_USERDEFINED_MEMORY)
   {
        DTCOrigin = DEM_DTC_ORIGIN_SECONDARY_MEMORY;
   }

    return ((Dem_Clients[ClientId].DTC == DTC) && (Dem_Clients[ClientId].DTCFormat == DTCFormat) && (Dem_Clients[ClientId].DTCOrigin == DTCOrigin));
}

Dem_ReturnClearDTCType Dem_ClearDTC(uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin)
{
    Dem_ReturnClearDTCType returnSts = E_OK;
   uint8 ClientId = DEM_CLIENTID_DCM;

   DEM_ENTRY_CONDITION_CHECK_DEM_INITIALIZED(DEM_DET_APIID_CLEARDTC,DEM_CLEAR_FAILED);

   if(!Dem_Client_AreParametersAlreadyRequested(ClientId, DTC, DTCFormat, DTCOrigin))
   {

        returnSts = (Dem_ReturnClearDTCType) Dem_SelectDTC(ClientId, DTC, DTCFormat, DTCOrigin);
   }

   if(returnSts == E_OK)
   {

        returnSts = (Dem_ReturnClearDTCType)Dem_ClearDTC_4_3(ClientId);
   }

    return returnSts;
}

static void Dem_InvalidateSelectDTCParams(void){
    Dem_ClientIdType clientId;
   for(clientId = 1; clientId < DEM_CLIENTID_ARRAYLENGTH; clientId++)
   {
        (void) Dem_SelectDTC(clientId, DEM_INVALID_DTC, DEM_INVALID_DTC_FORMAT, DEM_INVALID_DTC_ORIGIN_MEMORY);
   }
}

void Dem_ClearDtcInit(void){
    Dem_InvalidateSelectDTCParams();
    Dem_ClientSelectionType_invalidateSelectionResult(&Dem_Client_getClient(DEM_CLIENTID_DCM)->selection);
}

boolean Dem_ClearIsInProgress (void){
    return (Dem_ClientClearMachine.machine_state == DEM_CLEAR_DTC_MACHINE_STATE_EXEC);
}

void Dem_DcmCancelOperation (void){
    Dem_InvalidateSelectDTCParams();
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

