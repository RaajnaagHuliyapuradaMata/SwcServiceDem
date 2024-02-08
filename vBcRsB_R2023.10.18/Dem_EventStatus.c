#include "Std_Types.hpp"

#include "Dem.hpp"
#include "Rte_Dem.hpp"
#include "Dem_EventStatus.hpp"
#include "Dem_Events.hpp"
#include "Dem_Cfg_Main.hpp"
#include "Dem_Dependencies.hpp"
#include "Dem_Nvm.hpp"

#if(DEM_CFG_TRIGGERFIMREPORTS == DEM_CFG_TRIGGERFIMREPORTS_ON)
#include "FiM.hpp"
#endif

#include "Dem_Lok_CallEvtStChngdCbk.hpp"
#include "Dem_Cfg.hpp"

#define DEM_START_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.hpp"
DEM_ARRAY_DEFINE(      uint8, Dem_AllEventsStatusByte, DEM_EVENTID_ARRAYLENGTH);
#define DEM_STOP_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

#if DEM_CFG_CUSTOMIZABLEDTCSTATUSBYTE
DEM_ARRAY_DEFINE(      uint8, Dem_AllEventsStatusByteCust, DEM_EVENTID_ARRAYLENGTH);
#endif

#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

void Dem_EventStatusInitCheckNvM(void){
    Dem_NvmResultType NvmResult;

   if(Dem_NvMIsInvalidateAllNVMBlocksRequested())
   {

        DEM_MEMSET( &Dem_AllEventsStatusByte, (sint32)DEM_ISO14229BYTE_INITVALUE, DEM_SIZEOF_VAR(Dem_AllEventsStatusByte));
        Dem_NvMClearBlockByInvalidate(DEM_NVM_ID_EVT_STATUSBYTE);
   }
   else{

        NvmResult = Dem_NvmGetStatus (DEM_NVM_ID_EVT_STATUSBYTE);

        if(NvmResult != DEM_NVM_SUCCESS)
        {

            DEM_MEMSET( &Dem_AllEventsStatusByte, (sint32)DEM_ISO14229BYTE_INITVALUE, DEM_SIZEOF_VAR(Dem_AllEventsStatusByte));

            //Set the Dirty flag
            Dem_NvMWriteBlockImmediate(DEM_NVM_ID_EVT_STATUSBYTE);
        }
   }
}

Std_ReturnType Dem_GetEventStatus(Dem_EventIdType EventId
   ,     Dem_UdsStatusByteType* EventStatusExtended)
{
    DEM_ENTRY_CONDITION_CHECK_DEMINIT_OR_FIM_IS_IN_INIT_OR_OPMO_ALLFAILUREINFOLOCKED_EVTIDVALID_EVTAVAILABLE(EventId, DEM_DET_APIID_DEM_GETEVENTSTATUS , E_NOT_OK);
   DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(EventStatusExtended,DEM_DET_APIID_DEM_GETEVENTSTATUS,E_NOT_OK);

    *EventStatusExtended = Dem_EvtGetIsoByte(EventId);
    return E_OK;
}

Std_ReturnType Dem_GetEventStatus_GeneralEvtInfo(Dem_EventIdType EventId
   ,     Dem_UdsStatusByteType* EventStatusExtended)
{
    return Dem_GetEventStatus(EventId, EventStatusExtended);
}

Dem_EventStatusType Dem_EvtGetLastReportedEventStatus (Dem_EventIdType EventId)
{
    return Dem_EvtGetLastReportedEvent(EventId);
}

void Dem_ClearEvent(Dem_EventIdType eventId, boolean ClearFully)
{
    Dem_UdsStatusByteType statusOld, statusNew;
    Dem_UdsStatusByteType dtcStByteOld;

   statusOld = DEM_ISO14229BYTE_INITVALUE;
   statusNew = DEM_ISO14229BYTE_INITVALUE;
    dtcStByteOld = DEM_ISO14229BYTE_INITVALUE;

   if(!Dem_EvtIsSuppressed(eventId))
   {
        DEM_ENTERLOCK_MON();
        Dem_StatusChange_GetOldStatus(eventId, &statusOld, &dtcStByteOld);
        if(ClearFully)
        {
            Dem_EvtSt_HandleClear(eventId);

            statusNew = Dem_EvtGetIsoByte(eventId);

            Dem_EvtSetCausal(eventId, FALSE);
            Dem_EvtSetInitMonitoring(eventId, DEM_INIT_MONITOR_CLEAR);
            Dem_EvtSetLastReportedEvent(eventId, DEM_EVENT_STATUS_INVALIDREPORT);
            Dem_EvtRequestResetFailureFilter(eventId, TRUE);

#if(DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)
               Dem_EvtSetFDCThresholdReachedTOC(eventId,FALSE);
#endif
#if(DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED)
               Dem_EvtSetFDCThresholdReached(eventId,FALSE);
#endif

            if(statusNew != statusOld)
            {
                Dem_ClearIndicatorAttributes(eventId,statusOld,statusNew);
                Dem_NodeSetRecheckOnClear(Dem_NodeIdFromEventId(eventId), TRUE);
            }
        }
        else{
            Dem_EvtSt_HandleClear_OnlyThisCycleAndReadiness(eventId);
            statusNew = Dem_EvtGetIsoByte(eventId);
        }
        DEM_EXITLOCK_MON();
        Dem_TriggerOn_EventStatusChange(eventId,statusOld,statusNew,dtcStByteOld);
   }
}

