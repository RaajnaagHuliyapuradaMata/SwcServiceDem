

#ifndef DEM_EVENTS_H
#define DEM_EVENTS_H

#include "Dem.hpp"

#include "Dem_Array.hpp"
#include "Dem_BitArray.hpp"
#include "rba_DiagLib_Bits8.hpp"
#include "rba_DiagLib_Bits16.hpp"
#include "rba_DiagLib_Bits32.hpp"
#include "Dem_ISO14229Byte.hpp"

#include "Dem_Clear.hpp"
#include "Dem_Cfg_Events.hpp"
#include "Dem_Cfg_Deb.hpp"
#include "Dem_Cfg_EvBuff.hpp"
#include "Dem_Cfg_Nodes.hpp"
#include "Dem_EventCategory.hpp"
#include "Dem_StorageCondition.hpp"       // -> situationfilterCFG
#include "Dem_EnableCondition.hpp"         // -> enableconditionCFG
#include "Dem_Cfg_Main.hpp"
#include "Dem_Cfg_OperationCycle.hpp"
#include "Dem_Cfg_DistMem.hpp"
#include "Dem_Cfg_StorageCondition.hpp"
#include "Dem_Nvm.hpp"
#include "Dem_IndicatorAttributes.hpp"
#include "Dem_Indicator.hpp"

#include "Dem_Cfg_Events_DataStructures.hpp"

#if(DEM_CFG_EVT_ATTRIBUTE == DEM_CFG_EVT_ATTRIBUTE_ON)
#include "Dem_EventAttribute.hpp"
#endif

typedef Std_ReturnType (* Dem_InitMForEAllowedFncType) (Dem_InitMonitorReasonType InitMonitorReason);
typedef struct{

  uint16 Eventid;
  Dem_InitMForEAllowedFncType InitMForEAllwdCBFnc;
}Dem_InitMonitorForE;

typedef struct{
    Dem_EvtStateType  state;
   sint16 debounceLevel;
}Dem_EvtState;

typedef struct{
    Dem_EventStatusType lastReportedEvent;
}Dem_EvtState8;

typedef void (* Dem_EvtStatusChangeFncType) ( Dem_EventIdType EventId, Dem_UdsStatusByteType EventStatusOld, Dem_UdsStatusByteType EventStatusNew );

#define DEM_EVTPARAM_DEBPARAM_SHIFT   4u
#define DEM_EVTPARAM_DEBMETHOD_MASK   0x0Fu

#if(DEM_CFG_EVTCATEGORY == DEM_CFG_EVTCATEGORY_ON)
typedef struct{
    Dem_EvtCategoryPrioType evtcatprio;
}Dem_EvtCategoryPriority;
#endif

#if(DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
#define DEM_EVTS_INIT_SEQUENTIALFAILURBUFFER(X)    ,(X)
#else
#define DEM_EVTS_INIT_SEQUENTIALFAILURBUFFER(X)
#endif

#if(DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)
#define DEM_EVTS_INIT_STORAGECONDITION(X)          ,(X)
#else
#define DEM_EVTS_INIT_STORAGECONDITION(X)
#endif

#if(DEM_CFG_ENABLECONDITION == DEM_CFG_ENABLECONDITION_ON)
#define DEM_EVTS_INIT_ENABLECONDITION(X)           ,(X)
#else
#define DEM_EVTS_INIT_ENABLECONDITION(X)
#endif

#if(DEM_CFG_EVT_STATUS_CHANGE_NUM_CALLBACKS > 0)
#define DEM_EVTS_INIT_CALLBACKEVENTSTATUSCHANGED(X)                ,(X)
#else
#define DEM_EVTS_INIT_CALLBACKEVENTSTATUSCHANGED(X)
#endif

#if(DEM_CFG_EVT_CLEARALLOWEDCALLBACK != DEM_CFG_EVT_CLEARALLOWEDCALLBACK_OFF)
#define DEM_EVTS_INIT_CALLBACKCLEARALLOWED(X)                ,(X)
#else
#define DEM_EVTS_INIT_CALLBACKCLEARALLOWED(X)
#endif

