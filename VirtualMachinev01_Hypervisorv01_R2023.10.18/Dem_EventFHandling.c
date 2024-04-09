#include "Std_Types.hpp"

#include "Dem.hpp"
#include "Rte_Dem.hpp"
#include "Dem_EventFHandling.hpp"
#include "Dem_Cfg_Events.hpp"
#include "Dem_Cfg_Main.hpp"
#include "Dem_Cfg_Nodes.hpp"
#include "Dem_Dependencies.hpp"
#include "Dem_EventRecheck.hpp"
#include "Dem_EvBuff.hpp"
#include "Dem_Deb.hpp"
#include "Dem_Main.hpp"
#include "Dem_EventStatus.hpp"
#include "Dem_ISO14229Byte.hpp"
#include "Dem_DTCs.hpp"
#include "Dem_OperationCycle.hpp"

#if(DEM_CFG_TRIGGERFIMREPORTS == DEM_CFG_TRIGGERFIMREPORTS_ON)
#include "FiM.hpp"
#endif

#include "Dem_EvMemGen.hpp"
#include "Dem_DTCGroup.hpp"
#include "Dem_Lok_CallEvtStChngdCbk.hpp"
#include "Dem_Cfg.hpp"
#include "Dem_Events.hpp"
#include "Dem_RingBuffer.hpp"

#if(DEM_CFG_EVT_PROJECT_EXTENSION)
#include "Dem_PrjEvtProjectExtension.hpp"
#endif

#include "Dem_Lib.hpp"
#include "Dem_Cfg_Events_DataStructures.hpp"

typedef struct{
   Dem_EventStatusType EventStatus;
   Dem_EventIdType EventId;
#if(DEM_CFG_DEBUGDATA_BEFOREINIT == DEM_CFG_DEBUGDATA_BEFOREINIT_ON)
   Dem_DebugDataType debug0;
   Dem_DebugDataType debug1;
#endif
}Dem_ErrorQueueType;

#if(DEM_CFG_DEBUGDATA_BEFOREINIT == DEM_CFG_DEBUGDATA_BEFOREINIT_ON)
#define DEM_ERRORQUEUETYPE_INIT {0,DEM_EVENTID_INVALID,0,0}
#else
#define DEM_ERRORQUEUETYPE_INIT {0,DEM_EVENTID_INVALID}
#endif

typedef struct{
   uint8 overflowcounter;
   boolean isQueueEnabled;
}Dem_ErrorQueueControlType;

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

DEM_DEFINE_RINGBUFFER(Dem_ErrorQueueType, Dem_ErrorQueue, DEM_CFG_BSWERRORBUFFERSIZE);

static Dem_ErrorQueueControlType Dem_ErrorQueueControl;

#if(DEM_CFG_ALLOW_HISTORY == DEM_CFG_ALLOW_HISTORY_ON)
static boolean Dem_HistoryStatusAllowed;
#endif

#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

#if(DEM_CFG_TESTMODE_SUPPORT == DEM_CFG_TESTMODE_SUPPORT_ON)

#define DEM_TESTMODE_EVENTID_OFFSET     10000
#define DEM_DECODE_SUCCESSFULL         TRUE
#define DEM_DECODE_NOT_SUCCESSFULL     FALSE

#define DEM_START_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.hpp"

static boolean Dem_TestModeActive=FALSE;
#define DEM_STOP_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.hpp"
#endif

#if(DEM_CFG_TESTMODE_SUPPORT == DEM_CFG_TESTMODE_SUPPORT_ON)
DEM_INLINE boolean Dem_DecodeTestModeEventId (Dem_EventIdType *EventId)
{
   if(Dem_TestModeActive)
   {

        if(*EventId >= DEM_TESTMODE_EVENTID_OFFSET)
        {
            *EventId = *EventId-DEM_TESTMODE_EVENTID_OFFSET;
            return DEM_DECODE_SUCCESSFULL;
        }
        else{
            return DEM_DECODE_NOT_SUCCESSFULL;
        }
   }
   else{

        if(*EventId >= DEM_TESTMODE_EVENTID_OFFSET)
        {
            return DEM_DECODE_NOT_SUCCESSFULL;
        }
        else{
            return DEM_DECODE_SUCCESSFULL;
        }
   }
}