void Dem_EvtAdvanceOperationCycle(Dem_OperationCycleList operationCycleList)
{
    Dem_EventIdIterator eventIt;
    Dem_EventIdType eventId;
    Dem_UdsStatusByteType statusNew,statusOld;
    Dem_UdsStatusByteType dtcStByteOld;
    Dem_EventIdType CBeventId[DEM_CFG_ADVANCEOPERATIONCYCLE_EVENTSPERLOCK] = {0};
    Dem_UdsStatusByteType CBStatusOld[DEM_CFG_ADVANCEOPERATIONCYCLE_EVENTSPERLOCK] = {0};
    Dem_UdsStatusByteType CBStatusNew[DEM_CFG_ADVANCEOPERATIONCYCLE_EVENTSPERLOCK] = {0};
    Dem_UdsStatusByteType CBdtcStByteOld[DEM_CFG_ADVANCEOPERATIONCYCLE_EVENTSPERLOCK] = {0};
   uint32 CBindex=0;
   uint32 i;
   uint32 eventsProcessed = 0;

    DEM_ENTERLOCK_MON();
   for(Dem_EventIdIteratorNew(&eventIt); Dem_EventIdIteratorIsValid(&eventIt); Dem_EventIdIteratorNext(&eventIt))
   {
        eventsProcessed++;
        eventId = Dem_EventIdIteratorCurrent(&eventIt);
        if(Dem_isEventAffectedByOperationCycleList(eventId, operationCycleList))
        {

            Dem_StatusChange_GetOldStatus(eventId, &statusOld, &dtcStByteOld);
            Dem_EvtSt_HandleNewOperationCycle(eventId);

            Dem_SetIndicatorDeActivation_OnOperationCycleChange(eventId, statusOld, Dem_EvtGetIsoByte(eventId));

            statusNew = Dem_EvtGetIsoByte(eventId);

            //Reset FDC-Threshold_reached-flag whenever the operation cycle starts/restarts
#if(DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)
            Dem_EvtSetFDCThresholdReachedTOC(eventId,FALSE);
#endif
            Dem_EvtSetInitMonitoring(eventId, DEM_INIT_MONITOR_RESTART);
            Dem_EvtRequestResetFailureFilter(eventId, TRUE);
            Dem_EvtSetLastReportedEvent(eventId,DEM_EVENT_STATUS_INVALIDREPORT);

            CBeventId[CBindex]=eventId;
            CBStatusOld[CBindex]=statusOld;
            CBStatusNew[CBindex]=statusNew;
            CBdtcStByteOld[CBindex]=dtcStByteOld;
            CBindex++;

        }

        if(Dem_isEventAffectedByFailureCycleList(eventId, operationCycleList))
        {
            Dem_EvtSt_HandleNewFailureCycle(eventId);
        }

        if(eventsProcessed >= DEM_CFG_ADVANCEOPERATIONCYCLE_EVENTSPERLOCK)
        {
            eventsProcessed=0;
            DEM_EXITLOCK_MON();
            for(i=0; i<CBindex; i++)
            {
                Dem_TriggerOn_EventStatusChange(CBeventId[i],CBStatusOld[i],CBStatusNew[i],CBdtcStByteOld[i]);
            }
            CBindex=0;
            DEM_ENTERLOCK_MON();
        }
   }
    DEM_EXITLOCK_MON();
   for(i=0; i<CBindex; i++)
   {
        Dem_TriggerOn_EventStatusChange(CBeventId[i],CBStatusOld[i],CBStatusNew[i],CBdtcStByteOld[i]);
   }
}

Std_ReturnType Dem_OverwriteWIRStatus( Dem_EventIdType EventId, boolean WIRStatus )
{
    Std_ReturnType ret_val = E_NOT_OK;

   if( Dem_isEventIdValid(EventId) )
   {
        DEM_ENTERLOCK_MON();

        if(WIRStatus)
        {
            Dem_EvtSt_HandleIndicatorOn(EventId);
        }
        else{
            Dem_EvtSt_HandleIndicatorOff(EventId);
        }

        DEM_EXITLOCK_MON();
        ret_val = E_OK;
   }

    return ret_val;
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