#if(DEM_CFG_EVT_CLEARALLOWEDCALLBACK != DEM_CFG_EVT_CLEARALLOWEDCALLBACK_OFF)
#define DEM_EVTS_INIT_CLEARALLOWEDBEHAVIOR(X)                ,(X)
#else
#define DEM_EVTS_INIT_CLEARALLOWEDBEHAVIOR(X)
#endif

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

#if(DEM_CFG_EVTCATEGORY == DEM_CFG_EVTCATEGORY_ON)
DEM_ARRAY_DECLARE_CONST(Dem_EvtCategoryPriority,Dem_EvtCategoryPrio,DEM_EVENTCATPRIO_ARRAYLENGTH);
#endif

#if(DEM_CFG_CALLBACK_INIT_MON_FOR_EVENT_SUPPORTED == TRUE)
DEM_ARRAY_DECLARE_CONST(Dem_InitMonitorForE, Dem_Cfg_Callback_InitMForE_List, DEM_CFG_CALLBACK_INITMFORE_LISTLENGTH);
#endif

#if(DEM_CFG_EVT_ATTRIBUTE == DEM_CFG_EVT_ATTRIBUTE_ON)
DEM_ARRAY_DECLARE_CONST(Dem_EventAttributeType, Dem_AllEventsUserAttributes, DEM_EVENTID_ARRAYLENGTH);
#endif

#if(DEM_CFG_EVT_STATUS_CHANGE_NUM_CALLBACKS > 0)
DEM_ARRAY_DECLARE_CONST(Dem_EvtStatusChangeFncType, Dem_AllEventsStatusChangedFnc, DEM_CFG_EVT_STATUS_CHANGE_NUM_CALLBACKS);
#endif

#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.hpp"

#if(DEM_CFG_ALLOW_HISTORY == DEM_CFG_ALLOW_HISTORY_ON)
DEM_BITARRAY_DECLARE  (Dem_AllEventsHistoryStatus, DEM_EVENTID_ARRAYLENGTH);
#endif

#define DEM_STOP_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

extern uint32 Dem_EvtIsAnyInitMonitoringRequestedMask;
DEM_ARRAY_DECLARE(Dem_EvtState, Dem_AllEventsState, DEM_EVENTID_ARRAYLENGTH);
DEM_ARRAY_DECLARE(Dem_EvtState8, Dem_AllEventsState8, DEM_EVENTID_ARRAYLENGTH);
DEM_BITARRAY_DECLARE(Dem_AllEventsResetDebouncerRequested, DEM_EVENTID_ARRAYLENGTH);
DEM_BITARRAY_DECLARE(Dem_EventWasPassedReported,DEM_EVENTID_ARRAYLENGTH);

extern uint16 Dem_GlobalInitMonitoringCounter;

#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

DEM_INLINE Dem_boolean_least Dem_EvtGetHistoryStatus(Dem_EventIdType EventId)
{
#if(DEM_CFG_ALLOW_HISTORY == DEM_CFG_ALLOW_HISTORY_ON)
    return Dem_BitArrayIsBitSet(Dem_AllEventsHistoryStatus, EventId);
#else
    DEM_UNUSED_PARAM(EventId);
    return FALSE;
#endif
}

DEM_INLINE void Dem_EvtSetHistoryStatus(Dem_EventIdType EventId, boolean newStatus)
{
#if(DEM_CFG_ALLOW_HISTORY == DEM_CFG_ALLOW_HISTORY_ON)
    Dem_BitArrayOverwriteBit(Dem_AllEventsHistoryStatus, EventId, newStatus);
    Dem_NvMWriteBlockOnShutdown(DEM_NVM_ID_HISTORY_STATUS_BYTE);
#else
    DEM_UNUSED_PARAM(EventId);
    DEM_UNUSED_PARAM(newStatus);
#endif
}

DEM_INLINE sint16 Dem_EvtGetDebounceLevel (Dem_EventIdType EventId)
{
   return Dem_AllEventsState[EventId].debounceLevel;
}

DEM_INLINE void Dem_EvtSetDebounceLevel (Dem_EventIdType EventId, sint16 debounceLevel)
{
   Dem_AllEventsState[EventId].debounceLevel = debounceLevel;
}