DEM_INLINE void Dem_EncodeTestModeEventId (Dem_EventIdType *EventId)
{
    *EventId = (*EventId + DEM_TESTMODE_EVENTID_OFFSET);
}
#endif

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
Std_ReturnType  Dem_SetEventStatus(Dem_EventIdType     EventId
   ,     Dem_EventStatusType EventStatus)
{
   return Dem_SetEventStatusWithEnvData (EventId, EventStatus, 0, 0);
}

void Dem_ReportErrorStatus( Dem_EventIdType EventId, Dem_EventStatusType EventStatus )
{
   Dem_ReportErrorStatusWithEnvData (EventId, EventStatus, 0, 0);
}

Std_ReturnType Dem_SetEventStatusWithEnvData (Dem_EventIdType EventId
   ,     Dem_EventStatusType EventStatus
   ,     Dem_DebugDataType debug0
   ,     Dem_DebugDataType debug1)
{
   uint8_least debAction;
   Dem_boolean_least continueProcessing = TRUE;

#if(DEM_CFG_DEBUGDATA == DEM_CFG_DEBUGDATA_OFF)
   	DEM_UNUSED_PARAM(debug0);
   	DEM_UNUSED_PARAM(debug1);
#endif

#if(DEM_CFG_TESTMODE_SUPPORT == DEM_CFG_TESTMODE_SUPPORT_ON)

   if(Dem_DecodeTestModeEventId(&EventId) == DEM_DECODE_NOT_SUCCESSFULL)
   {
        return E_NOT_OK;
   }

#endif

#if(DEM_CFG_LOCK_ALLFAILUREINFO == DEM_CFG_LOCK_ALLFAILUREINFO_ON)
   if(Dem_OpMoIsAllFailureInfoLocked())
   {
   	return E_NOT_OK;
   }
#endif

    DEM_ENTRY_CONDITION_CHECK_INIT_EVTIDVALID_EVTAVAILABLE(EventId, DEM_DET_APIID_SETEVENTSTATUS,E_NOT_OK);

   if(Dem_IsPendingClearEvent(EventId))
   {
        return E_NOT_OK;
   }

   DEM_ENTERLOCK_MON();
   continueProcessing = Dem_DebHandleResetConditions(EventId);
   DEM_EXITLOCK_MON();
   if(!continueProcessing)
   {
        return E_NOT_OK;
   }

   if(!Dem_IsOperationCycleStarted(Dem_EvtParam_GetOperationCycleID(EventId)))
   {
   	return E_NOT_OK;
   }

   debAction = Dem_DebCallFilter(EventId, &EventStatus);

   Dem_EvtSetLastReportedEvent (EventId, EventStatus);

   if(debAction != DEM_DEBACTION_NOOP)
   {
   	Dem_DebHandleDebounceAction(EventId, debAction, debug0, debug1);
   }

#if(DEM_CFG_EVT_PROJECT_EXTENSION)
   Dem_EvtProjectExtensionSetEventStatus(EventId, EventStatus, debAction);
#endif

   if((EventStatus == DEM_EVENT_STATUS_PASSED) || (EventStatus == DEM_EVENT_STATUS_FAILED))
   {

#if(DEM_CFG_SETEVENTSTATUSALLOWEDCALLBACK == DEM_CFG_SETEVENTSTATUSALLOWEDCALLBACK_ON)
   	if(Dem_SetEventStatusAllowedHook(EventId, EventStatus) == E_OK)
#endif
   	{
   		Dem_EvtProcessPassedAndFailed (EventId, EventStatus
   				DEM_DEBUGDATA_PARAM(debug0 ,debug1));

#if(DEM_CFG_SETEVENTSTATUSCALLNOTIFICATION == DEM_CFG_SETEVENTSTATUSCALLNOTIFICATION_ON)
   		Dem_SetEventStatusCallNotification (EventId, faultlevel, debug0, debug1);
#endif
   	}
   }

#if(DEM_CFG_DISTURBANCE_MEMORY == DEM_CFG_DISTURBANCE_MEMORY_ON)
   if(Dem_DistMemIsReportFailedNecessary(EventId, EventStatus))
   {
   	Dem_DistMemReportFailed(EventId
   			DEM_DEBUGDATA_PARAM(debug0 ,debug1));
   }
#endif

   if(EventStatus == DEM_EVENT_STATUS_FAILED)
   {
   	Dem_EvMemGenReportFailedEvent(EventId);
   }

   return E_OK;
}

