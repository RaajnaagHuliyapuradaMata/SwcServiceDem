#pragma once
/******************************************************************************/
/* File   : ServiceDem_core.hpp                                                      */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "CompilerCfg_ServiceDem.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define DEM_CORE_FUNCTIONALITIES                                               \
              FUNC(void,           DEM_CODE) Shutdown                             (void);     \
              FUNC(void,           DEM_CODE) ClearDTC                             (void);     \
              FUNC(void,           DEM_CODE) ClearPrestoredMcalFreezeMcalFrame            (void);     \
              FUNC(void,           DEM_CODE) GetServiceComponentFailed                   (void);     \
              FUNC(void,           DEM_CODE) GetDTCSelectionResult                (void);     \
              FUNC(void,           DEM_CODE) GetDTCSelectionResultForClearDTC     (void);     \
              FUNC(void,           DEM_CODE) GetEventUdsStatus                    (void);     \
              FUNC(void,           DEM_CODE) GetMonitorStatus                     (void);     \
              FUNC(void,           DEM_CODE) GetDebouncingOfEvent                 (void);     \
              FUNC(void,           DEM_CODE) GetDTCOfEvent                        (void);     \
              FUNC(void,           DEM_CODE) GetDTCSuppression                    (void);     \
              FUNC(void,           DEM_CODE) GetFaultServiceDetectionCounter             (void);     \
              FUNC(void,           DEM_CODE) GetIndicatorStatus                   (void);     \
              FUNC(void,           DEM_CODE) GetEventMcalFreezeMcalFrameDataEx            (void);     \
              FUNC(void,           DEM_CODE) GetEventExtendedDataRecordEx         (void);     \
              FUNC(void,           DEM_CODE) GetEventMemoryOverflow               (void);     \
              FUNC(void,           DEM_CODE) GetNumberOfEventMemoryEntries        (void);     \
              FUNC(void,           DEM_CODE) ResetEventDebounceStatus             (void);     \
              FUNC(void,           DEM_CODE) ResetEventStatus                     (void);     \
              FUNC(void,           DEM_CODE) RestartOperationCycle                (void);     \
              FUNC(void,           DEM_CODE) PrestoreMcalFreezeMcalFrame                  (void);     \
              FUNC(void,           DEM_CODE) SelectDTC                            (void);     \
              FUNC(void,           DEM_CODE) SetServiceComponentAvailable                (void);     \
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
              FUNC(void,           DEM_CODE) SetMcalFreezeMcalFrameRecordFilter           (void);     \
              FUNC(void,           DEM_CODE) GetNextFilteredRecord                (void);     \
              FUNC(void,           DEM_CODE) GetDTCByOccuranceTime                (void);     \
              FUNC(void,           DEM_CODE) DisableDTCRecordUpdate               (void);     \
              FUNC(void,           DEM_CODE) EnableDTCRecordUpdate                (void);     \
              FUNC(void,           DEM_CODE) GetSizeOfExtendedDataRecordSelection (void);     \
              FUNC(void,           DEM_CODE) GetSizeOfMcalFreezeMcalFrameSelection        (void);     \
              FUNC(void,           DEM_CODE) GetNextExtendedDataRecord            (void);     \
              FUNC(void,           DEM_CODE) GetNextMcalFreezeMcalFrameData               (void);     \
              FUNC(void,           DEM_CODE) SelectExtendedDataRecord             (void);     \
              FUNC(void,           DEM_CODE) SelectMcalFreezeMcalFrameData                (void);     \
              FUNC(void,           DEM_CODE) GetNumberOfMcalFreezeMcalFrameRecords        (void);     \
              FUNC(void,           DEM_CODE) DisableDTCSetting                    (void);     \
              FUNC(void,           DEM_CODE) EnableDTCSetting                     (void);     \
              FUNC(void,           DEM_CODE) ServiceDcmGetInfoTypeValue08                (void);     \
              FUNC(void,           DEM_CODE) ServiceDcmGetInfoTypeValue0B                (void);     \
              FUNC(void,           DEM_CODE) ServiceDcmReadDataOfPID01                   (void);     \
              FUNC(void,           DEM_CODE) ServiceDcmReadDataOfPID1C                   (void);     \
              FUNC(void,           DEM_CODE) ServiceDcmReadDataOfPID21                   (void);     \
              FUNC(void,           DEM_CODE) ServiceDcmReadDataOfPID30                   (void);     \
              FUNC(void,           DEM_CODE) ServiceDcmReadDataOfPID31                   (void);     \
              FUNC(void,           DEM_CODE) ServiceDcmReadDataOfPID41                   (void);     \
              FUNC(void,           DEM_CODE) ServiceDcmReadDataOfPID4D                   (void);     \
              FUNC(void,           DEM_CODE) ServiceDcmReadDataOfPID4E                   (void);     \
              FUNC(void,           DEM_CODE) ServiceDcmReadDataOfPID91                   (void);     \
              FUNC(void,           DEM_CODE) ServiceDcmReadDataOfOBDMcalFreezeMcalFrame          (void);     \
              FUNC(void,           DEM_CODE) ServiceDcmGetDTCOfOBDMcalFreezeMcalFrame            (void);     \
              FUNC(void,           DEM_CODE) ServiceDcmGetAvailableOBDMIDs               (void);     \
              FUNC(void,           DEM_CODE) ServiceDcmGetNumTIDsOfOBDMID                (void);     \
              FUNC(void,           DEM_CODE) ServiceDcmGetDTRData                        (void);     \
              FUNC(void,           DEM_CODE) J1939ServiceDcmSetDTCFilter                 (void);     \
              FUNC(void,           DEM_CODE) J1939ServiceDcmGetNumberOfFilteredDTC       (void);     \
              FUNC(void,           DEM_CODE) J1939ServiceDcmGetNextFilteredDTC           (void);     \
              FUNC(void,           DEM_CODE) J1939ServiceDcmFirstDTCwithLampStatus       (void);     \
              FUNC(void,           DEM_CODE) J1939ServiceDcmClearDTC                     (void);     \
              FUNC(void,           DEM_CODE) J1939ServiceDcmSetMcalFreezeMcalFrameFilter         (void);     \
              FUNC(void,           DEM_CODE) J1939ServiceDcmGetNextMcalFreezeMcalFrame           (void);     \
              FUNC(void,           DEM_CODE) J1939ServiceDcmGetNextSPNInMcalFreezeMcalFrame      (void);     \
              FUNC(void,           DEM_CODE) J1939ServiceDcmSetRatioFilter               (void);     \
              FUNC(void,           DEM_CODE) J1939ServiceDcmGetNextFilteredRatio         (void);     \
              FUNC(void,           DEM_CODE) J1939ServiceDcmReadDiagnosticReadiness1     (void);     \
              FUNC(void,           DEM_CODE) J1939ServiceDcmReadDiagnosticReadiness2     (void);     \
              FUNC(void,           DEM_CODE) J1939ServiceDcmReadDiagnosticReadiness3     (void);     \
              FUNC(void,           DEM_CODE) SetEventDisabled                     (void);     \
              FUNC(void,           DEM_CODE) RepIUMPRFaultServiceDetected                (void);     \
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

