#pragma once
/******************************************************************************/
/* File   : Dem_core.hpp                                                      */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "CompilerCfg_Dem.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define DEM_COREFUNCTIONALITIES                                                \
              FUNC(void,           DEM_CODE) Shutdown                             (void);     \
              FUNC(void,           DEM_CODE) ClearDTC                             (void);     \
              FUNC(void,           DEM_CODE) ClearPrestoredFreezeFrame            (void);     \
              FUNC(void,           DEM_CODE) GetComponentFailed                   (void);     \
              FUNC(void,           DEM_CODE) GetDTCSelectionResult                (void);     \
              FUNC(void,           DEM_CODE) GetDTCSelectionResultForClearDTC     (void);     \
              FUNC(void,           DEM_CODE) GetEventUdsStatus                    (void);     \
              FUNC(void,           DEM_CODE) GetMonitorStatus                     (void);     \
              FUNC(void,           DEM_CODE) GetDebouncingOfEvent                 (void);     \
              FUNC(void,           DEM_CODE) GetDTCOfEvent                        (void);     \
              FUNC(void,           DEM_CODE) GetDTCSuppression                    (void);     \
              FUNC(void,           DEM_CODE) GetFaultDetectionCounter             (void);     \
              FUNC(void,           DEM_CODE) GetIndicatorStatus                   (void);     \
              FUNC(void,           DEM_CODE) GetEventFreezeFrameDataEx            (void);     \
              FUNC(void,           DEM_CODE) GetEventExtendedDataRecordEx         (void);     \
              FUNC(void,           DEM_CODE) GetEventMemoryOverflow               (void);     \
              FUNC(void,           DEM_CODE) GetNumberOfEventMemoryEntries        (void);     \
              FUNC(void,           DEM_CODE) ResetEventDebounceStatus             (void);     \
              FUNC(void,           DEM_CODE) ResetEventStatus                     (void);     \
              FUNC(void,           DEM_CODE) RestartOperationCycle                (void);     \
              FUNC(void,           DEM_CODE) PrestoreFreezeFrame                  (void);     \
              FUNC(void,           DEM_CODE) SelectDTC                            (void);     \
              FUNC(void,           DEM_CODE) SetComponentAvailable                (void);     \
              FUNC(void,           DEM_CODE) SetDTCSuppression                    (void);     \
              FUNC(void,           DEM_CODE) SetEnableCondition                   (void);     \
              FUNC(void,           DEM_CODE) SetEventAvailable                    (void);     \
              FUNC(void,           DEM_CODE) SetEventFailureCycleCounterThreshold (void);     \
              FUNC(Std_TypeReturn, DEM_CODE) SetEventStatus                       (void);     \
              FUNC(void,           DEM_CODE) SetEventStatusWithMonitorData        (void);     \
              FUNC(void,           DEM_CODE) SetStorageCondition                  (void);     \
              FUNC(void,           DEM_CODE) SetWIRStatus                         (void);     \
              FUNC(void,           DEM_CODE) GetTranslationType                   (void);     \
              FUNC(void,           DEM_CODE) GetDTCStatusAvailabilityMask         (void);     \
              FUNC(void,           DEM_CODE) GetStatusOfDTC                       (void);     \
              FUNC(void,           DEM_CODE) GetSeverityOfDTC                     (void);     \
              FUNC(void,           DEM_CODE) GetFunctionalUnitOfDTC               (void);     \
              FUNC(void,           DEM_CODE) SetDTCFilter                         (void);     \
              FUNC(void,           DEM_CODE) GetNumberOfFilteredDTC               (void);     \
              FUNC(void,           DEM_CODE) GetNextFilteredDTC                   (void);     \
              FUNC(void,           DEM_CODE) GetNextFilteredDTCAndFDC             (void);     \
              FUNC(void,           DEM_CODE) GetNextFilteredDTCAndSeverity        (void);     \
              FUNC(void,           DEM_CODE) SetFreezeFrameRecordFilter           (void);     \
              FUNC(void,           DEM_CODE) GetNextFilteredRecord                (void);     \
              FUNC(void,           DEM_CODE) GetDTCByOccuranceTime                (void);     \
              FUNC(void,           DEM_CODE) DisableDTCRecordUpdate               (void);     \
              FUNC(void,           DEM_CODE) EnableDTCRecordUpdate                (void);     \
              FUNC(void,           DEM_CODE) GetSizeOfExtendedDataRecordSelection (void);     \
              FUNC(void,           DEM_CODE) GetSizeOfFreezeFrameSelection        (void);     \
              FUNC(void,           DEM_CODE) GetNextExtendedDataRecord            (void);     \
              FUNC(void,           DEM_CODE) GetNextFreezeFrameData               (void);     \
              FUNC(void,           DEM_CODE) SelectExtendedDataRecord             (void);     \
              FUNC(void,           DEM_CODE) SelectFreezeFrameData                (void);     \
              FUNC(void,           DEM_CODE) GetNumberOfFreezeFrameRecords        (void);     \
              FUNC(void,           DEM_CODE) DisableDTCSetting                    (void);     \
              FUNC(void,           DEM_CODE) EnableDTCSetting                     (void);     \
              FUNC(void,           DEM_CODE) DcmGetInfoTypeValue08                (void);     \
              FUNC(void,           DEM_CODE) DcmGetInfoTypeValue0B                (void);     \
              FUNC(void,           DEM_CODE) DcmReadDataOfPID01                   (void);     \
              FUNC(void,           DEM_CODE) DcmReadDataOfPID1C                   (void);     \
              FUNC(void,           DEM_CODE) DcmReadDataOfPID21                   (void);     \
              FUNC(void,           DEM_CODE) DcmReadDataOfPID30                   (void);     \
              FUNC(void,           DEM_CODE) DcmReadDataOfPID31                   (void);     \
              FUNC(void,           DEM_CODE) DcmReadDataOfPID41                   (void);     \
              FUNC(void,           DEM_CODE) DcmReadDataOfPID4D                   (void);     \
              FUNC(void,           DEM_CODE) DcmReadDataOfPID4E                   (void);     \
              FUNC(void,           DEM_CODE) DcmReadDataOfPID91                   (void);     \
              FUNC(void,           DEM_CODE) DcmReadDataOfOBDFreezeFrame          (void);     \
              FUNC(void,           DEM_CODE) DcmGetDTCOfOBDFreezeFrame            (void);     \
              FUNC(void,           DEM_CODE) DcmGetAvailableOBDMIDs               (void);     \
              FUNC(void,           DEM_CODE) DcmGetNumTIDsOfOBDMID                (void);     \
              FUNC(void,           DEM_CODE) DcmGetDTRData                        (void);     \
              FUNC(void,           DEM_CODE) J1939DcmSetDTCFilter                 (void);     \
              FUNC(void,           DEM_CODE) J1939DcmGetNumberOfFilteredDTC       (void);     \
              FUNC(void,           DEM_CODE) J1939DcmGetNextFilteredDTC           (void);     \
              FUNC(void,           DEM_CODE) J1939DcmFirstDTCwithLampStatus       (void);     \
              FUNC(void,           DEM_CODE) J1939DcmClearDTC                     (void);     \
              FUNC(void,           DEM_CODE) J1939DcmSetFreezeFrameFilter         (void);     \
              FUNC(void,           DEM_CODE) J1939DcmGetNextFreezeFrame           (void);     \
              FUNC(void,           DEM_CODE) J1939DcmGetNextSPNInFreezeFrame      (void);     \
              FUNC(void,           DEM_CODE) J1939DcmSetRatioFilter               (void);     \
              FUNC(void,           DEM_CODE) J1939DcmGetNextFilteredRatio         (void);     \
              FUNC(void,           DEM_CODE) J1939DcmReadDiagnosticReadiness1     (void);     \
              FUNC(void,           DEM_CODE) J1939DcmReadDiagnosticReadiness2     (void);     \
              FUNC(void,           DEM_CODE) J1939DcmReadDiagnosticReadiness3     (void);     \
              FUNC(void,           DEM_CODE) SetEventDisabled                     (void);     \
              FUNC(void,           DEM_CODE) RepIUMPRFaultDetected                (void);     \
              FUNC(void,           DEM_CODE) SetIUMPRDenCondition                 (void);     \
              FUNC(void,           DEM_CODE) GetIUMPRDenCondition                 (void);     \
              FUNC(void,           DEM_CODE) RepIUMPRDenRelease                   (void);     \
              FUNC(void,           DEM_CODE) SetPtoStatus                         (void);     \
              FUNC(void,           DEM_CODE) ReadDataPID01                        (void);     \
              FUNC(void,           DEM_CODE) GetDataOfPID21                       (void);     \
              FUNC(void,           DEM_CODE) SetDataOfPID21                       (void);     \
              FUNC(void,           DEM_CODE) SetDataOfPID31                       (void);     \
              FUNC(void,           DEM_CODE) SetDataOfPID4D                       (void);     \
              FUNC(void,           DEM_CODE) SetDataOfPID4E                       (void);     \
              FUNC(void,           DEM_CODE) GetCycleQualified                    (void);     \
              FUNC(void,           DEM_CODE) SetCycleQualified                    (void);     \
              FUNC(void,           DEM_CODE) GetDTCSeverityAvailabilityMask       (void);     \
              FUNC(void,           DEM_CODE) GetB1Counter                         (void);     \
              FUNC(void,           DEM_CODE) SetDTR                               (void);     \

