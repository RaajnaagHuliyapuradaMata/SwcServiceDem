#include "Std_Types.hpp"

#include "Dem_DebArTime.hpp"
#include "Dem_Deb.hpp"
#include "Dem_Events.hpp"
#include "Dem_EventStatus.hpp"
#include "Dem_EventFHandling.hpp"
#include "Dem_DisturbanceMemory.hpp"
#include "Dem_DTCs.hpp"
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

void Dem_DebArTime_GetLimits(const void* paramSet
   ,     uint16 paramIndex
   ,     sint16_least* MinThreshold
   ,     sint16_least* MaxThreshold)
{

   *MinThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].TimePassedThreshold;

   *MaxThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].TimeFailedThreshold;
}

#if(DEM_CFG_DEBARTIMEBASE == DEM_CFG_DEBARTIMEBASE_ON)

uint8_least Dem_DebArTime_Filter(Dem_EventIdType EventId
   ,     Dem_EventStatusType* status
   ,     const void* paramSet
   ,     uint16 paramIndex
        DEM_DEB_LOCAL_CALC_PARAMS)
{
   uint8_least debAction = DEM_DEBACTION_NOOP;
   sint16_least TimePassedThreshold, TimeFailedThreshold;
#if(DEM_CFG_SUSPICIOUS_SUPPORT)

   sint16_least SuspiciousThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].SuspiciousThreshold;
#endif

#if(DEM_CFG_DISTURBANCE_MEMORY == DEM_CFG_DISTURBANCE_MEMORY_ON)
   if((*status == DEM_EVENT_STATUS_PASSED) || (*status == DEM_EVENT_STATUS_PREPASSED))
   {

   	TimeFailedThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].TimeFailedThreshold;

   	if( (Dem_EvtGetDebounceLevel(EventId) < TimeFailedThreshold) && (Dem_EvtGetLastReportedEvent(EventId) == DEM_EVENT_STATUS_PREFAILED) )
   	{
   	    Dem_DistMemReportPassed(EventId);
   	}
   }
#endif

   *status = *status;

   if((*status == DEM_EVENT_STATUS_PASSED) || (*status == DEM_EVENT_STATUS_FAILED))
   {
      DEM_ENTERLOCK_MON();

      switch(*status)
      {

      case DEM_EVENT_STATUS_PASSED:
      {

            TimePassedThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].TimePassedThreshold;
            Dem_EvtSetDebounceLevel (EventId, (sint16) TimePassedThreshold);
#if(DEM_CFG_SUSPICIOUS_SUPPORT)
                if(SuspiciousThreshold != DEM_MAXSINT16)
                {
                    debAction |= DEM_DEBACTION_RESETSUSPICIOUS;
                }
#endif
            Dem_EvtRequestResetFailureFilterAfterDtcSetting(EventId, FALSE);
            Dem_EvtRequestResetFailureFilter(EventId, FALSE);
#if(DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED)
            debAction |= DEM_DEBACTION_RESETFDCTHRESHOLDREACHED;
#endif
            break;
      }

      case DEM_EVENT_STATUS_FAILED:
      {

            TimeFailedThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].TimeFailedThreshold;
            Dem_EvtSetDebounceLevel (EventId, (sint16) TimeFailedThreshold);
            Dem_EvtRequestResetFailureFilterAfterDtcSetting(EventId, FALSE);
            Dem_EvtRequestResetFailureFilter(EventId, FALSE);
#if((DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)||\
    (DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED))
   		debAction |= DEM_DEBACTION_SETFDCTHRESHOLDREACHED;
#endif
   	   break;
      }
      default:
      {

   	   break;
      }
      }
      DEM_EXITLOCK_MON();
   }

   return debAction;
}

void Dem_DebArTime_Cyclic(Dem_EventIdType EventId, const void* paramSet, uint16 paramIndex
                          DEM_DEB_LOCAL_CALC_PARAMS)
{
   sint16_least TimePassedThreshold, TimeFailedThreshold;
   Dem_EventStatusType status2report = DEM_EVENT_STATUS_INVALIDREPORT;
   uint8_least debAction = DEM_DEBACTION_NOOP;
   Dem_boolean_least insertUnrobustToEvBuffer;

#if((DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)||\
    (DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED))

   sint16_least FDCThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].FDCThreshold;
#endif
#if(DEM_CFG_SUSPICIOUS_SUPPORT)

   sint16_least SuspiciousThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].SuspiciousThreshold;