#define DEM_CORE_FUNCTIONALITIES_VIRTUAL                                       \
      virtual FUNC(void,           DEM_CODE) Shutdown                             (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ClearDTC                             (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ClearPrestoredMcalFreezeMcalFrame            (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetServiceComponentFailed                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetDTCSelectionResult                (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetDTCSelectionResultForClearDTC     (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetEventUdsStatus                    (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetMonitorStatus                     (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetDebouncingOfEvent                 (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetDTCOfEvent                        (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetDTCSuppression                    (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetFaultServiceDetectionCounter             (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetIndicatorStatus                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetEventMcalFreezeMcalFrameDataEx            (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetEventExtendedDataRecordEx         (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetEventMemoryOverflow               (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetNumberOfEventMemoryEntries        (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ResetEventDebounceStatus             (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ResetEventStatus                     (void) = 0; \
      virtual FUNC(void,           DEM_CODE) RestartOperationCycle                (void) = 0; \
      virtual FUNC(void,           DEM_CODE) PrestoreMcalFreezeMcalFrame                  (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SelectDTC                            (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SetServiceComponentAvailable                (void) = 0; \
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
      virtual FUNC(void,           DEM_CODE) SetMcalFreezeMcalFrameRecordFilter           (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetNextFilteredRecord                (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetDTCByOccuranceTime                (void) = 0; \
      virtual FUNC(void,           DEM_CODE) DisableDTCRecordUpdate               (void) = 0; \
      virtual FUNC(void,           DEM_CODE) EnableDTCRecordUpdate                (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetSizeOfExtendedDataRecordSelection (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetSizeOfMcalFreezeMcalFrameSelection        (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetNextExtendedDataRecord            (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetNextMcalFreezeMcalFrameData               (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SelectExtendedDataRecord             (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SelectMcalFreezeMcalFrameData                (void) = 0; \
      virtual FUNC(void,           DEM_CODE) GetNumberOfMcalFreezeMcalFrameRecords        (void) = 0; \
      virtual FUNC(void,           DEM_CODE) DisableDTCSetting                    (void) = 0; \
      virtual FUNC(void,           DEM_CODE) EnableDTCSetting                     (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ServiceDcmGetInfoTypeValue08                (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ServiceDcmGetInfoTypeValue0B                (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ServiceDcmReadDataOfPID01                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ServiceDcmReadDataOfPID1C                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ServiceDcmReadDataOfPID21                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ServiceDcmReadDataOfPID30                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ServiceDcmReadDataOfPID31                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ServiceDcmReadDataOfPID41                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ServiceDcmReadDataOfPID4D                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ServiceDcmReadDataOfPID4E                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ServiceDcmReadDataOfPID91                   (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ServiceDcmReadDataOfOBDMcalFreezeMcalFrame          (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ServiceDcmGetDTCOfOBDMcalFreezeMcalFrame            (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ServiceDcmGetAvailableOBDMIDs               (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ServiceDcmGetNumTIDsOfOBDMID                (void) = 0; \
      virtual FUNC(void,           DEM_CODE) ServiceDcmGetDTRData                        (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939ServiceDcmSetDTCFilter                 (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939ServiceDcmGetNumberOfFilteredDTC       (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939ServiceDcmGetNextFilteredDTC           (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939ServiceDcmFirstDTCwithLampStatus       (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939ServiceDcmClearDTC                     (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939ServiceDcmSetMcalFreezeMcalFrameFilter         (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939ServiceDcmGetNextMcalFreezeMcalFrame           (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939ServiceDcmGetNextSPNInMcalFreezeMcalFrame      (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939ServiceDcmSetRatioFilter               (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939ServiceDcmGetNextFilteredRatio         (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939ServiceDcmReadDiagnosticReadiness1     (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939ServiceDcmReadDiagnosticReadiness2     (void) = 0; \
      virtual FUNC(void,           DEM_CODE) J1939ServiceDcmReadDiagnosticReadiness3     (void) = 0; \
      virtual FUNC(void,           DEM_CODE) SetEventDisabled                     (void) = 0; \
      virtual FUNC(void,           DEM_CODE) RepIUMPRFaultServiceDetected                (void) = 0; \
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
class class_ServiceDem_Functionality{
   public:
      DEM_CORE_FUNCTIONALITIES_VIRTUAL
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