#define DEM_COREFUNCTIONALITIES_VIRTUAL                                        \
      virtual FUNC(void,           DEM_CODE) Shutdown                             (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ClearDTC                             (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ClearPrestoredFreezeFrame            (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetComponentFailed                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetDTCSelectionResult                (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetDTCSelectionResultForClearDTC     (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetEventUdsStatus                    (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetMonitorStatus                     (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetDebouncingOfEvent                 (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetDTCOfEvent                        (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetDTCSuppression                    (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetFaultDetectionCounter             (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetIndicatorStatus                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetEventFreezeFrameDataEx            (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetEventExtendedDataRecordEx         (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetEventMemoryOverflow               (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetNumberOfEventMemoryEntries        (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ResetEventDebounceStatus             (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ResetEventStatus                     (void) = 0; \
      virtual FUNC(void,           DEM_CODE) RestartOperationCycle                (void) = 0; \
      virtual FUNC(void,           DEM_CODE) PrestoreFreezeFrame                  (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SelectDTC                            (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SetComponentAvailable                (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SetDTCSuppression                    (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SetEnableCondition                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SetEventAvailable                    (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SetEventFailureCycleCounterThreshold (void) = 0; \
      virtual FUNC(Std_TypeReturn, DEM_CODE) SetEventStatus                       (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SetEventStatusWithMonitorData        (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SetStorageCondition                  (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SetWIRStatus                         (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetTranslationType                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetDTCStatusAvailabilityMask         (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetStatusOfDTC                       (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetSeverityOfDTC                     (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetFunctionalUnitOfDTC               (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SetDTCFilter                         (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetNumberOfFilteredDTC               (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetNextFilteredDTC                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetNextFilteredDTCAndFDC             (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetNextFilteredDTCAndSeverity        (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SetFreezeFrameRecordFilter           (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetNextFilteredRecord                (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetDTCByOccuranceTime                (void) = 0; \
      virtual FUNC(void,           DEM_CODE) DisableDTCRecordUpdate               (void) = 0; \
      virtual FUNC(void,           DEM_CODE) EnableDTCRecordUpdate                (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetSizeOfExtendedDataRecordSelection (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetSizeOfFreezeFrameSelection        (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetNextExtendedDataRecord            (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetNextFreezeFrameData               (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SelectExtendedDataRecord             (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SelectFreezeFrameData                (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetNumberOfFreezeFrameRecords        (void) = 0; \
      virtual FUNC(void,           DEM_CODE) DisableDTCSetting                    (void) = 0; \
      virtual FUNC(void,           DEM_CODE) EnableDTCSetting                     (void) = 0; \
      virtual FUNC(void,           DEM_CODE) DcmGetInfoTypeValue08                (void) = 0; \
      virtual FUNC(void,           DEM_CODE) DcmGetInfoTypeValue0B                (void) = 0; \
      virtual FUNC(void,           DEM_CODE) DcmReadDataOfPID01                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) DcmReadDataOfPID1C                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) DcmReadDataOfPID21                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) DcmReadDataOfPID30                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) DcmReadDataOfPID31                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) DcmReadDataOfPID41                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) DcmReadDataOfPID4D                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) DcmReadDataOfPID4E                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) DcmReadDataOfPID91                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) DcmReadDataOfOBDFreezeFrame          (void) = 0; \
      virtual FUNC(void,           DEM_CODE) DcmGetDTCOfOBDFreezeFrame            (void) = 0; \
      virtual FUNC(void,           DEM_CODE) DcmGetAvailableOBDMIDs               (void) = 0; \
      virtual FUNC(void,           DEM_CODE) DcmGetNumTIDsOfOBDMID                (void) = 0; \
      virtual FUNC(void,           DEM_CODE) DcmGetDTRData                        (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939DcmSetDTCFilter                 (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939DcmGetNumberOfFilteredDTC       (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939DcmGetNextFilteredDTC           (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939DcmFirstDTCwithLampStatus       (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939DcmClearDTC                     (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939DcmSetFreezeFrameFilter         (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939DcmGetNextFreezeFrame           (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939DcmGetNextSPNInFreezeFrame      (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939DcmSetRatioFilter               (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939DcmGetNextFilteredRatio         (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939DcmReadDiagnosticReadiness1     (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939DcmReadDiagnosticReadiness2     (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939DcmReadDiagnosticReadiness3     (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SetEventDisabled                     (void) = 0; \
      virtual FUNC(void,           DEM_CODE) RepIUMPRFaultDetected                (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SetIUMPRDenCondition                 (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetIUMPRDenCondition                 (void) = 0; \
      virtual FUNC(void,           DEM_CODE) RepIUMPRDenRelease                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SetPtoStatus                         (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ReadDataPID01                        (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetDataOfPID21                       (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SetDataOfPID21                       (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SetDataOfPID31                       (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SetDataOfPID4D                       (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SetDataOfPID4E                       (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetCycleQualified                    (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SetCycleQualified                    (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetDTCSeverityAvailabilityMask       (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetB1Counter                         (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SetDTR                               (void) = 0; \

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class class_Dem_Functionality{
   public:
      DEM_COREFUNCTIONALITIES_VIRTUAL
};

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