DEM_INLINE void Dem_EvtIncDebounceLevel (Dem_EventIdType EventId)
{
   Dem_AllEventsState[EventId].debounceLevel++;
}

DEM_INLINE void Dem_EvtDecDebounceLevel (Dem_EventIdType EventId)
{
   Dem_AllEventsState[EventId].debounceLevel--;
}

DEM_INLINE Dem_EventStatusType Dem_EvtGetLastReportedEvent (Dem_EventIdType EventId)
{
   return Dem_AllEventsState8[EventId].lastReportedEvent;
}

DEM_INLINE void Dem_EvtSetLastReportedEvent (Dem_EventIdType EventId, Dem_EventStatusType EventStatus)
{
   Dem_AllEventsState8[EventId].lastReportedEvent = EventStatus;
}

Dem_boolean_least Dem_EvtIsRecoverable (Dem_EventIdType EventId);

DEM_INLINE Dem_boolean_least Dem_EvtIsNotRecoverableTOC(Dem_EventIdType EventId)
{
    return (! Dem_EvtIsRecoverable(EventId));
}

DEM_INLINE Dem_boolean_least Dem_EvtIsCausal (Dem_EventIdType EventId)
{
   return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_CAUSALFAULT);
}

DEM_INLINE void Dem_EvtSetCausal_Flag (Dem_EventIdType EventId, Dem_boolean_least setBit)
{
    DEM_ASSERT_ISLOCKED();
   DEM_EVTSTATE_OVERWRITEBIT(&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_CAUSALFAULT, setBit);
}

DEM_INLINE Dem_boolean_least Dem_EvtIsRecheckedAndWaitingForMonResult (Dem_EventIdType EventId)
{
#if(DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
    return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_IS_RECHECKEDANDWAITING_FOR_MONRES);
#else
    DEM_UNUSED_PARAM(EventId);
    return FALSE;
#endif
}

DEM_INLINE void Dem_EvtSetIsRecheckedAndWaitingForMonResult (Dem_EventIdType EventId, Dem_boolean_least setBit)
{
#if(DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
    DEM_ASSERT_ISLOCKED();
    DEM_EVTSTATE_OVERWRITEBIT(&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_IS_RECHECKEDANDWAITING_FOR_MONRES, setBit);
#else
    DEM_UNUSED_PARAM(EventId);
    DEM_UNUSED_PARAM(setBit);
#endif
}

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

boolean Dem_EvtClearEventAllowed ( Dem_EventIdType eventId );
void Dem_EvtSetCausal (Dem_EventIdType EventId, Dem_boolean_least causal);
Std_ReturnType Dem_EvtResetIsoByteCallback(void);
void Dem_EvtPreInitEvents (void);
void Dem_EvtInitEvents(void);

#if((DEM_CFG_SUPPRESSION == DEM_EVENT_SUPPRESSION) || (DEM_CFG_SUPPRESSION == DEM_EVENT_AND_DTC_SUPPRESSION))
void Dem_EvtSetSuppression (Dem_EventIdType EventId, Dem_boolean_least newSuppressed);
#endif

#if(DEM_CFG_CHECKAPICONSISTENCY == TRUE)

Std_ReturnType Dem_GetEventTested_GeneralEvtInfo(Dem_EventIdType EventId, boolean* EventTested);
#endif

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#if(DEM_CFG_ALLOW_HISTORY == DEM_CFG_ALLOW_HISTORY_ON)
//Function to Validate the Nv Blocks after startup
DEM_INLINE void Dem_EvtHistoryStatusInitCheckNvM(void){
    Dem_NvmResultType NvmResult;

   if(Dem_NvMIsInvalidateAllNVMBlocksRequested())
   {

        DEM_MEMSET( &Dem_AllEventsHistoryStatus, 0x00, DEM_SIZEOF_VAR(Dem_AllEventsHistoryStatus));
        Dem_NvMClearBlockByInvalidate(DEM_NVM_ID_HISTORY_STATUS_BYTE);
   }
   else{

        NvmResult = Dem_NvmGetStatus (DEM_NVM_ID_HISTORY_STATUS_BYTE);

        if(NvmResult != DEM_NVM_SUCCESS)
        {

            DEM_MEMSET( &Dem_AllEventsHistoryStatus, 0x00, DEM_SIZEOF_VAR(Dem_AllEventsHistoryStatus));
            Dem_NvMWriteBlockOnShutdown(DEM_NVM_ID_HISTORY_STATUS_BYTE);
        }
   }
}
#endif