Std_ReturnType Dem_GetEventFailed(Dem_EventIdType EventId, boolean* EventFailed)
{
    DEM_ENTRY_CONDITION_CHECK_EVENT_ID_VALID_AVAILABLE(EventId,DEM_DET_APIID_DEM_GETEVENTFAILED,E_NOT_OK);
    DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(EventFailed,DEM_DET_APIID_DEM_GETEVENTFAILED,E_NOT_OK);

   if(Dem_GetTestFailedInitState() == FALSE)
   {
        DEM_DET(DEM_DET_APIID_DEM_GETEVENTFAILED, DEM_E_UNINIT);
        return E_NOT_OK;
   }
   else{
        *EventFailed = (boolean)Dem_EvtSt_GetTestFailed(EventId);
        return E_OK;
   }
}

Std_ReturnType Dem_GetEventFailed_GeneralEvtInfo(Dem_EventIdType EventId, boolean* EventFailed)
{
    return Dem_GetEventFailed(EventId, EventFailed);
}

Std_ReturnType Dem_GetEventFdcThresholdReached(Dem_EventIdType EventId, boolean* FdcThresholdReached)
{
#if(DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED)
   if(Dem_EvtIsSuppressed(EventId))
   {
        return E_NOT_OK;
   }

    *FdcThresholdReached = (boolean)Dem_EvtGetFDCThresholdReached(EventId);
    return E_OK;
#else
    DEM_UNUSED_PARAM(EventId);
    DEM_UNUSED_PARAM(FdcThresholdReached);
    return E_NOT_OK;
#endif
}

