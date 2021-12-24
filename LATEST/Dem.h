#pragma once

class class_Dem{
   public:
      void PreInit(void);
      void InitFunction(void);
      void GetVersionInfo(void);
      void Shutdown(void);
      void ClearDTC(void);
      void ClearPrestoredFreezeFrame(void);
      void GetComponentFailed(void);
      void GetDTCSelectionResult(void);
      void GetDTCSelectionResultForClearDTC(void);
      void GetEventUdsStatus(void);
      void GetMonitorStatus(void);
      void GetDebouncingOfEvent(void);
      void GetDTCOfEvent(void);
      void GetDTCSuppression(void);
      void GetFaultDetectionCounter(void);
      void GetIndicatorStatus(void);
      void GetEventFreezeFrameDataEx(void);
      void GetEventExtendedDataRecordEx(void);
      void GetEventMemoryOverflow(void);
      void GetNumberOfEventMemoryEntries(void);
      void ResetEventDebounceStatus(void);
      void ResetEventStatus(void);
      void RestartOperationCycle(void);
      void PrestoreFreezeFrame(void);
      void SelectDTC(void);
      void SetComponentAvailable(void);
      void SetDTCSuppression(void);
      void SetEnableCondition(void);
      void SetEventAvailable(void);
      void SetEventFailureCycleCounterThreshold(void);
      void SetEventStatus(void);
      void SetEventStatusWithMonitorData(void);
      void SetStorageCondition(void);
      void SetWIRStatus(void);
      void GetTranslationType(void);
      void GetDTCStatusAvailabilityMask(void);
      void GetStatusOfDTC(void);
      void GetSeverityOfDTC(void);
      void GetFunctionalUnitOfDTC(void);
      void SetDTCFilter(void);
      void GetNumberOfFilteredDTC(void);
      void GetNextFilteredDTC(void);
      void GetNextFilteredDTCAndFDC(void);
      void GetNextFilteredDTCAndSeverity(void);
      void SetFreezeFrameRecordFilter(void);
      void GetNextFilteredRecord(void);
      void GetDTCByOccuranceTime(void);
};

extern class_Dem Dem;


