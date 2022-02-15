#pragma once
/*****************************************************/
/* File   : Dem_Unused.h                             */
/* Author : Naagraaj HM                              */
/*****************************************************/

/*****************************************************/
/* #INCLUDES                                         */
/*****************************************************/
#include "Std_Types.h"
#include "Compiler_Cfg_Dem.h"

/*****************************************************/
/* TYPEDEFS                                          */
/*****************************************************/
class class_Dem_Unused{
   public:
/*****************************************************/
/* FUNCTIONS                                         */
/*****************************************************/
      FUNC(void, DEM_CODE) GetVersionInfo(void);
      FUNC(void, DEM_CODE) Shutdown(void);
      FUNC(void, DEM_CODE) ClearDTC(void);
      FUNC(void, DEM_CODE) ClearPrestoredFreezeFrame(void);
      FUNC(void, DEM_CODE) GetComponentFailed(void);
      FUNC(void, DEM_CODE) GetDTCSelectionResult(void);
      FUNC(void, DEM_CODE) GetDTCSelectionResultForClearDTC(void);
      FUNC(void, DEM_CODE) GetEventUdsStatus(void);
      FUNC(void, DEM_CODE) GetMonitorStatus(void);
      FUNC(void, DEM_CODE) GetDebouncingOfEvent(void);
      FUNC(void, DEM_CODE) GetDTCOfEvent(void);
      FUNC(void, DEM_CODE) GetDTCSuppression(void);
      FUNC(void, DEM_CODE) GetFaultDetectionCounter(void);
      FUNC(void, DEM_CODE) GetIndicatorStatus(void);
      FUNC(void, DEM_CODE) GetEventFreezeFrameDataEx(void);
      FUNC(void, DEM_CODE) GetEventExtendedDataRecordEx(void);
      FUNC(void, DEM_CODE) GetEventMemoryOverflow(void);
      FUNC(void, DEM_CODE) GetNumberOfEventMemoryEntries(void);
      FUNC(void, DEM_CODE) ResetEventDebounceStatus(void);
      FUNC(void, DEM_CODE) ResetEventStatus(void);
      FUNC(void, DEM_CODE) RestartOperationCycle(void);
      FUNC(void, DEM_CODE) PrestoreFreezeFrame(void);
      FUNC(void, DEM_CODE) SelectDTC(void);
      FUNC(void, DEM_CODE) SetComponentAvailable(void);
      FUNC(void, DEM_CODE) SetDTCSuppression(void);
      FUNC(void, DEM_CODE) SetEnableCondition(void);
      FUNC(void, DEM_CODE) SetEventAvailable(void);
      FUNC(void, DEM_CODE) SetEventFailureCycleCounterThreshold(void);
      FUNC(void, DEM_CODE) SetEventStatus(void);
      FUNC(void, DEM_CODE) SetEventStatusWithMonitorData(void);
      FUNC(void, DEM_CODE) SetStorageCondition(void);
      FUNC(void, DEM_CODE) SetWIRStatus(void);
      FUNC(void, DEM_CODE) GetTranslationType(void);
      FUNC(void, DEM_CODE) GetDTCStatusAvailabilityMask(void);
      FUNC(void, DEM_CODE) GetStatusOfDTC(void);
      FUNC(void, DEM_CODE) GetSeverityOfDTC(void);
      FUNC(void, DEM_CODE) GetFunctionalUnitOfDTC(void);
      FUNC(void, DEM_CODE) SetDTCFilter(void);
      FUNC(void, DEM_CODE) GetNumberOfFilteredDTC(void);
      FUNC(void, DEM_CODE) GetNextFilteredDTC(void);
      FUNC(void, DEM_CODE) GetNextFilteredDTCAndFDC(void);
      FUNC(void, DEM_CODE) GetNextFilteredDTCAndSeverity(void);
      FUNC(void, DEM_CODE) SetFreezeFrameRecordFilter(void);
      FUNC(void, DEM_CODE) GetNextFilteredRecord(void);
      FUNC(void, DEM_CODE) GetDTCByOccuranceTime(void);
      FUNC(void, DEM_CODE) DisableDTCRecordUpdate(void);
      FUNC(void, DEM_CODE) EnableDTCRecordUpdate(void);
      FUNC(void, DEM_CODE) GetSizeOfExtendedDataRecordSelection(void);
      FUNC(void, DEM_CODE) GetSizeOfFreezeFrameSelection(void);
      FUNC(void, DEM_CODE) GetNextExtendedDataRecord(void);
      FUNC(void, DEM_CODE) GetNextFreezeFrameData(void);
      FUNC(void, DEM_CODE) SelectExtendedDataRecord(void);
      FUNC(void, DEM_CODE) SelectFreezeFrameData(void);
      FUNC(void, DEM_CODE) GetNumberOfFreezeFrameRecords(void);
      FUNC(void, DEM_CODE) DisableDTCSetting(void);
      FUNC(void, DEM_CODE) EnableDTCSetting(void);
      FUNC(void, DEM_CODE) DcmGetInfoTypeValue08(void);
      FUNC(void, DEM_CODE) DcmGetInfoTypeValue0B(void);
      FUNC(void, DEM_CODE) DcmReadDataOfPID01(void);
      FUNC(void, DEM_CODE) DcmReadDataOfPID1C(void);
      FUNC(void, DEM_CODE) DcmReadDataOfPID21(void);
      FUNC(void, DEM_CODE) DcmReadDataOfPID30(void);
      FUNC(void, DEM_CODE) DcmReadDataOfPID31(void);
      FUNC(void, DEM_CODE) DcmReadDataOfPID41(void);
      FUNC(void, DEM_CODE) DcmReadDataOfPID4D(void);
      FUNC(void, DEM_CODE) DcmReadDataOfPID4E(void);
      FUNC(void, DEM_CODE) DcmReadDataOfPID91(void);
      FUNC(void, DEM_CODE) DcmReadDataOfOBDFreezeFrame(void);
      FUNC(void, DEM_CODE) DcmGetDTCOfOBDFreezeFrame(void);
      FUNC(void, DEM_CODE) DcmGetAvailableOBDMIDs(void);
      FUNC(void, DEM_CODE) DcmGetNumTIDsOfOBDMID(void);
      FUNC(void, DEM_CODE) DcmGetDTRData(void);
      FUNC(void, DEM_CODE) J1939DcmSetDTCFilter(void);
      FUNC(void, DEM_CODE) J1939DcmGetNumberOfFilteredDTC(void);
      FUNC(void, DEM_CODE) J1939DcmGetNextFilteredDTC(void);
      FUNC(void, DEM_CODE) J1939DcmFirstDTCwithLampStatus(void);
      FUNC(void, DEM_CODE) J1939DcmClearDTC(void);
      FUNC(void, DEM_CODE) J1939DcmSetFreezeFrameFilter(void);
      FUNC(void, DEM_CODE) J1939DcmGetNextFreezeFrame(void);
      FUNC(void, DEM_CODE) J1939DcmGetNextSPNInFreezeFrame(void);
      FUNC(void, DEM_CODE) J1939DcmSetRatioFilter(void);
      FUNC(void, DEM_CODE) J1939DcmGetNextFilteredRatio(void);
      FUNC(void, DEM_CODE) J1939DcmReadDiagnosticReadiness1(void);
      FUNC(void, DEM_CODE) J1939DcmReadDiagnosticReadiness2(void);
      FUNC(void, DEM_CODE) J1939DcmReadDiagnosticReadiness3(void);
      FUNC(void, DEM_CODE) SetEventDisabled(void);
      FUNC(void, DEM_CODE) RepIUMPRFaultDetected(void);
      FUNC(void, DEM_CODE) SetIUMPRDenCondition(void);
      FUNC(void, DEM_CODE) GetIUMPRDenCondition(void);
      FUNC(void, DEM_CODE) RepIUMPRDenRelease(void);
      FUNC(void, DEM_CODE) SetPtoStatus(void);
      FUNC(void, DEM_CODE) ReadDataPID01(void);
      FUNC(void, DEM_CODE) GetDataOfPID21(void);
      FUNC(void, DEM_CODE) SetDataOfPID21(void);
      FUNC(void, DEM_CODE) SetDataOfPID31(void);
      FUNC(void, DEM_CODE) SetDataOfPID4D(void);
      FUNC(void, DEM_CODE) SetDataOfPID4E(void);
      FUNC(void, DEM_CODE) GetCycleQualified(void);
      FUNC(void, DEM_CODE) SetCycleQualified(void);
      FUNC(void, DEM_CODE) GetDTCSeverityAvailabilityMask(void);
      FUNC(void, DEM_CODE) GetB1Counter(void);
      FUNC(void, DEM_CODE) SetDTR(void);
};

/*****************************************************/
/* OBJECTS                                           */
/*****************************************************/
//extern class_Dem Dem;

/*****************************************************/
/* EOF                                               */
/*****************************************************/

