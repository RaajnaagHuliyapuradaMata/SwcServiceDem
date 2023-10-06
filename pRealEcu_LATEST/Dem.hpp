#ifndef DEM_H
#define DEM_H

#include "Dem_Types.hpp"

#include "Dem_Cfg_Version.hpp"
#include "Dem_Cfg_EventId.hpp"
#include "Dem_Cfg_DtcId.hpp"
#include "Dem_Cfg_NodeId.hpp"
#include "Dem_Cfg_Main.hpp"
#include "Dem_Cfg_Deb.hpp"
#include "Dem_Cfg_EnableCondition.hpp"
#include "Dem_Cfg_EventCategory.hpp"
#include "Dem_Cfg_EventIndicators.hpp"
#include "Dem_Cfg_OperationCycle.hpp"
#include "Dem_Cfg_StorageCondition.hpp"
#include "Dem_Dlt.hpp"
#include "Dem_Dcm.hpp"
#include "Dem_J1939Dcm.hpp"

#ifdef DEM_CFG_EXTPROTOTYPES_H
#error "Do not include 'Dem_Cfg_ExtPrototypes.h' in header file"
#endif

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#if(DEM_CFG_CHECKAPICONSISTENCY == FALSE)
#ifndef RTE_TYPE_H
    #error "If the RTE is not used, then /Dem/DemGeneral/DemRbGeneral/DemRbCheckApiConsistency has to be set to True."
#endif

#else

#if(DEM_CFG_EVT_INDICATOR != DEM_CFG_EVT_INDICATOR_OFF)

Std_ReturnType Dem_GetIndicatorStatus(uint8 IndicatorId, Dem_IndicatorStatusType* IndicatorStatus);
#endif

Std_ReturnType Dem_GetOperationCycleState(Dem_OperationCycleIdType OperationCycleId, Dem_OperationCycleStateType* CycleState);
Std_ReturnType Dem_GetCycleQualified(Dem_OperationCycleIdType OperationCycleId,boolean* isQualified);
void infSwcServiceDemSwcServiceSchM_vMainFunction(void);
Std_ReturnType Dem_SetOperationCycleState(Dem_OperationCycleIdType OperationCycleId, Dem_OperationCycleStateType CycleState);
Std_ReturnType Dem_SetCycleQualified(Dem_OperationCycleIdType OperationCycleId);
Std_ReturnType Dem_GetEventMemoryOverflow(Dem_DTCOriginType DTCOrigin, boolean* OverflowIndication);
Std_ReturnType Dem_GetNumberOfEventMemoryEntries(Dem_DTCOriginType DTCOrigin, uint8* NumberOfEventMemoryEntries);
Std_ReturnType Dem_SetWIRStatus(Dem_EventIdType EventId, boolean WIRStatus);
Std_ReturnType Dem_GetDebouncingOfEvent(Dem_EventIdType EventId, Dem_DebouncingStateType* DebouncingState);
Std_ReturnType Dem_GetDTCOfEvent(Dem_EventIdType EventId, Dem_DTCFormatType DTCFormat, uint32* DTCOfEvent);
Std_ReturnType Dem_GetEventFailed(Dem_EventIdType EventId, boolean* EventFailed);
Std_ReturnType Dem_GetEventStatus(Dem_EventIdType EventId, Dem_UdsStatusByteType* EventStatusExtended);
Std_ReturnType Dem_GetEventTested(Dem_EventIdType EventId, boolean* EventTested);
Std_ReturnType Dem_GetFaultDetectionCounter(Dem_EventIdType EventId, sint8* FaultDetectionCounter);
Std_ReturnType Dem_ResetEventStatus(Dem_EventIdType EventId);
Std_ReturnType Dem_SetEventStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus);
Std_ReturnType Dem_GetStorageCondition(uint8 StorageConditionID, boolean* ConditionFulfilled);
Std_ReturnType Dem_SetDTCSuppression(uint32 DTC, Dem_DTCFormatType DTCFormat, boolean SuppressionStatus);
Std_ReturnType Dem_SetEnableCondition(uint8 EnableConditionID, boolean ConditionFulfilled);

#if((DEM_CFG_SUPPRESSION == DEM_EVENT_SUPPRESSION) || (DEM_CFG_SUPPRESSION == DEM_EVENT_AND_DTC_SUPPRESSION))
    Std_ReturnType Dem_SetEventAvailable(Dem_EventIdType EventId, boolean AvailableStatus);
#endif

