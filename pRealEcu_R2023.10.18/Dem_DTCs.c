#include "Std_Types.hpp"

#include "Dem.hpp"
#include "Dem_Dcm.hpp"
#include "Rte_Dem.hpp"
#include "Dem_DTCs.hpp"
#include "Dem_Deb.hpp"
#include "Dem_Events.hpp"
#include "Dem_EventStatus.hpp"
#include "Dem_Nvm.hpp"
#include "Dem_Mapping.hpp"
#include "Dem_Cfg.hpp"
#include "Dem_DTCGroup.hpp"
#include "Dem_Lok_J1939Dcm.hpp"
#include "DemAppInterfaceX.hpp"
#include "Rte_Dem.hpp"
#include "FiM.hpp"

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"
    DEM_ARRAY_DEFINE(Dem_DtcState, Dem_AllDTCsState, DEM_DTCID_ARRAYLENGTH);
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.hpp"

#if(DEM_CFG_ALTERNATIVEDTC == DEM_CFG_ALTERNATIVEDTC_ON)
   boolean Dem_AlternativeDTCEnabled = FALSE;
#endif

#define DEM_STOP_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

#if(DEM_CFG_ALTERNATIVEDTC == DEM_CFG_ALTERNATIVEDTC_ON)
 DEM_ARRAY_DEFINE_CONST(Dem_DtcAltParam, Dem_AllAlternativeDTCsParam, DEM_ALTERNATIVE_DTCCODE_ARRAYLENGTH, DEM_CFG_ALTERNATIVE_DTCPARAMS);
#endif

#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#if(DEM_CFG_ALTERNATIVEDTC == DEM_CFG_ALTERNATIVEDTC_ON)
void Dem_SwitchToAlternativeDtc(void){
   Dem_AlternativeDTCEnabled = TRUE;
}
#endif

Dem_boolean_least Dem_IsEventEnabledByDtcSetting(Dem_EventIdType EventId)
{
   if(Dem_EventIdIsDtcAssigned(EventId))
   {
        if(!Dem_DtcIsDTCSettingEnabled(Dem_DtcIdFromEventId(EventId)))
        {
#if(DEM_DTC_DTCSETTING_CALLBACK_SUPPORTED == DEM_DTC_DTCSETTING_CALLBACK_SUPPORTED_ON)
            //invoke the global config callback to get the DTC Disable status
            if(DEM_DTC_CALLBACK_FUNCTION_DISABLE_DTCSETTING_ALLOWED(EventId))
#endif
            {
                return FALSE;
            }
        }
   }
    return TRUE;
}

Dem_DtcIdType Dem_DtcIdFromDtcCode (Dem_DtcCodeType dtcCode)
{
   Dem_DtcIdIterator dtcId;

   for(Dem_DtcIdIteratorNew(&dtcId);
   		Dem_DtcIdIteratorIsValid(&dtcId);
   		Dem_DtcIdIteratorNext(&dtcId))
   {
   	if(Dem_GetDtcCode(Dem_DtcIdIteratorCurrent(&dtcId)) == dtcCode)
   	{
   		return Dem_DtcIdIteratorCurrent(&dtcId);
   	}
   }
   return DEM_DTCID_INVALID;
}

Std_ReturnType Dem_GetDTCOfEvent(Dem_EventIdType EventId, Dem_DTCFormatType DTCFormat, uint32* DTCOfEvent)
{
   Dem_DtcIdType dtcId;

   DEM_ENTRY_CONDITION_CHECK_EVENT_ID_VALID_AVAILABLE(EventId,DEM_DET_APIID_DEM_GETDTCOFEVENT,E_NOT_OK);
   DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(DTCOfEvent,DEM_DET_APIID_DEM_GETDTCOFEVENT,E_NOT_OK);

   if(!Dem_EventIdIsDtcAssigned(EventId))
   {
      return DEM_E_NO_DTC_AVAILABLE;
   }

   dtcId = Dem_DtcIdFromEventId(EventId);

   if(DTCFormat == DEM_DTC_FORMAT_UDS)
   {
       *DTCOfEvent = Dem_GetDtcCode(dtcId);
       return E_OK;
   }
   else if(DTCFormat == DEM_DTC_FORMAT_OBD)
   {

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
       *DTCOfEvent = rba_DemObdBasic_Dtc_GetCode(dtcId);
       return E_OK;
#else

       return E_NOT_OK;

#endif

   }
   else if(DTCFormat == DEM_DTC_FORMAT_J1939)
   {

#if(DEM_CFG_J1939DCM != DEM_CFG_J1939DCM_OFF)
       *DTCOfEvent = Dem_J1939DtcGetCode(dtcId);
       return E_OK;
#else

       return E_NOT_OK;

#endif

   }
   else{
       DEM_ASSERT_ISNOTLOCKED(); //To ensure that early return does not exit from within lock
       DEM_DET(DEM_DET_APIID_DEM_GETDTCOFEVENT,DEM_E_WRONG_CONFIGURATION);
       return E_NOT_OK;
   }
}

Std_ReturnType Dem_GetDTCOfEvent_GeneralEvtInfo(Dem_EventIdType EventId, Dem_DTCFormatType DTCFormat, uint32* DTCOfEvent)
{
    return Dem_GetDTCOfEvent(EventId, DTCFormat, DTCOfEvent);
}

Dem_DTCTranslationFormatType Dem_GetTranslationType(void){
   return DEM_CFG_DTC_TRANSLATION_TYPE;
}

Std_ReturnType Dem_GetDTCStatusAvailabilityMask(uint8* DTCStatusMask)
{
   *DTCStatusMask = DEM_CFG_DTCSTATUS_AVAILABILITYMASK;
   return E_OK;
}