DEM_INLINE Dem_boolean_least Dem_EvtIsSuspicious (Dem_EventIdType EventId)
{
   return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_SUSPICIONLEVEL);
}

DEM_INLINE void Dem_EvtSetSuspicionLevel (Dem_EventIdType EventId, Dem_boolean_least setBit)
{
   DEM_EVTSTATE_OVERWRITEBIT (&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_SUSPICIONLEVEL, setBit);
}

#if(DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)
DEM_INLINE Dem_boolean_least Dem_EvtGetFDCThresholdReachedTOC (Dem_EventIdType EventId)
{
  return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_FDCTHRESHOLDREACHEDTOC);
}

DEM_INLINE void Dem_EvtSetFDCThresholdReachedTOC (Dem_EventIdType EventId, Dem_boolean_least setBit)
{
   DEM_EVTSTATE_OVERWRITEBIT (&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_FDCTHRESHOLDREACHEDTOC, setBit);
}
#endif

#if(DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED)
DEM_INLINE Dem_boolean_least Dem_EvtGetFDCThresholdReached (Dem_EventIdType EventId)
{
  return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_FDCTHRESHOLDREACHED);
}
#endif

DEM_INLINE void Dem_EvtSetFDCThresholdReached (Dem_EventIdType EventId, Dem_boolean_least setBit)
{
#if(DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED)
   DEM_EVTSTATE_OVERWRITEBIT (&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_FDCTHRESHOLDREACHED, setBit);
#else
   DEM_UNUSED_PARAM(EventId);
   DEM_UNUSED_PARAM(setBit);
#endif
}

#if(DEM_CFG_EVTCATEGORY == DEM_CFG_EVTCATEGORY_ON)

DEM_INLINE Dem_EvtCategoryPriorityType Dem_GetEventCategoryPriority (Dem_EventCategoryType Category)
{
    return (Dem_EvtCategoryPriorityType) Dem_EvtCategoryPrio[Category].evtcatprio;
}
#endif

DEM_INLINE Dem_boolean_least Dem_EvtIsStorageFiltered (Dem_EventIdType EventId)
{
#if(DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)
   return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_ISSTORAGEFILTERED);
#else
   DEM_UNUSED_PARAM(EventId);
   return FALSE;
#endif
}

DEM_INLINE void Dem_EvtSetStorageFiltered (Dem_EventIdType EventId, Dem_boolean_least setBit)
{
#if(DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)
   DEM_EVTSTATE_OVERWRITEBIT (&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_ISSTORAGEFILTERED, setBit);
#else
   DEM_UNUSED_PARAM(EventId);
   DEM_UNUSED_PARAM(setBit);
#endif
}
DEM_INLINE Dem_boolean_least Dem_EvtAllEnableConditionsFulfilled (Dem_EventIdType EventId)
{
   return (Dem_EnCoAreAllFulfilled(Dem_EvtParam_GetEnableConditions(EventId)));
}

DEM_INLINE void Dem_EvtRequestResetFailureFilter(Dem_EventIdType EventId, Dem_boolean_least setBit)
{
    DEM_ASSERT_ISLOCKED();
    Dem_BitArrayOverwriteBit(Dem_AllEventsResetDebouncerRequested, EventId, setBit);
}

DEM_INLINE Dem_boolean_least Dem_EvtIsResetFailureFilterRequested(Dem_EventIdType EventId)
{
    return Dem_BitArrayIsBitSet(Dem_AllEventsResetDebouncerRequested, EventId);
}

