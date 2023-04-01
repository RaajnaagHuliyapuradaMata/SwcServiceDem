#pragma once
/******************************************************************************/
/* File   : ServiceDem_core.hpp                                                      */
/*                                                                            */
/* Author : Nagaraja HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Nagaraja HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/NagarajaHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "CompilerCfg_ServiceDem.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define SERVICEDEM_CORE_FUNCTIONALITIES                                               \
              FUNC(void,           SERVICEDEM_CODE) Shutdown                             (void);     \
              FUNC(void,           SERVICEDEM_CODE) ClearDTC                             (void);     \
              FUNC(void,           SERVICEDEM_CODE) ClearPrestoredMcalFreezeMcalFrame            (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetServiceComponentFailed                   (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetDTCSelectionResult                (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetDTCSelectionResultForClearDTC     (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetEventUdsStatus                    (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetMonitorStatus                     (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetDebouncingOfEvent                 (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetDTCOfEvent                        (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetDTCSuppression                    (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetFaultServiceDetectionCounter             (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetIndicatorStatus                   (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetEventMcalFreezeMcalFrameDataEx            (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetEventExtendedDataRecordEx         (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetEventMemoryOverflow               (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetNumberOfEventMemoryEntries        (void);     \
              FUNC(void,           SERVICEDEM_CODE) ResetEventDebounceStatus             (void);     \
              FUNC(void,           SERVICEDEM_CODE) ResetEventStatus                     (void);     \
              FUNC(void,           SERVICEDEM_CODE) RestartOperationCycle                (void);     \
              FUNC(void,           SERVICEDEM_CODE) PrestoreMcalFreezeMcalFrame                  (void);     \
              FUNC(void,           SERVICEDEM_CODE) SelectDTC                            (void);     \
              FUNC(void,           SERVICEDEM_CODE) SetServiceComponentAvailable                (void);     \
              FUNC(void,           SERVICEDEM_CODE) SetDTCSuppression                    (void);     \
              FUNC(void,           SERVICEDEM_CODE) SetEnableCondition                   (void);     \
              FUNC(void,           SERVICEDEM_CODE) SetEventAvailable                    (void);     \
              FUNC(void,           SERVICEDEM_CODE) SetEventFailureCycleCounterThreshold (void);     \
              FUNC(Std_TypeReturn, SERVICEDEM_CODE) SetEventStatus                       (void);     \
              FUNC(void,           SERVICEDEM_CODE) SetEventStatusWithMonitorData        (void);     \
              FUNC(void,           SERVICEDEM_CODE) SetStorageCondition                  (void);     \
              FUNC(void,           SERVICEDEM_CODE) SetWIRStatus                         (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetTranslationType                   (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetDTCStatusAvailabilityMask         (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetStatusOfDTC                       (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetSeverityOfDTC                     (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetFunctionalUnitOfDTC               (void);     \
              FUNC(void,           SERVICEDEM_CODE) SetDTCFilter                         (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetNumberOfFilteredDTC               (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetNextFilteredDTC                   (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetNextFilteredDTCAndFDC             (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetNextFilteredDTCAndSeverity        (void);     \
              FUNC(void,           SERVICEDEM_CODE) SetMcalFreezeMcalFrameRecordFilter           (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetNextFilteredRecord                (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetDTCByOccuranceTime                (void);     \
              FUNC(void,           SERVICEDEM_CODE) DisableDTCRecordUpdate               (void);     \
              FUNC(void,           SERVICEDEM_CODE) EnableDTCRecordUpdate                (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetSizeOfExtendedDataRecordSelection (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetSizeOfMcalFreezeMcalFrameSelection        (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetNextExtendedDataRecord            (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetNextMcalFreezeMcalFrameData               (void);     \
              FUNC(void,           SERVICEDEM_CODE) SelectExtendedDataRecord             (void);     \
              FUNC(void,           SERVICEDEM_CODE) SelectMcalFreezeMcalFrameData                (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetNumberOfMcalFreezeMcalFrameRecords        (void);     \
              FUNC(void,           SERVICEDEM_CODE) DisableDTCSetting                    (void);     \
              FUNC(void,           SERVICEDEM_CODE) EnableDTCSetting                     (void);     \
              FUNC(void,           SERVICEDEM_CODE) ServiceDcmGetInfoTypeValue08                (void);     \
              FUNC(void,           SERVICEDEM_CODE) ServiceDcmGetInfoTypeValue0B                (void);     \
              FUNC(void,           SERVICEDEM_CODE) ServiceDcmReadDataOfPID01                   (void);     \
              FUNC(void,           SERVICEDEM_CODE) ServiceDcmReadDataOfPID1C                   (void);     \
              FUNC(void,           SERVICEDEM_CODE) ServiceDcmReadDataOfPID21                   (void);     \
              FUNC(void,           SERVICEDEM_CODE) ServiceDcmReadDataOfPID30                   (void);     \
              FUNC(void,           SERVICEDEM_CODE) ServiceDcmReadDataOfPID31                   (void);     \
              FUNC(void,           SERVICEDEM_CODE) ServiceDcmReadDataOfPID41                   (void);     \
              FUNC(void,           SERVICEDEM_CODE) ServiceDcmReadDataOfPID4D                   (void);     \
              FUNC(void,           SERVICEDEM_CODE) ServiceDcmReadDataOfPID4E                   (void);     \
              FUNC(void,           SERVICEDEM_CODE) ServiceDcmReadDataOfPID91                   (void);     \
              FUNC(void,           SERVICEDEM_CODE) ServiceDcmReadDataOfOBDMcalFreezeMcalFrame          (void);     \
              FUNC(void,           SERVICEDEM_CODE) ServiceDcmGetDTCOfOBDMcalFreezeMcalFrame            (void);     \
              FUNC(void,           SERVICEDEM_CODE) ServiceDcmGetAvailableOBDMIDs               (void);     \
              FUNC(void,           SERVICEDEM_CODE) ServiceDcmGetNumTIDsOfOBDMID                (void);     \
              FUNC(void,           SERVICEDEM_CODE) ServiceDcmGetDTRData                        (void);     \
              FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmSetDTCFilter                 (void);     \
              FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmGetNumberOfFilteredDTC       (void);     \
              FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmGetNextFilteredDTC           (void);     \
              FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmFirstDTCwithLampStatus       (void);     \
              FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmClearDTC                     (void);     \
              FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmSetMcalFreezeMcalFrameFilter         (void);     \
              FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmGetNextMcalFreezeMcalFrame           (void);     \
              FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmGetNextSPNInMcalFreezeMcalFrame      (void);     \
              FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmSetRatioFilter               (void);     \
              FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmGetNextFilteredRatio         (void);     \
              FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmReadDiagnosticReadiness1     (void);     \
              FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmReadDiagnosticReadiness2     (void);     \
              FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmReadDiagnosticReadiness3     (void);     \
              FUNC(void,           SERVICEDEM_CODE) SetEventDisabled                     (void);     \
              FUNC(void,           SERVICEDEM_CODE) RepIUMPRFaultServiceDetected                (void);     \
              FUNC(void,           SERVICEDEM_CODE) SetIUMPRDenCondition                 (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetIUMPRDenCondition                 (void);     \
              FUNC(void,           SERVICEDEM_CODE) RepIUMPRDenRelease                   (void);     \
              FUNC(void,           SERVICEDEM_CODE) SetPtoStatus                         (void);     \
              FUNC(void,           SERVICEDEM_CODE) ReadDataPID01                        (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetDataOfPID21                       (void);     \
              FUNC(void,           SERVICEDEM_CODE) SetDataOfPID21                       (void);     \
              FUNC(void,           SERVICEDEM_CODE) SetDataOfPID31                       (void);     \
              FUNC(void,           SERVICEDEM_CODE) SetDataOfPID4D                       (void);     \
              FUNC(void,           SERVICEDEM_CODE) SetDataOfPID4E                       (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetCycleQualified                    (void);     \
              FUNC(void,           SERVICEDEM_CODE) SetCycleQualified                    (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetDTCSeverityAvailabilityMask       (void);     \
              FUNC(void,           SERVICEDEM_CODE) GetB1Counter                         (void);     \
              FUNC(void,           SERVICEDEM_CODE) SetDTR                               (void);     \

#define SERVICEDEM_CORE_FUNCTIONALITIES_VIRTUAL                                       \
      virtual FUNC(void,           SERVICEDEM_CODE) Shutdown                             (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) ClearDTC                             (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) ClearPrestoredMcalFreezeMcalFrame            (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetServiceComponentFailed                   (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetDTCSelectionResult                (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetDTCSelectionResultForClearDTC     (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetEventUdsStatus                    (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetMonitorStatus                     (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetDebouncingOfEvent                 (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetDTCOfEvent                        (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetDTCSuppression                    (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetFaultServiceDetectionCounter             (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetIndicatorStatus                   (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetEventMcalFreezeMcalFrameDataEx            (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetEventExtendedDataRecordEx         (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetEventMemoryOverflow               (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetNumberOfEventMemoryEntries        (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) ResetEventDebounceStatus             (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) ResetEventStatus                     (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) RestartOperationCycle                (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) PrestoreMcalFreezeMcalFrame                  (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SelectDTC                            (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SetServiceComponentAvailable                (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SetDTCSuppression                    (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SetEnableCondition                   (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SetEventAvailable                    (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SetEventFailureCycleCounterThreshold (void) = 0; \
      virtual FUNC(Std_TypeReturn, SERVICEDEM_CODE) SetEventStatus                       (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SetEventStatusWithMonitorData        (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SetStorageCondition                  (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SetWIRStatus                         (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetTranslationType                   (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetDTCStatusAvailabilityMask         (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetStatusOfDTC                       (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetSeverityOfDTC                     (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetFunctionalUnitOfDTC               (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SetDTCFilter                         (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetNumberOfFilteredDTC               (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetNextFilteredDTC                   (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetNextFilteredDTCAndFDC             (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetNextFilteredDTCAndSeverity        (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SetMcalFreezeMcalFrameRecordFilter           (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetNextFilteredRecord                (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetDTCByOccuranceTime                (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) DisableDTCRecordUpdate               (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) EnableDTCRecordUpdate                (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetSizeOfExtendedDataRecordSelection (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetSizeOfMcalFreezeMcalFrameSelection        (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetNextExtendedDataRecord            (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetNextMcalFreezeMcalFrameData               (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SelectExtendedDataRecord             (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SelectMcalFreezeMcalFrameData                (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetNumberOfMcalFreezeMcalFrameRecords        (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) DisableDTCSetting                    (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) EnableDTCSetting                     (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) ServiceDcmGetInfoTypeValue08                (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) ServiceDcmGetInfoTypeValue0B                (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) ServiceDcmReadDataOfPID01                   (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) ServiceDcmReadDataOfPID1C                   (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) ServiceDcmReadDataOfPID21                   (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) ServiceDcmReadDataOfPID30                   (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) ServiceDcmReadDataOfPID31                   (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) ServiceDcmReadDataOfPID41                   (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) ServiceDcmReadDataOfPID4D                   (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) ServiceDcmReadDataOfPID4E                   (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) ServiceDcmReadDataOfPID91                   (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) ServiceDcmReadDataOfOBDMcalFreezeMcalFrame          (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) ServiceDcmGetDTCOfOBDMcalFreezeMcalFrame            (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) ServiceDcmGetAvailableOBDMIDs               (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) ServiceDcmGetNumTIDsOfOBDMID                (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) ServiceDcmGetDTRData                        (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmSetDTCFilter                 (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmGetNumberOfFilteredDTC       (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmGetNextFilteredDTC           (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmFirstDTCwithLampStatus       (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmClearDTC                     (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmSetMcalFreezeMcalFrameFilter         (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmGetNextMcalFreezeMcalFrame           (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmGetNextSPNInMcalFreezeMcalFrame      (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmSetRatioFilter               (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmGetNextFilteredRatio         (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmReadDiagnosticReadiness1     (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmReadDiagnosticReadiness2     (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) J1939ServiceDcmReadDiagnosticReadiness3     (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SetEventDisabled                     (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) RepIUMPRFaultServiceDetected                (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SetIUMPRDenCondition                 (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetIUMPRDenCondition                 (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) RepIUMPRDenRelease                   (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SetPtoStatus                         (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) ReadDataPID01                        (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetDataOfPID21                       (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SetDataOfPID21                       (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SetDataOfPID31                       (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SetDataOfPID4D                       (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SetDataOfPID4E                       (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetCycleQualified                    (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SetCycleQualified                    (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetDTCSeverityAvailabilityMask       (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) GetB1Counter                         (void) = 0; \
      virtual FUNC(void,           SERVICEDEM_CODE) SetDTR                               (void) = 0; \

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class class_ServiceDem_Functionality{
   public:
      SERVICEDEM_CORE_FUNCTIONALITIES_VIRTUAL
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