#endif

   if(Dem_EvtIsSuppressed(EventId))
   {
        return;
   }

   DEM_ENTERLOCK_MON();

   (void)Dem_DebHandleResetConditions(EventId);

   switch(Dem_EvtGetLastReportedEvent (EventId))
   {
   	case DEM_EVENT_STATUS_PREPASSED:
   	{

   		TimePassedThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].TimePassedThreshold;

   		if(Dem_EvtGetDebounceLevel (EventId) > TimePassedThreshold)
   		{
   			if(Dem_EvtGetDebounceLevel (EventId) > 0)
   			{
   				Dem_EvtSetDebounceLevel (EventId, 0);
   			}
   			Dem_EvtDecDebounceLevel (EventId);

   			if(Dem_EvtGetDebounceLevel (EventId) == TimePassedThreshold)
   			{
   				status2report = DEM_EVENT_STATUS_PASSED;
   			}
   		}
   		else
   		{
   			if(!Dem_EvtSt_GetTestCompleteTOC(EventId))
   			{
   				status2report = DEM_EVENT_STATUS_PASSED;
   			}
   		}
#if(DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED)
   		    debAction |= DEM_DEBACTION_RESETFDCTHRESHOLDREACHED;
#endif
#if(DEM_CFG_SUSPICIOUS_SUPPORT)
                if(SuspiciousThreshold != DEM_MAXSINT16)
                {
                    debAction |= DEM_DEBACTION_RESETSUSPICIOUS;
                }
#endif
   		break;
   	}

   	case DEM_EVENT_STATUS_PREFAILED:
   	{

   		TimeFailedThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].TimeFailedThreshold;

   		if(Dem_EvtGetDebounceLevel (EventId) < TimeFailedThreshold)
   		{
   			if(Dem_EvtGetDebounceLevel (EventId) < 0)
   			{
   				Dem_EvtSetDebounceLevel (EventId, 0);
   			}
   			Dem_EvtIncDebounceLevel (EventId);

   			if(Dem_EvtGetDebounceLevel (EventId) == TimeFailedThreshold)
   			{
   				status2report = DEM_EVENT_STATUS_FAILED;
   			}

#if((DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)||\
    (DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED))
   			if( Dem_EvtGetDebounceLevel (EventId) >= FDCThreshold)
   			{
   				debAction |= DEM_DEBACTION_SETFDCTHRESHOLDREACHED;
#if(DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)
   				if(status2report != DEM_EVENT_STATUS_FAILED)
   				{
   					status2report = DEM_EVENT_STATUS_PREFAILED;
   					debAction |= DEM_DEBACTION_ALLOW_BUFFER_INSERT;
   				}
#endif
   			}
#endif

#if(DEM_CFG_SUSPICIOUS_SUPPORT)
                if(SuspiciousThreshold != DEM_MAXSINT16)
                {
                    if(Dem_EvtGetDebounceLevel(EventId) >= SuspiciousThreshold)
                    {
                        debAction |= DEM_DEBACTION_SETSUSPICIOUS;
                    }
                }
#endif
   		}

   		else
   		{
   			if(!Dem_EvtSt_GetTestFailed(EventId))
   			{
   				status2report = DEM_EVENT_STATUS_FAILED;
#if((DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)||\
    (DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED))
   				debAction |= DEM_DEBACTION_SETFDCTHRESHOLDREACHED;
#endif
   			}
   		}

   		break;
   	}

   	case DEM_EVENT_STATUS_PASSED:
   	{

   		TimePassedThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].TimePassedThreshold;

   		{

   			Dem_EvtSetDebounceLevel (EventId, (sint16) TimePassedThreshold);

   			if(Dem_EvtSt_GetTestFailed(EventId))
   			{
   				status2report = DEM_EVENT_STATUS_PASSED;
   			}
#if(DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED)
   		debAction |= DEM_DEBACTION_RESETFDCTHRESHOLDREACHED;
#endif
#if(DEM_CFG_SUSPICIOUS_SUPPORT)
                if(SuspiciousThreshold != DEM_MAXSINT16)
                {
                    debAction |= DEM_DEBACTION_RESETSUSPICIOUS;
                }
#endif
   		}
   		break;
   	}

   	case DEM_EVENT_STATUS_FAILED:
   	{

   		TimeFailedThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].TimeFailedThreshold;

   		{
   			Dem_EvtSetDebounceLevel (EventId, (sint16) TimeFailedThreshold);
   			if(!Dem_EvtSt_GetTestFailed(EventId))
   			{
   				status2report = DEM_EVENT_STATUS_FAILED;
#if((DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)||\
    (DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED))
   		debAction |= DEM_DEBACTION_SETFDCTHRESHOLDREACHED;
#endif
   			}
   		}
   		break;
   	}
   	default:
   	{

   		break;
   	}
   }

   insertUnrobustToEvBuffer = Dem_DebHandleDebounceAction_4_TimeBasedDeb(EventId, debAction);
   DEM_EXITLOCK_MON();

   if(insertUnrobustToEvBuffer)
   {
       (void)Dem_EvBuffInsert(C_EVENTTYPE_UNROBUST, EventId DEM_DEBUGDATA_PARAM(0, 0));
   }

   #if(DEM_CFG_DISTURBANCE_MEMORY == DEM_CFG_DISTURBANCE_MEMORY_ON)
   if(Dem_DistMemIsReportFailedNecessary(EventId, status2report))
   {
   	Dem_DistMemReportFailed(EventId
   							DEM_DEBUGDATA_PARAM(0 ,0));
   }
   #endif

   if((status2report == DEM_EVENT_STATUS_PASSED) || (status2report == DEM_EVENT_STATUS_FAILED))
   {
   	Dem_EvtProcessPassedAndFailed(EventId, status2report
   						   DEM_DEBUGDATA_PARAM(0 ,0));
   }
}
#endif
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