DEM_INLINE Dem_boolean_least Dem_EvtIsResetFailureFilterRequestedAfterDtcSetting (Dem_EventIdType EventId)
{

#if(!DEM_CFG_DTCSETTINGBLOCKSREPORTING)
    return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_DEBCOUNTER_RESET_REQUESTED);
#else
    DEM_UNUSED_PARAM(EventId);
    return FALSE;
#endif
}

DEM_INLINE void Dem_EvtRequestResetFailureFilterAfterDtcSetting (Dem_EventIdType EventId, Dem_boolean_least setBit)
{

    DEM_ASSERT_ISLOCKED();

#if(!DEM_CFG_DTCSETTINGBLOCKSREPORTING)
   DEM_EVTSTATE_OVERWRITEBIT (&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_DEBCOUNTER_RESET_REQUESTED, setBit);
#else
   DEM_UNUSED_PARAM(EventId);
   DEM_UNUSED_PARAM(setBit);
#endif
}

DEM_INLINE void Dem_EvtRequestResetFailureFilterAfterStorageCondition (Dem_EventIdType EventId, Dem_boolean_least setBit)
{
   DEM_ASSERT_ISLOCKED();
#if(DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)
    DEM_EVTSTATE_OVERWRITEBIT (&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_IS_STORAGEFILTERED_EVENT_REPORTED, setBit);
#else
    DEM_UNUSED_PARAM(EventId);
    DEM_UNUSED_PARAM(setBit);
#endif
}

DEM_INLINE Dem_boolean_least Dem_EvtIsResetFailureFilterRequestedAfterStorageCondition (Dem_EventIdType EventId)
{
#if(DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)
    return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_IS_STORAGEFILTERED_EVENT_REPORTED);
#else
    DEM_UNUSED_PARAM(EventId);
   return FALSE;
#endif
}

DEM_INLINE void Dem_EvtIncreaseGlobalInitMonitoringCounter(void){
    Dem_GlobalInitMonitoringCounter++;
}

DEM_INLINE void Dem_EvtSetAnyInitMonitoring (Dem_InitMonitorReasonType reason) { rba_DiagLib_Bit32SetBit(&Dem_EvtIsAnyInitMonitoringRequestedMask, reason); }
DEM_INLINE void Dem_EvtResetAnyInitMonitoring (void) { Dem_EvtIsAnyInitMonitoringRequestedMask = 0u; }
DEM_INLINE boolean Dem_EvtIsAnyInitMonitoringRequested (void) { return (Dem_EvtIsAnyInitMonitoringRequestedMask != 0u); }
DEM_INLINE boolean Dem_EvtIsAnyInitMonitoringRequestedClear (void) { return rba_DiagLib_Bit32IsBitSet(Dem_EvtIsAnyInitMonitoringRequestedMask, DEM_INIT_MONITOR_CLEAR); }
//DEM_INLINE boolean Dem_EvtIsAnyInitMonitoringRequestedRestart (void) { return rba_DiagLib_Bit32IsBitSet(Dem_EvtIsAnyInitMonitoringRequestedMask, DEM_INIT_MONITOR_RESTART); }
//DEM_INLINE boolean Dem_EvtIsAnyInitMonitoringRequestedRecheck (void) { return rba_DiagLib__Bit32IsBitSet(Dem_EvtIsAnyInitMonitoringRequestedMask, DEM_INIT_MONITOR_STORAGE_REENABLED); }

DEM_INLINE void Dem_EvtSetInitMonitoring (Dem_EventIdType EventId, Dem_InitMonitorReasonType newReason)
{
    Dem_InitMonitorReasonType oldReason = (Dem_InitMonitorReasonType)DEM_EVTSTATE_GETBITS (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_INITMONITORING, DEM_EVT_BP_STATE_INITMONITORING_SIZE);

    DEM_ASSERT_ISLOCKED();
   if((oldReason == 0u) || (oldReason > newReason))
   {
        DEM_EVTSTATE_OVERWRITEBITS (&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_INITMONITORING, DEM_EVT_BP_STATE_INITMONITORING_SIZE, newReason);
   }
    Dem_EvtIncreaseGlobalInitMonitoringCounter();
    Dem_EvtSetAnyInitMonitoring (newReason);
}