Std_ReturnType Dem_SetStorageCondition(uint8 StorageConditionID, boolean ConditionFulfilled);
Std_ReturnType Dem_ClearPrestoredFreezeFrame(Dem_EventIdType EventId);
Std_ReturnType Dem_GetEventExtendedDataRecordEx(Dem_EventIdType EventId, uint8 RecordNumber, uint8* DestBuffer, uint16* BufSize);
Std_ReturnType Dem_GetEventFreezeFrameDataEx(Dem_EventIdType EventId, uint8 RecordNumber, uint16 DataId, uint8* DestBuffer, uint16* BufSize);
Std_ReturnType Dem_PrestoreFreezeFrame(Dem_EventIdType EventId);
Std_ReturnType Dem_ResetEventDebounceStatus(Dem_EventIdType EventId, Dem_DebounceResetStatusType DebounceResetStatus);

#endif

Std_ReturnType Dem_DebSwitchToParameters(uint8 CounterParamSetId);
Std_ReturnType Dem_GetDtcFaultDetectionCounter(Dem_DtcCodeType dtcCode, sint8* FaultDetectionCounter);
Std_ReturnType Dem_GetEventAvailable(Dem_EventIdType EventId, boolean* AvailableStatus);

#if(DEM_CFG_ERASE_ALL_DATA_SUPPORTED != DEM_CFG_ERASE_ALL_OFF)
Std_ReturnType Dem_GetEraseAllNvMDataResult(Dem_EraseAllStatusType* EraseResult);
#endif

#if(DEM_CFG_VERSION_INFO_API == DEM_CFG_VERSION_INFO_API_ON)
void Dem_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

#if(DEM_CFG_ALTERNATIVEDTC == DEM_CFG_ALTERNATIVEDTC_ON)
void Dem_SwitchToAlternativeDtc(void);
#endif

#if(DEM_CFG_TRIGGER_TO_STORE_NVM_SUPPORTED)
Std_ReturnType Dem_TriggerStorageToNvm(void);
#endif

#if(DEM_CFG_DEBTIMEBASED_CONFIGURED_CYCLICTASKTIME)
void Dem_TimeBasedDebounceMainFunction(void);
#endif

void Dem_AllowHistoryStatus(void);
Dem_EventStatusType Dem_EvtGetLastReportedEventStatus(Dem_EventIdType EventId);
Std_ReturnType Dem_GetDtcKindOfEvent(Dem_EventIdType EventId, Dem_DTCKindType *DtcKind);
Std_ReturnType Dem_GetEventCategory(Dem_EventIdType EventId, Dem_EventCategoryType *EventCategory);
Std_ReturnType Dem_GetEventFdcThresholdReached(Dem_EventIdType EventId, boolean* FdcThresholdReached);
Std_ReturnType Dem_GetEventSuspicious(Dem_EventIdType EventId, boolean* EventSuspicious);
Std_ReturnType Dem_GetHistoryStatus(Dem_EventIdType EventId, boolean *historyStatus);
Std_ReturnType Dem_IsAnyInitMonitorForEventRequested(uint16 *localCounter, boolean *modified);
boolean Dem_IsInitMonitorForEventRequested(Dem_EventIdType EventId, Dem_InitMonitorReasonType* InitMonitorReason);
Std_ReturnType Dem_ManipulateEventDebounceStatus(Dem_EventIdType EventId, Dem_DebugDataType debug0, Dem_DebugDataType debug1, sint16 manipulationValue);
Std_ReturnType Dem_OverwriteWIRStatus(Dem_EventIdType EventId, boolean WIRStatus);
void Dem_ReportErrorStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus);
void Dem_ReportErrorStatusWithEnvData( Dem_EventIdType EventId,Dem_EventStatusType EventStatus,Dem_DebugDataType debug0,Dem_DebugDataType debug1);

Std_ReturnType Dem_SetEventStatusWithEnvData(Dem_EventIdType EventId
   ,     Dem_EventStatusType EventStatus
   ,     Dem_DebugDataType debug0
   ,     Dem_DebugDataType debug1);

#if(DEM_CFG_SUSPICIOUS_SUPPORT)
void Dem_SetEventSuspicion(Dem_EventIdType EventId, boolean suspicion);
#endif

Std_ReturnType Dem_SetIndicatorStatusForEvent(Dem_EventIdType EventId, Dem_IndicatorIdType IndicatorId, boolean IndicatorActivation);
Std_ReturnType Dem_LockAllFailureInfo(void);
Std_ReturnType Dem_GetComponentAvailable(Dem_ComponentIdType ComponentId, boolean* ComponentAvailable);

#if(DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
Std_ReturnType Dem_SetComponentAvailable(Dem_ComponentIdType ComponentId, boolean AvailableStatus);
#endif

Std_ReturnType Dem_SetEventSuppression(Dem_EventIdType EventId, boolean SuppressionStatus);
Std_ReturnType Dem_SetEventSuppressionByDTC(uint32 DTC, Dem_DTCFormatType DTCFormat, boolean SuppressionStatus);