Dem_ReturnGetSeverityOfDTCType Dem_GetSeverityOfDTC(uint32 DTC, Dem_DTCSeverityType* DTCSeverity)
{
   Dem_DtcIdType dtcId = Dem_DtcIdFromDtcCode(DTC);

   if(!Dem_DtcIsSupported(dtcId))
   {
      return DEM_GET_SEVERITYOFDTC_WRONG_DTC;
   }

   *DTCSeverity = Dem_Cfg_Dtc_GetSeverity(dtcId);
   return DEM_GET_SEVERITYOFDTC_OK;
}

Dem_ReturnGetFunctionalUnitOfDTCType Dem_GetFunctionalUnitOfDTC (uint32 DTC, uint8* DTCFunctionalUnit)
{
   Dem_DtcIdType dtcId = Dem_DtcIdFromDtcCode(DTC);

   if(!Dem_DtcIsSupported(dtcId))
   {
      return DEM_GET_FUNCTIONALUNITOFDTC_WRONG_DTC;
   }

   *DTCFunctionalUnit = Dem_Cfg_Dtc_GetFunc_Unit(dtcId);
   return DEM_GET_FUNCTIONALUNITOFDTC_OK;
}

Std_ReturnType Dem_SetDTCSuppression (uint32 DTC, Dem_DTCFormatType DTCFormat, boolean SuppressionStatus)
{
#if((DEM_CFG_SUPPRESSION == DEM_DTC_SUPPRESSION) || (DEM_CFG_SUPPRESSION == DEM_EVENT_AND_DTC_SUPPRESSION))

   Dem_DtcIdType dtcId = Dem_DtcIdFromDtcCode(DTC);

    DEM_ENTRY_CONDITION_CHECK_DEM_PREINITIALIZED(DEM_DET_APIID_DEM_SETDTCSUPPRESSION,E_NOT_OK);

   if(DTCFormat == DEM_DTC_FORMAT_UDS)
   {
      dtcId = Dem_DtcIdFromDtcCode(DTC);
   }
   else{

     	DEM_ASSERT_ISNOTLOCKED();	//to ensure that early return does not exit from within lock
     	//DET reported incase DTC FOrmat is neither OBD nor UDS
       DEM_DET(DEM_DET_APIID_DEM_SETDTCSUPPRESSION,DEM_E_WRONG_CONFIGURATION);
     return E_NOT_OK;
   }

   if((!Dem_isDtcIdValid(dtcId)) || (Dem_IsEventMemoryEntryExistForDTC(dtcId)))
   {
       DEM_ASSERT_ISNOTLOCKED();   //to ensure that early return does not exit from within lock
       DEM_DET(DEM_DET_APIID_DEM_SETDTCSUPPRESSION,DEM_E_WRONG_CONFIGURATION);
   	return E_NOT_OK;
   }
   else
   {
   	Dem_DtcSuppressionApply(dtcId, SuppressionStatus);
   	return E_OK;
   }
#else
   DEM_UNUSED_PARAM(DTC);
   DEM_UNUSED_PARAM(DTCFormat);
   DEM_UNUSED_PARAM(SuppressionStatus);
   return E_NOT_OK;
#endif
}

sint8 Dem_DtcFaultDetectionRetrieve (Dem_DtcIdType dtcId)
{
   Dem_EventIdListIterator eventIt;
   Dem_EventIdType eventId;
   sint8 faultDetectionCtrVal=0;
   sint8 maxFaultDetectionCtrVal = -128;
   sint8 returnValue = 0;

   if(Dem_DtcIsSupported(dtcId))
   {
   	for(Dem_EventIdListIteratorNewFromDtcId(&eventIt, dtcId);
   			Dem_EventIdListIteratorIsValid(&eventIt);
   			Dem_EventIdListIteratorNext(&eventIt))
   	{
   		eventId = Dem_EventIdListIteratorCurrent(&eventIt);
   		if(Dem_GetFaultDetectionCounter(eventId, &faultDetectionCtrVal) == E_OK)
   		{
   		    DEM_A_MAX_AB(maxFaultDetectionCtrVal, faultDetectionCtrVal);
   		                    returnValue=maxFaultDetectionCtrVal;
   		}

   	}
   }
   return returnValue;
}

Std_ReturnType Dem_GetDtcFaultDetectionCounter(Dem_DtcCodeType dtcCode, sint8* FaultDetectionCounter)
{
    Dem_DtcIdType dtcId;

   if( FaultDetectionCounter != NULL_PTR )
   {
        dtcId = Dem_DtcIdFromDtcCode(dtcCode);

        if( Dem_isDtcIdValid(dtcId) )
        {
            *FaultDetectionCounter = Dem_DtcFaultDetectionRetrieve(dtcId);
            return E_OK;
        }
   }

    return E_NOT_OK;
}

void Dem_DtcSetDTCSetting (Dem_DtcIdType dtcId, Dem_boolean_least setBit)
{
    Dem_EventIdListIterator eventIt;

    DEM_ASSERT_ISLOCKED();

    DEM_DTCSTATE_OVERWRITEBIT (&Dem_AllDTCsState[dtcId].state, DEM_DTC_BP_GROUP_DTCSETTING_DISABLED, setBit);

   if(!setBit)
   {
        for(Dem_EventIdListIteratorNewFromDtcId(&eventIt, dtcId);
                Dem_EventIdListIteratorIsValid(&eventIt);
                Dem_EventIdListIteratorNext(&eventIt))
        {
            Dem_EvtSt_HandleDTCSettingOn(Dem_EventIdListIteratorCurrent(&eventIt));
            Dem_EvtSetInitMonitoring((Dem_EventIdListIteratorCurrent(&eventIt)), DEM_INIT_MONITOR_REENABLED);
        }
   }
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