DEM_INLINE uint8 Dem_EvtIsInitMonitoringRequested (Dem_EventIdType EventId)
{
  return ((uint8)(DEM_EVTSTATE_GETBITS (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_INITMONITORING, DEM_EVT_BP_STATE_INITMONITORING_SIZE )));
}

DEM_INLINE void Dem_EvtClearInitMonitoringRequests (Dem_EventIdType EventId)
{
  DEM_EVTSTATE_CLEARBITS (&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_INITMONITORING, DEM_EVT_BP_STATE_INITMONITORING_SIZE);
}

#if(DEM_CFG_CALLBACK_INIT_MON_FOR_EVENT_SUPPORTED == TRUE)

DEM_INLINE void Dem_InitMonitorForEFnc (void){
    Dem_InitMonitorReasonType InitMonitorReason;
   uint16_least i;
   if(Dem_EvtIsAnyInitMonitoringRequested())
   {
        DEM_ENTERLOCK_MON();

        Dem_EvtResetAnyInitMonitoring();

        DEM_EXITLOCK_MON();
        for(i=0u; i<DEM_CFG_CALLBACK_INITMFORE_LISTLENGTH; i++)
        {
            if(Dem_IsInitMonitorForEventRequested(Dem_Cfg_Callback_InitMForE_List[i].Eventid, &InitMonitorReason))
            {
                Dem_Cfg_Callback_InitMForE_List[i].InitMForEAllwdCBFnc(InitMonitorReason);
            }
        }
   }
}

#endif

#if( DEM_CFG_EVT_STATUS_CHANGE_NUM_CALLBACKS > 0 )
DEM_INLINE void Dem_CallEventStatusChangedCallBack (Dem_EventIdType EventId, Dem_UdsStatusByteType EventStatusOld, Dem_UdsStatusByteType EventStatusNew )
{
  if(Dem_EvtParam_GetCallbackEventStatusChangedIndex(EventId) > 0)
  {
    (*Dem_AllEventsStatusChangedFnc[Dem_EvtParam_GetCallbackEventStatusChangedIndex(EventId)])(EventId, EventStatusOld, EventStatusNew);
  }
  else{

  }
}
#endif

#if(DEM_CFG_EVT_INDICATOR != DEM_CFG_EVT_INDICATOR_PROJECTSPECIFIC)
DEM_INLINE void Dem_EvtSetWIRExtern(Dem_EventIdType EventId, Dem_boolean_least newState)
{
  DEM_EVTSTATE_OVERWRITEBIT (&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_WIRSTATUS_EXTERNAL,newState);
}

DEM_INLINE Dem_boolean_least Dem_EvtIsWIRExternal(Dem_EventIdType EventId)
{
  return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_WIRSTATUS_EXTERNAL);
}
#else
#define Dem_EvtSetWIRExtern(X,Y)    do{}while(0);
#define Dem_EvtIsWIRExternal(X)     (FALSE)
#endif

DEM_INLINE Dem_boolean_least Dem_isEventAffectedByOperationCycleList (Dem_EventIdType EventId, Dem_OperationCycleList operationCycleList)
{
  return ((operationCycleList & (Dem_OperationCycleList)(1u<<Dem_EvtParam_GetOperationCycleID(EventId))) != 0u);
}

DEM_INLINE Dem_boolean_least Dem_isEventAffectedByAgingCycleList (Dem_EventIdType EventId, Dem_OperationCycleList agingCycleList)
{
  return ((agingCycleList & (Dem_OperationCycleList)(1u<<Dem_EvtParam_GetAgingCycleID(EventId))) != 0u);
}

DEM_INLINE Dem_boolean_least Dem_isEventAffectedByFailureCycleList (Dem_EventIdType EventId, Dem_OperationCycleList failureCycleList)
{
   return ((failureCycleList & (Dem_OperationCycleList)(1u<<Dem_EvtParam_GetFailureCycleID(EventId))) != 0u);
}

#if(DEM_CFG_DISTURBANCE_MEMORY == DEM_CFG_DISTURBANCE_MEMORY_ON)