void Dem_PreInitErrorQueue(void){
    //Initialize the Dem_ErrorQueue ring buffer
    Dem_RingBuffer__Init(Dem_ErrorQueue);
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

DEM_INLINE boolean Dem_CompareFuncForEvents (const Dem_ErrorQueueType *bufferElement, Dem_EventIdType evtId)
{
   return (bufferElement->EventId == evtId);
}

DEM_INLINE void Dem_ReportErrorStatusEnqueue( Dem_EventIdType EventId, Dem_EventStatusType EventStatus
   ,     Dem_DebugDataType debug0, Dem_DebugDataType debug1)
{
   uint16 loc;
   boolean islocationvalid = TRUE;
   boolean isInBuffer;

    DEM_ASSERT_ISLOCKED();

    //Check if the event already exists in the queue or get the next the insertion index
    Dem_RingBufferIndex__ISINBUFFER(Dem_ErrorQueue,Dem_CompareFuncForEvents, EventId, isInBuffer, loc);
   if(!isInBuffer)
   {
        if(!Dem_RingBuffer__insert(&Dem_ErrorQueue_Handler, &loc))
        {
            Dem_ErrorQueueControl.overflowcounter++;
            DEM_DET(DEM_DET_APIID_REPORERRORSTATUSQUEUE,Dem_ErrorQueueControl.overflowcounter);
            islocationvalid = FALSE;
        }
   }

   if(islocationvalid)
   {
        Dem_ErrorQueue[loc].EventId = EventId;
        Dem_ErrorQueue[loc].EventStatus = EventStatus;
#if(DEM_CFG_DEBUGDATA_BEFOREINIT == DEM_CFG_DEBUGDATA_BEFOREINIT_ON)
        Dem_ErrorQueue[loc].debug0 = debug0;
        Dem_ErrorQueue[loc].debug1 = debug1;
#else
        DEM_UNUSED_PARAM(debug0);
        DEM_UNUSED_PARAM(debug1);
#endif
   }
}

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
void Dem_ReportErrorStatusDisableQueue(void){
    Dem_ErrorQueueType tmpErrorEvent = DEM_ERRORQUEUETYPE_INIT;
   uint16 removedIndex = 0;
   boolean eventAvailableForProcessing = TRUE;

   while(Dem_ErrorQueueControl.isQueueEnabled)
   {

        DEM_ENTERLOCK_MON();
        if(Dem_RingBuffer__remove(&Dem_ErrorQueue_Handler,&removedIndex))
        {

            DEM_MEMCPY( &tmpErrorEvent, &Dem_ErrorQueue[removedIndex], DEM_SIZEOF_TYPE(Dem_ErrorQueueType) );
        }
        else{

            Dem_ErrorQueueControl.isQueueEnabled = FALSE;
            Dem_ErrorQueueControl.overflowcounter = 0;

            eventAvailableForProcessing = FALSE;
        }
        DEM_EXITLOCK_MON();

        if(eventAvailableForProcessing && !Dem_EvtIsSuppressed(tmpErrorEvent.EventId))
        {
            if(Dem_IsOperationCycleStarted(Dem_EvtParam_GetOperationCycleID(tmpErrorEvent.EventId)))
            {
#if(DEM_CFG_DEBUGDATA_BEFOREINIT == DEM_CFG_DEBUGDATA_BEFOREINIT_ON)
                Dem_EvtProcessPassedAndFailed (tmpErrorEvent.EventId, tmpErrorEvent.EventStatus
                        DEM_DEBUGDATA_PARAM(tmpErrorEvent.debug0,tmpErrorEvent.debug1));
#else
                Dem_EvtProcessPassedAndFailed (tmpErrorEvent.EventId, tmpErrorEvent.EventStatus
                        DEM_DEBUGDATA_PARAM(0 ,0));
#endif
            }
            else{
                DEM_ENTERLOCK_MON();
                Dem_EvtRequestResetFailureFilter(tmpErrorEvent.EventId, TRUE);
                DEM_EXITLOCK_MON();
            }

#if(DEM_CFG_DISTURBANCE_MEMORY == DEM_CFG_DISTURBANCE_MEMORY_ON)
            if(Dem_DistMemIsReportFailedNecessary(tmpErrorEvent.EventId, tmpErrorEvent.EventStatus))
            {
#if(DEM_CFG_DEBUGDATA_BEFOREINIT == DEM_CFG_DEBUGDATA_BEFOREINIT_ON)
                Dem_DistMemReportFailed(tmpErrorEvent.EventId
                        DEM_DEBUGDATA_PARAM(tmpErrorEvent.debug0,tmpErrorEvent.debug1));
#else
                Dem_DistMemReportFailed(tmpErrorEvent.EventId
                        DEM_DEBUGDATA_PARAM(0 ,0));
#endif
            }
#endif
        }
   }
}

void Dem_ReportErrorStatusEnableQueue(void){
   if(!Dem_ErrorQueueControl.isQueueEnabled)
   {
   	DEM_ENTERLOCK_MON();

   	Dem_ErrorQueueControl.isQueueEnabled = TRUE;
   	Dem_ErrorQueueControl.overflowcounter = 0;

   	DEM_EXITLOCK_MON();
   }
}

void Dem_ReportErrorStatusWithEnvData( Dem_EventIdType EventId
   ,                                 Dem_EventStatusType EventStatus
   ,     Dem_DebugDataType debug0
   ,     Dem_DebugDataType debug1)
{
   uint8_least debAction;
   Dem_boolean_least callSetEventStatus;

#if(DEM_CFG_TESTMODE_SUPPORT == DEM_CFG_TESTMODE_SUPPORT_ON)

   if(Dem_DecodeTestModeEventId(&EventId) == DEM_DECODE_NOT_SUCCESSFULL)
   {
       return;
   }
#endif

   DEM_ENTRY_CONDITION_CHECK_VOID_API_PREINIT_EVTIDVALID_EVTAVAILABLE(EventId, DEM_DET_APIID_REPORTERRORSTATUS);

   if(!Dem_ErrorQueueControl.isQueueEnabled)
   {
#if(DEM_CFG_TESTMODE_SUPPORT == DEM_CFG_TESTMODE_SUPPORT_ON)
        if(Dem_TestModeActive)
   	{
   	    Dem_EncodeTestModeEventId(&EventId);
   	}
#endif
        (void)Dem_SetEventStatusWithEnvData (EventId,EventStatus,debug0,debug1);
        return;
   }else{
      if(Dem_EvtAllEnableConditionsFulfilled(EventId) &&
              Dem_IsEventReportingEnabledByDtcSetting(EventId))
      {
         debAction = Dem_DebCallFilter(EventId, &EventStatus);

         Dem_EvtSetLastReportedEvent (EventId, EventStatus);

         if(debAction != DEM_DEBACTION_NOOP)
         {
           Dem_DebHandleDebounceAction(EventId, debAction, debug0, debug1);
         }

         if((EventStatus == DEM_EVENT_STATUS_PASSED) || (EventStatus == DEM_EVENT_STATUS_FAILED))
         {
        	 DEM_ENTERLOCK_MON();

            if(Dem_ErrorQueueControl.isQueueEnabled)
            {
            	Dem_ReportErrorStatusEnqueue(EventId, EventStatus, debug0, debug1);

            
            	callSetEventStatus = FALSE;
            }
            else{
            	callSetEventStatus = TRUE;
            }

        	 DEM_EXITLOCK_MON();

        	 if(callSetEventStatus)
        	 {
        		 (void)Dem_SetEventStatusWithEnvData (EventId,EventStatus,debug0,debug1);
        	 }
         }
      }
   }
}

Std_ReturnType Dem_ResetEventStatus(Dem_EventIdType EventId)
{
   Dem_UdsStatusByteType isoByteOld, isoByteNew, evtStatus;
   Dem_UdsStatusByteType dtcStByteOld = 0;

#if(DEM_CFG_LOCK_ALLFAILUREINFO == DEM_CFG_LOCK_ALLFAILUREINFO_ON)
   if(Dem_OpMoIsAllFailureInfoLocked())
   {
   	return E_NOT_OK;
   }
#endif

   DEM_ENTRY_CONDITION_CHECK_INIT_EVTIDVALID_EVTAVAILABLE(EventId, DEM_DET_APIID_RESETEVENTSTATUS,E_NOT_OK);

   evtStatus = Dem_EvtGetIsoByte(EventId);

   if(Dem_ISO14229ByteIsTestCompleteTOC(evtStatus))
   {
       return E_NOT_OK;
   }

   if(Dem_EnCoAreAllFulfilled(Dem_EvtParam_GetEnableConditions(EventId)))
   {
   	DEM_ENTERLOCK_MON();
   	Dem_StatusChange_GetOldStatus(EventId, &isoByteOld, &dtcStByteOld);
   	Dem_EvtRequestResetFailureFilter(EventId, TRUE);
   	Dem_EvtSetLastReportedEvent(EventId, DEM_EVENT_STATUS_INVALIDREPORT);
   	Dem_EvtSt_HandleResetEventStatus(EventId);
   	isoByteNew = Dem_EvtGetIsoByte(EventId);

   	DEM_EXITLOCK_MON();

   	Dem_TriggerOn_EventStatusChange(EventId,isoByteOld,isoByteNew,dtcStByteOld);

   	return E_OK;
   }
   else
   {
   	return E_NOT_OK;
   }
}

DEM_INLINE void Dem_SetHistoryStatus (Dem_EventIdType EventId)
{
#if(DEM_CFG_ALLOW_HISTORY == DEM_CFG_ALLOW_HISTORY_ON)
   if(Dem_HistoryStatusAllowed && (!Dem_EvtGetHistoryStatus(EventId)))
   {
        DEM_ENTERLOCK_MON();
        Dem_EvtSetHistoryStatus(EventId, TRUE);
        DEM_EXITLOCK_MON();
   }
#else
    DEM_UNUSED_PARAM (EventId);
#endif
}

void Dem_EvtProcessPassedAndFailed (Dem_EventIdType EventId, Dem_EventStatusType EventStatus
                      DEM_DEBUGDATA_PARAM(Dem_DebugDataType debug0_ul, Dem_DebugDataType debug1_ul))
{
    Dem_ComponentIdType NodeId;
    Dem_boolean_least reportIsFailed = FALSE;
   boolean oldCausal, newCausal, storageFiltered;

    Dem_EvBuffEventType eventType = C_EVENTTYPE_NOEVENT;

    Dem_UdsStatusByteType isoByteOld, isoByteNew;
    Dem_UdsStatusByteType dtcStByteOld = 0;

   if(EventStatus != DEM_EVENT_STATUS_PASSED)
   {
        reportIsFailed = TRUE;
        Dem_SetHistoryStatus(EventId);
   }

   if(   (!Dem_EvtSt_IsUpdateNeeded(EventId, reportIsFailed))
        && (!Dem_EvtIsStorageFiltered(EventId))
        && (!Dem_EvtIsRecheckedAndWaitingForMonResult(EventId))
        && (!Dem_EvtIsNextReportRelevantForMemories(EventId))
       )
   {

        return;
   }

    NodeId = Dem_NodeIdFromEventId(EventId);
    Dem_StatusChange_GetOldStatus(EventId, &isoByteOld, &dtcStByteOld);

    DEM_ENTERLOCK_MON();

   isoByteOld = Dem_EvtGetIsoByte(EventId);  // capture oldstatus again to have it atomic; repeated dtc status capture too expensive

   if(!Dem_EvtIsSuppressed(EventId))
   {
        if(reportIsFailed)
        {
            Dem_EvtSt_HandleFailed(EventId);

            Dem_SetIndicatorActivation(EventId,isoByteOld,Dem_EvtGetIsoByte(EventId));
        }
        else{
            if(Dem_EvtIsRecoverable(EventId))
            {
                Dem_EvtSt_HandlePassed(EventId);
                Dem_SetIndicatorDeActivation(EventId, isoByteOld, Dem_EvtGetIsoByte(EventId));
            }
        }
   }
   else{
        DEM_EXITLOCK_MON();
        return;
   }

   isoByteNew = Dem_EvtGetIsoByte(EventId);
    //Dem_EvtOverwriteFailedCompleteAndWIR(EventId, isoByteNew);

    DEM_EXITLOCK_MON();

    Dem_TriggerOn_EventStatusChange(EventId,isoByteOld,isoByteNew,dtcStByteOld);

   if(    reportIsFailed
         && Dem_EvtIsCausal(EventId)
         && !Dem_StoCoAreAllFulfilled(Dem_EvtParam_GetStorageConditions(EventId))
       )
   {

        return;
   }

    DEM_ENTERLOCK_MON();
   if(isoByteNew == Dem_EvtGetIsoByte(EventId))
   {

        if(reportIsFailed)
        {
            boolean checkIsCausal = Dem_Dependencies_CheckEventIsCausal(EventId, NodeId);
            storageFiltered = !Dem_StoCoAreAllFulfilled(Dem_EvtParam_GetStorageConditions(EventId))
                            || (Dem_NodeAreAllFailedFiltered(NodeId) && !checkIsCausal);
            oldCausal = Dem_EvtIsCausal(EventId);
            newCausal = oldCausal || (checkIsCausal && !storageFiltered);

            Dem_EvtSetStorageFiltered (EventId, storageFiltered);
            Dem_EvtSetCausal (EventId, newCausal);
            Dem_Dependencies_SetNodeFailed ( NodeId, newCausal, storageFiltered, (Dem_EvtParam_GetIsRecoverable(EventId) && Dem_NodeRecoveryAllowed(Dem_NodeIdFromEventId(EventId))) );

            if(checkIsCausal)
            {
                if(!storageFiltered)
                {
                    eventType = C_EVENTTYPE_SET;
                    if(oldCausal)
                    {
                        eventType = C_EVENTTYPE_SET_RECONFIRMED;
                    }
                }else{
                    Dem_StoCoSetHasFilteredEvent(Dem_EvtParam_GetStorageConditions(EventId)
                            DEM_DEBUGDATA_PARAM(EventId,debug1_ul));
                }
            }else{
                if(oldCausal) {
                    eventType = C_EVENTTYPE_SET_RECONFIRMED;
                }
            }
        }
        else{
            if(!Dem_ISO14229ByteIsTestFailed(isoByteNew))
            {
                if(Dem_EvtIsCausal(EventId))
                {
                    Dem_EvtSetCausal (EventId, FALSE);
                    Dem_NodeSetRecovered(NodeId);
                }

                if(        (
                                  (Dem_ISO14229ByteIsTestFailed(isoByteOld)
                                    || Dem_ISO14229ByteIsConfirmedDTC(isoByteOld)
                                    || Dem_ISO14229ByteIsPendingDTC(isoByteOld))
                                    && (!Dem_EvtIsStorageFiltered(EventId))
                            )
                            ||Dem_EvtIsNextReportRelevantForMemories(EventId)
                )
                {
                    eventType = C_EVENTTYPE_RESET;
                }
                Dem_EvtSetStorageFiltered (EventId, FALSE);
                Dem_Dependencies_ResetNodeFailed (NodeId);
            }
        }

   }

    DEM_EXITLOCK_MON();

   if(Dem_NodeIsAvailable (NodeId))
   {
        if((eventType != C_EVENTTYPE_NOEVENT) && (Dem_IsEventStorageEnabledByDtcSetting (EventId)))
        {
            if(!Dem_EvBuffInsert (eventType, EventId DEM_DEBUGDATA_PARAM(debug0_ul, debug1_ul)))
            {
                DEM_ENTERLOCK_MON();
                Dem_EvtSetCausal (EventId, FALSE);
                if(eventType == C_EVENTTYPE_RESET)
                {
                    Dem_EvtSetPassedWasReported (EventId, TRUE);
                }
                DEM_EXITLOCK_MON();
            }
        }
   }
}

#if(DEM_CFG_SUSPICIOUS_SUPPORT)
void Dem_SetEventSuspicion_Internal (Dem_EventIdType EventId, boolean suspicion)
{
    Dem_ComponentIdType NodeId = Dem_NodeIdFromEventId(EventId);

    DEM_ASSERT_ISLOCKED();

   if(Dem_EvtIsSuppressed(EventId))
   {
        return;
   }

   if(suspicion && Dem_EvtSt_GetTestFailed(EventId))
   {
        return;
   }
   if((Dem_EvtIsSuspicious(EventId)) == suspicion)
   {
        return;
   }

    Dem_EvtSetSuspicionLevel(EventId,suspicion);

   if(Dem_NodeIdIsValid(NodeId) && Dem_NodeIsAvailable (NodeId))
   {
        Dem_NodeSetSuspicious(NodeId, suspicion);
   }
}

void Dem_SetEventSuspicion (Dem_EventIdType EventId, boolean suspicion)
{
   DEM_ENTERLOCK_MON();
   Dem_SetEventSuspicion_Internal(EventId, suspicion);
    DEM_EXITLOCK_MON();
}
#endif

Std_ReturnType Dem_GetEventSuspicious(Dem_EventIdType EventId, boolean* EventSuspicious)
{
#if(DEM_CFG_SUSPICIOUS_SUPPORT)
   if(Dem_EvtIsSuppressed(EventId))
   {
        return E_NOT_OK;
   }

    *EventSuspicious = (boolean)Dem_EvtIsSuspicious(EventId);
    return E_OK;
#else
    DEM_UNUSED_PARAM(EventId);
    DEM_UNUSED_PARAM(EventSuspicious);
    return E_NOT_OK;
#endif
}

#if((DEM_CFG_SUPPRESSION == DEM_EVENT_SUPPRESSION) || (DEM_CFG_SUPPRESSION == DEM_EVENT_AND_DTC_SUPPRESSION))
Std_ReturnType Dem_SetEventAvailable(Dem_EventIdType EventId, boolean AvailableStatus)
{
   Std_ReturnType retval;
   retval = Dem_SetEventSuppression(EventId, !AvailableStatus);
    return retval;
}
#endif

Std_ReturnType Dem_GetEventAvailable(Dem_EventIdType EventId, boolean* AvailableStatus)
{
   if(AvailableStatus == NULL_PTR)
   {
        return E_NOT_OK;
   }
   if(!Dem_isEventIdValid(EventId))
   {
        return E_NOT_OK;
   }

    *AvailableStatus = (boolean)Dem_EvtIsSuppressed(EventId);
    return E_OK;
}

Std_ReturnType Dem_SetEventSuppression(Dem_EventIdType EventId, boolean SuppressionStatus)
{
    Std_ReturnType returnVal;
    Dem_UdsStatusByteType evtStatus;

#if(DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
    Dem_ComponentIdType ComponentId;
#endif

   DEM_ENTRY_CONDITION_CHECK_PREINIT_EVTIDVALID(EventId,DEM_DET_APIID_DEM_SETEVENTAVAILABLE,E_NOT_OK);

#if(DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)

   ComponentId = Dem_NodeIdFromEventId(EventId);

   if((!SuppressionStatus) && (!Dem_NodeIsAvailable(ComponentId)))
   {
        return E_NOT_OK;
   }
#endif

   DEM_ENTERLOCK_MON();

   evtStatus = Dem_EvtGetIsoByte(EventId);

   if(    Dem_ISO14229ByteIsTestFailed(evtStatus)
        || Dem_ISO14229ByteIsPendingDTC(evtStatus)
        || Dem_ISO14229ByteIsConfirmedDTC(evtStatus)
        || Dem_ISO14229ByteIsWarningIndicatorRequested(evtStatus))
   {
       returnVal =  E_NOT_OK;
   }
   else
   {
#if((DEM_CFG_SUPPRESSION == DEM_EVENT_SUPPRESSION) || (DEM_CFG_SUPPRESSION == DEM_EVENT_AND_DTC_SUPPRESSION))
       Dem_EvtSetSuppression(EventId, SuppressionStatus);
#else
       DEM_UNUSED_PARAM(SuppressionStatus);
#endif
       returnVal = E_OK;
   }

   DEM_EXITLOCK_MON();

   return returnVal;
}

Std_ReturnType Dem_SetEventSuppressionByDTC(uint32 DTC, Dem_DTCFormatType DTCFormat, boolean SuppressionStatus)
{
#if((DEM_CFG_SUPPRESSION == DEM_EVENT_SUPPRESSION) || (DEM_CFG_SUPPRESSION == DEM_EVENT_AND_DTC_SUPPRESSION))

    Dem_EventIdListIterator eventIt;
    Dem_EventIdType eventId;
    Std_ReturnType retval;
    Dem_DtcIdType dtcId;

   if(DTCFormat == DEM_DTC_FORMAT_UDS)
   {
        dtcId = Dem_DtcIdFromDtcCode(DTC);
   }
   else{

        return E_NOT_OK;
   }

   if(!Dem_isDtcIdValid(dtcId))
   {
        return E_NOT_OK;
   }

    retval = E_OK;
   for(Dem_EventIdListIteratorNewFromDtcId(&eventIt, dtcId);
            Dem_EventIdListIteratorIsValid(&eventIt);
            Dem_EventIdListIteratorNext(&eventIt))
   {
        eventId = Dem_EventIdListIteratorCurrent(&eventIt);

        if(Dem_SetEventSuppression(eventId, SuppressionStatus) == E_NOT_OK)
        {
            retval = E_NOT_OK;
        }
   }

    return retval;

#else
    DEM_UNUSED_PARAM(DTC);
    DEM_UNUSED_PARAM(DTCFormat);
    DEM_UNUSED_PARAM(SuppressionStatus);
    return E_NOT_OK;
#endif
}

void Dem_AllowHistoryStatus(void){
#if(DEM_CFG_ALLOW_HISTORY == DEM_CFG_ALLOW_HISTORY_ON)
   Dem_HistoryStatusAllowed = TRUE;
#endif
}

Std_ReturnType Dem_GetHistoryStatus ( Dem_EventIdType EventId, boolean* historyStatus)
{
#if(DEM_CFG_ALLOW_HISTORY == DEM_CFG_ALLOW_HISTORY_ON)
    if(Dem_EvtIsSuppressed(EventId))
    {
     return E_NOT_OK;
    }

   if(historyStatus != NULL_PTR)
   {
   	*historyStatus = (boolean)Dem_EvtGetHistoryStatus(EventId);
   	return E_OK;
   }
   else
   {
   	DEM_DET(DEM_DET_APIID_GETHISTORYSTATUS, DEM_E_PARAM_POINTER);
   	return E_NOT_OK;
   }
#else
   DEM_UNUSED_PARAM(EventId);
   DEM_UNUSED_PARAM(historyStatus);

   return E_NOT_OK;
#endif
}

#if(DEM_CFG_TESTMODE_SUPPORT == DEM_CFG_TESTMODE_SUPPORT_ON)

Std_ReturnType  Dem_SetEventStatus_TestMode (Dem_EventIdType EventId, Dem_EventStatusType EventStatus)
{
    Dem_EncodeTestModeEventId(&EventId);
    return (Dem_SetEventStatusWithEnvData(EventId, EventStatus, 0, 0));
}

Std_ReturnType Dem_SetEventStatusWithEnvData_TestMode (Dem_EventIdType EventId, Dem_EventStatusType EventStatus, Dem_DebugDataType debug0, Dem_DebugDataType debug1)
{
    Dem_EncodeTestModeEventId(&EventId);
    return (Dem_SetEventStatusWithEnvData(EventId, EventStatus, debug0, debug1));
}

void Dem_ReportErrorStatus_TestMode( Dem_EventIdType EventId, Dem_EventStatusType EventStatus )
{
    Dem_EncodeTestModeEventId(&EventId);
    Dem_ReportErrorStatusWithEnvData (EventId, EventStatus, 0, 0);
    return;
}

void Dem_ReportErrorStatusWithEnvData_TestMode(Dem_EventIdType EventId, Dem_EventStatusType EventStatus, Dem_DebugDataType debug0, Dem_DebugDataType debug1)
{
    Dem_EncodeTestModeEventId(&EventId);
    Dem_ReportErrorStatusWithEnvData(EventId,EventStatus,debug0,debug1);
    return;
}

void Dem_EnableTestMode (boolean TestModeStatus)
{
    Dem_TestModeActive = TestModeStatus;
}
#endif

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