Std_ReturnType Dem_GetEventExtendedDataRecord(
        Dem_EventIdType EventId
   ,     uint8 RecordNumber
   ,     uint8* DestBuffer
   ,     uint16* BufSize
);

Std_ReturnType Dem_GetEventFreezeFrameData(
        Dem_EventIdType EventId
   ,     uint8 RecordNumber
   ,     boolean ReportTotalRecord
   ,     uint16 DataId
   ,     uint8* DestBuffer
   ,     uint16* BufSize
);

boolean Dem_GetEvMemLock(void);
Dem_ReadEventType Dem_GetNextEventFromMemory (Dem_ReadEventsFromMemoryType* ReadEventsFromMemoryState, Dem_EventIdType* EventId, uint16* LocId);
Std_ReturnType Dem_LockEventMemory(boolean Lock);
Std_ReturnType Dem_PrestoreFreezeFrameWithEnvData(Dem_EventIdType EventId ,Dem_DebugDataType debug0 ,Dem_DebugDataType debug1);
Dem_ReadEventType Dem_ReadEventsFromMemory(Dem_ReadEventsFromMemoryType* ReadEventsFromMemoryState, Dem_DTCOriginType origin);
Std_ReturnType Dem_ClearDisturbanceMemory(void);
Std_ReturnType Dem_GetNextDisturbanceData(Dem_EventIdType* EventId, uint8* DestBuffer, uint8* BufSize);
Std_ReturnType Dem_LockDisturbanceMemory(boolean Lock);
Std_ReturnType Dem_ReadDisturbanceMemory(void);
Std_ReturnType Dem_GetComponentAreAncestorsInitialized(Dem_ComponentIdType ComponentId, boolean* ComponentAreAncestorsInitialized);
Std_ReturnType Dem_GetComponentFailed(Dem_ComponentIdType ComponentId, boolean* ComponentFailed);
Std_ReturnType Dem_GetComponentFailedItself(Dem_ComponentIdType ComponentId, boolean* ComponentFailedItself);
Std_ReturnType Dem_GetComponentInitialized(Dem_ComponentIdType ComponentId, boolean* ComponentInitialized);
Std_ReturnType Dem_GetComponentRestrictedUsable(Dem_ComponentIdType ComponentId, boolean* ComponentRestrictedUsable);
Std_ReturnType Dem_GetComponentSuspicious(Dem_ComponentIdType ComponentId, boolean* ComponentSuspicious);
Std_ReturnType Dem_GetComponentSuspiciousItself(Dem_ComponentIdType ComponentId, boolean* ComponentSuspiciousItself);
Std_ReturnType Dem_GetComponentUsable(Dem_ComponentIdType ComponentId, boolean* ComponentUsable);
boolean Dem_NodeAreAllFailedFiltered(Dem_ComponentIdType NodeId);

#if(DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
boolean Dem_NodeAreAncestorsAvailable(Dem_ComponentIdType NodeId);
boolean Dem_NodeAreAncestorsFailed(Dem_ComponentIdType NodeId);
boolean Dem_NodeAreAncestorsRestrictedUsable(Dem_ComponentIdType NodeId);
boolean Dem_NodeAreAncestorsSuspicious(Dem_ComponentIdType NodeId);
boolean Dem_NodeAreAncestorsUsable(Dem_ComponentIdType NodeId);
boolean Dem_NodeHasCausalFault(Dem_ComponentIdType NodeId);
#endif

void Dem_NodeSetInitialized(Dem_ComponentIdType NodeId, boolean init);

#if(DEM_CFG_TESTMODE_SUPPORT == DEM_CFG_TESTMODE_SUPPORT_ON)

void Dem_EnableTestMode(boolean TestModeStatus);

void Dem_ReportErrorStatus_TestMode(Dem_EventIdType EventId, Dem_EventStatusType EventStatus);

void Dem_ReportErrorStatusWithEnvData_TestMode(Dem_EventIdType EventId
   ,     Dem_EventStatusType EventStatus
   ,     Dem_DebugDataType debug0
   ,     Dem_DebugDataType debug1);

Std_ReturnType Dem_SetEventStatus_TestMode(Dem_EventIdType EventId, Dem_EventStatusType EventStatus);

Std_ReturnType Dem_SetEventStatusWithEnvData_TestMode(Dem_EventIdType EventId
   ,     Dem_EventStatusType EventStatus
   ,     Dem_DebugDataType debug0
   ,     Dem_DebugDataType debug1);

#endif
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
extern const Dem_ConfigType Dem_ConfigAlternativeParameters;
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
void Dem_Init(void);
void Dem_PreInit(const Dem_ConfigType* ConfigPtr);
void Dem_Shutdown(void);
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#endif