#define DEM_DIST_MEM_IND_SET_BIT_MASK   (Dem_EvtStateType)(((Dem_EvtStateType)DEM_EVT_BP_STATE_DIST_MEM_IDX_MASK) << DEM_EVT_BP_STATE_DIST_MEM_IDX)
#define DEM_DIST_MEM_IND_CLEAR_BIT_MASK (Dem_EvtStateType)(~((Dem_EvtStateType)DEM_DIST_MEM_IND_SET_BIT_MASK))

DEM_INLINE Dem_boolean_least Dem_EvtIsEventStoredInDistMem (Dem_EventIdType EventId)
{
  return ((Dem_AllEventsState[EventId].state & DEM_DIST_MEM_IND_SET_BIT_MASK) != 0u);
}

DEM_INLINE void Dem_EvtSetEventsDistMemIndex (Dem_EventIdType EventId , uint8 idx)
{
   Dem_AllEventsState[EventId].state = ((Dem_AllEventsState[EventId].state & DEM_DIST_MEM_IND_CLEAR_BIT_MASK) |   \
   		((Dem_EvtStateType)(((Dem_EvtStateType)(idx & DEM_EVT_BP_STATE_DIST_MEM_IDX_MASK)) << DEM_EVT_BP_STATE_DIST_MEM_IDX)));
}

DEM_INLINE uint8 Dem_EvtGetEventsDistMemIndex (Dem_EventIdType EventId)
{
   return ((uint8)((Dem_AllEventsState[EventId].state & DEM_DIST_MEM_IND_SET_BIT_MASK) >> DEM_EVT_BP_STATE_DIST_MEM_IDX));
}

#endif

DEM_INLINE Dem_boolean_least Dem_EvtIsSuppressed (Dem_EventIdType EventId)
{
  return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_NOTAVAILABLE);
}

DEM_INLINE Dem_boolean_least Dem_EvtIsNextReportRelevantForMemories (Dem_EventIdType EventId)
{
   return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_NXT_REPORT_IS_RELEVANT);
}

DEM_INLINE void Dem_EvtSetNextReportRelevantForMemories (Dem_EventIdType EventId, Dem_boolean_least setBit)
{
   DEM_EVTSTATE_OVERWRITEBIT (&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_NXT_REPORT_IS_RELEVANT, setBit);
}

#if DEM_CFG_OBD == DEM_CFG_OBD_ON

DEM_INLINE Dem_boolean_least Dem_EvtGetTestFailedTFCSincePreinit(Dem_EventIdType EventId)
{
    return DEM_EVTSTATE_ISBITSET(Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_TFTFC_SINCE_PREINIT);
}

DEM_INLINE void Dem_EvtSetTestFailedTFCSincePreinit(Dem_EventIdType EventId, Dem_boolean_least newState)
{
    DEM_ASSERT_ISLOCKED();
    DEM_EVTSTATE_OVERWRITEBIT(&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_TFTFC_SINCE_PREINIT, newState);
}

DEM_INLINE Dem_boolean_least Dem_EvtGetTestCompleteTFCSincePreinit(Dem_EventIdType EventId)
{
    return DEM_EVTSTATE_ISBITSET(Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_TCTFC_SINCE_PREINIT);
}

DEM_INLINE void Dem_EvtSetTestCompleteTFCSincePreinit(Dem_EventIdType EventId, Dem_boolean_least newState)
{
    DEM_ASSERT_ISLOCKED();
    DEM_EVTSTATE_OVERWRITEBIT(&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_TCTFC_SINCE_PREINIT, newState);
}
#endif

DEM_INLINE void Dem_EvtSetPassedWasReported (Dem_EventIdType EventId, Dem_boolean_least setBit)
{
    DEM_ASSERT_ISLOCKED();
    Dem_BitArrayOverwriteBit (Dem_EventWasPassedReported, EventId, setBit);
}

DEM_INLINE Dem_boolean_least Dem_EvtWasPassedReported (DEM_BITARRAY_CONSTFUNCPARAM(buffer), Dem_EventIdType EventId)
{
    return Dem_BitArrayIsBitSet (buffer, EventId);
}

#endif

