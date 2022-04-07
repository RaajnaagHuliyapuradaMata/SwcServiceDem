/******************************************************************************/
/* File   : Dem.cpp                                                           */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Module.hpp"
#include "infDem_EcuM.hpp"
#include "infDem_Dcm.hpp"
#include "infDem_SchM.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define DEM_AR_RELEASE_VERSION_MAJOR                                           4
#define DEM_AR_RELEASE_VERSION_MINOR                                           3

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#if(DEM_AR_RELEASE_VERSION_MAJOR != STD_AR_RELEASE_VERSION_MAJOR)
   #error "Incompatible DEM_AR_RELEASE_VERSION_MAJOR!"
#endif

#if(DEM_AR_RELEASE_VERSION_MINOR != STD_AR_RELEASE_VERSION_MINOR)
   #error "Incompatible DEM_AR_RELEASE_VERSION_MINOR!"
#endif

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class module_Dem:
      public abstract_module
   ,  public infDem_EcuM
{
   public:
      module_Dem(Std_TypeVersionInfo lVersionInfo) : abstract_module(lVersionInfo){
      }
      FUNC(void, DEM_CODE) InitFunction(
         CONSTP2CONST(CfgModule_TypeAbstract, DEM_CONFIG_DATA, DEM_APPL_CONST) lptrCfgModule
      );
      FUNC(void, DEM_CODE) DeInitFunction (void);
      FUNC(void, DEM_CODE) MainFunction   (void);

      FUNC(void, DEM_CODE) PreInit        (void);
};

extern VAR(module_Dem, DEM_VAR) Dem;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
CONSTP2VAR(infEcuMClient, DEM_VAR, DEM_CONST) gptrinfEcuMClient_Dem = &Dem;
CONSTP2VAR(infDcmClient,  DEM_VAR, DEM_CONST) gptrinfDcmClient_Dem  = &Dem;
CONSTP2VAR(infSchMClient, DEM_VAR, DEM_CONST) gptrinfSchMClient_Dem = &Dem;
CONSTP2VAR(infDem_EcuM,   DEM_VAR, DEM_CONST) gptrinfDem_EcuM       = &Dem;

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/
#include "CfgDem.hpp"

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
VAR(module_Dem, DEM_VAR) Dem(
   {
         DEM_AR_RELEASE_VERSION_MAJOR
      ,  DEM_AR_RELEASE_VERSION_MINOR
      ,  0x00
      ,  0xFF
      ,  0x01
      ,  '0'
      ,  '1'
      ,  '0'
   }
);

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, DEM_CODE) module_Dem::InitFunction(
   CONSTP2CONST(CfgModule_TypeAbstract, DEM_CONFIG_DATA, DEM_APPL_CONST) lptrCfgModule
){
#if(STD_ON == Dem_InitCheck)
   if(E_OK == IsInitDone){
#if(STD_ON == Dem_DevErrorDetect)
      Det_ReportError(
      );
#endif
   }
   else{
#endif
      if(NULL_PTR == lptrCfgModule){
#if(STD_ON == Dem_DevErrorDetect)
         Det_ReportError(
         );
#endif
      }
      else{
         if(STD_LOW){
// check lptrCfgModule for memory faults
            lptrCfg = lptrCfgModule;
         }
         else{
// use PBcfgCanIf as back-up configuration
            lptrCfg = &PBcfgDem;
         }
      }
      IsInitDone = E_OK;
#if(STD_ON == Dem_InitCheck)
   }
#endif
}

FUNC(void, DEM_CODE) module_Dem::DeInitFunction(void){
#if(STD_ON == Dem_InitCheck)
   if(E_OK != IsInitDone){
#if(STD_ON == Dem_DevErrorDetect)
      Det_ReportError(
      );
#endif
   }
   else{
#endif
      IsInitDone = E_NOT_OK;
#if(STD_ON == Dem_InitCheck)
   }
#endif
}

FUNC(void, DEM_CODE) module_Dem::MainFunction(void){
#if(STD_ON == Dem_InitCheck)
   if(E_OK != IsInitDone){
#if(STD_ON == Dem_DevErrorDetect)
      Det_ReportError(
      );
#endif
   }
   else{
#endif
#if(STD_ON == Dem_InitCheck)
   }
#endif
}

FUNC(void, DEM_CODE) module_Dem::PreInit(void){
}

class class_Dem_Unused{
   public:
      FUNC(void,           DEM_CODE) Shutdown                             (void);
      FUNC(void,           DEM_CODE) ClearDTC                             (void);
      FUNC(void,           DEM_CODE) ClearPrestoredFreezeFrame            (void);
      FUNC(void,           DEM_CODE) GetComponentFailed                   (void);
      FUNC(void,           DEM_CODE) GetDTCSelectionResult                (void);
      FUNC(void,           DEM_CODE) GetDTCSelectionResultForClearDTC     (void);
      FUNC(void,           DEM_CODE) GetEventUdsStatus                    (void);
      FUNC(void,           DEM_CODE) GetMonitorStatus                     (void);
      FUNC(void,           DEM_CODE) GetDebouncingOfEvent                 (void);
      FUNC(void,           DEM_CODE) GetDTCOfEvent                        (void);
      FUNC(void,           DEM_CODE) GetDTCSuppression                    (void);
      FUNC(void,           DEM_CODE) GetFaultDetectionCounter             (void);
      FUNC(void,           DEM_CODE) GetIndicatorStatus                   (void);
      FUNC(void,           DEM_CODE) GetEventFreezeFrameDataEx            (void);
      FUNC(void,           DEM_CODE) GetEventExtendedDataRecordEx         (void);
      FUNC(void,           DEM_CODE) GetEventMemoryOverflow               (void);
      FUNC(void,           DEM_CODE) GetNumberOfEventMemoryEntries        (void);
      FUNC(void,           DEM_CODE) ResetEventDebounceStatus             (void);
      FUNC(void,           DEM_CODE) ResetEventStatus                     (void);
      FUNC(void,           DEM_CODE) RestartOperationCycle                (void);
      FUNC(void,           DEM_CODE) PrestoreFreezeFrame                  (void);
      FUNC(void,           DEM_CODE) SelectDTC                            (void);
      FUNC(void,           DEM_CODE) SetComponentAvailable                (void);
      FUNC(void,           DEM_CODE) SetDTCSuppression                    (void);
      FUNC(void,           DEM_CODE) SetEnableCondition                   (void);
      FUNC(void,           DEM_CODE) SetEventAvailable                    (void);
      FUNC(void,           DEM_CODE) SetEventFailureCycleCounterThreshold (void);
      FUNC(Std_TypeReturn, DEM_CODE) SetEventStatus                       (void);
      FUNC(void,           DEM_CODE) SetEventStatusWithMonitorData        (void);
      FUNC(void,           DEM_CODE) SetStorageCondition                  (void);
      FUNC(void,           DEM_CODE) SetWIRStatus                         (void);
      FUNC(void,           DEM_CODE) GetTranslationType                   (void);
      FUNC(void,           DEM_CODE) GetDTCStatusAvailabilityMask         (void);
      FUNC(void,           DEM_CODE) GetStatusOfDTC                       (void);
      FUNC(void,           DEM_CODE) GetSeverityOfDTC                     (void);
      FUNC(void,           DEM_CODE) GetFunctionalUnitOfDTC               (void);
      FUNC(void,           DEM_CODE) SetDTCFilter                         (void);
      FUNC(void,           DEM_CODE) GetNumberOfFilteredDTC               (void);
      FUNC(void,           DEM_CODE) GetNextFilteredDTC                   (void);
      FUNC(void,           DEM_CODE) GetNextFilteredDTCAndFDC             (void);
      FUNC(void,           DEM_CODE) GetNextFilteredDTCAndSeverity        (void);
      FUNC(void,           DEM_CODE) SetFreezeFrameRecordFilter           (void);
      FUNC(void,           DEM_CODE) GetNextFilteredRecord                (void);
      FUNC(void,           DEM_CODE) GetDTCByOccuranceTime                (void);
      FUNC(void,           DEM_CODE) DisableDTCRecordUpdate               (void);
      FUNC(void,           DEM_CODE) EnableDTCRecordUpdate                (void);
      FUNC(void,           DEM_CODE) GetSizeOfExtendedDataRecordSelection (void);
      FUNC(void,           DEM_CODE) GetSizeOfFreezeFrameSelection        (void);
      FUNC(void,           DEM_CODE) GetNextExtendedDataRecord            (void);
      FUNC(void,           DEM_CODE) GetNextFreezeFrameData               (void);
      FUNC(void,           DEM_CODE) SelectExtendedDataRecord             (void);
      FUNC(void,           DEM_CODE) SelectFreezeFrameData                (void);
      FUNC(void,           DEM_CODE) GetNumberOfFreezeFrameRecords        (void);
      FUNC(void,           DEM_CODE) DisableDTCSetting                    (void);
      FUNC(void,           DEM_CODE) EnableDTCSetting                     (void);
      FUNC(void,           DEM_CODE) DcmGetInfoTypeValue08                (void);
      FUNC(void,           DEM_CODE) DcmGetInfoTypeValue0B                (void);
      FUNC(void,           DEM_CODE) DcmReadDataOfPID01                   (void);
      FUNC(void,           DEM_CODE) DcmReadDataOfPID1C                   (void);
      FUNC(void,           DEM_CODE) DcmReadDataOfPID21                   (void);
      FUNC(void,           DEM_CODE) DcmReadDataOfPID30                   (void);
      FUNC(void,           DEM_CODE) DcmReadDataOfPID31                   (void);
      FUNC(void,           DEM_CODE) DcmReadDataOfPID41                   (void);
      FUNC(void,           DEM_CODE) DcmReadDataOfPID4D                   (void);
      FUNC(void,           DEM_CODE) DcmReadDataOfPID4E                   (void);
      FUNC(void,           DEM_CODE) DcmReadDataOfPID91                   (void);
      FUNC(void,           DEM_CODE) DcmReadDataOfOBDFreezeFrame          (void);
      FUNC(void,           DEM_CODE) DcmGetDTCOfOBDFreezeFrame            (void);
      FUNC(void,           DEM_CODE) DcmGetAvailableOBDMIDs               (void);
      FUNC(void,           DEM_CODE) DcmGetNumTIDsOfOBDMID                (void);
      FUNC(void,           DEM_CODE) DcmGetDTRData                        (void);
      FUNC(void,           DEM_CODE) J1939DcmSetDTCFilter                 (void);
      FUNC(void,           DEM_CODE) J1939DcmGetNumberOfFilteredDTC       (void);
      FUNC(void,           DEM_CODE) J1939DcmGetNextFilteredDTC           (void);
      FUNC(void,           DEM_CODE) J1939DcmFirstDTCwithLampStatus       (void);
      FUNC(void,           DEM_CODE) J1939DcmClearDTC                     (void);
      FUNC(void,           DEM_CODE) J1939DcmSetFreezeFrameFilter         (void);
      FUNC(void,           DEM_CODE) J1939DcmGetNextFreezeFrame           (void);
      FUNC(void,           DEM_CODE) J1939DcmGetNextSPNInFreezeFrame      (void);
      FUNC(void,           DEM_CODE) J1939DcmSetRatioFilter               (void);
      FUNC(void,           DEM_CODE) J1939DcmGetNextFilteredRatio         (void);
      FUNC(void,           DEM_CODE) J1939DcmReadDiagnosticReadiness1     (void);
      FUNC(void,           DEM_CODE) J1939DcmReadDiagnosticReadiness2     (void);
      FUNC(void,           DEM_CODE) J1939DcmReadDiagnosticReadiness3     (void);
      FUNC(void,           DEM_CODE) SetEventDisabled                     (void);
      FUNC(void,           DEM_CODE) RepIUMPRFaultDetected                (void);
      FUNC(void,           DEM_CODE) SetIUMPRDenCondition                 (void);
      FUNC(void,           DEM_CODE) GetIUMPRDenCondition                 (void);
      FUNC(void,           DEM_CODE) RepIUMPRDenRelease                   (void);
      FUNC(void,           DEM_CODE) SetPtoStatus                         (void);
      FUNC(void,           DEM_CODE) ReadDataPID01                        (void);
      FUNC(void,           DEM_CODE) GetDataOfPID21                       (void);
      FUNC(void,           DEM_CODE) SetDataOfPID21                       (void);
      FUNC(void,           DEM_CODE) SetDataOfPID31                       (void);
      FUNC(void,           DEM_CODE) SetDataOfPID4D                       (void);
      FUNC(void,           DEM_CODE) SetDataOfPID4E                       (void);
      FUNC(void,           DEM_CODE) GetCycleQualified                    (void);
      FUNC(void,           DEM_CODE) SetCycleQualified                    (void);
      FUNC(void,           DEM_CODE) GetDTCSeverityAvailabilityMask       (void);
      FUNC(void,           DEM_CODE) GetB1Counter                         (void);
      FUNC(void,           DEM_CODE) SetDTR                               (void);
};

FUNC(void, DEM_CODE) class_Dem_Unused::Shutdown(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::ClearDTC(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::ClearPrestoredFreezeFrame(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetComponentFailed(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetDTCSelectionResult(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetDTCSelectionResultForClearDTC(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetEventUdsStatus(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetMonitorStatus(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetDebouncingOfEvent(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetDTCOfEvent(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetDTCSuppression(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetFaultDetectionCounter(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetIndicatorStatus(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetEventFreezeFrameDataEx(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetEventExtendedDataRecordEx(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetEventMemoryOverflow(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetNumberOfEventMemoryEntries(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::ResetEventDebounceStatus(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::ResetEventStatus(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::RestartOperationCycle(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::PrestoreFreezeFrame(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::SelectDTC(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::SetComponentAvailable(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::SetDTCSuppression(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::SetEnableCondition(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::SetEventAvailable(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::SetEventFailureCycleCounterThreshold(void){
}

FUNC(Std_TypeReturn, DEM_CODE) class_Dem_Unused::SetEventStatus(void){
   return E_OK;
}

FUNC(void, DEM_CODE) class_Dem_Unused::SetEventStatusWithMonitorData(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::SetStorageCondition(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::SetWIRStatus(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetTranslationType(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetDTCStatusAvailabilityMask(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetStatusOfDTC(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetSeverityOfDTC(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetFunctionalUnitOfDTC(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::SetDTCFilter(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetNumberOfFilteredDTC(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetNextFilteredDTC(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetNextFilteredDTCAndFDC(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetNextFilteredDTCAndSeverity(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::SetFreezeFrameRecordFilter(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetNextFilteredRecord(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetDTCByOccuranceTime(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::DisableDTCRecordUpdate(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::EnableDTCRecordUpdate(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetSizeOfExtendedDataRecordSelection(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetSizeOfFreezeFrameSelection(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetNextExtendedDataRecord(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetNextFreezeFrameData(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::SelectExtendedDataRecord(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::SelectFreezeFrameData(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetNumberOfFreezeFrameRecords(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::DisableDTCSetting(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::EnableDTCSetting(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::DcmGetInfoTypeValue08(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::DcmGetInfoTypeValue0B(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::DcmReadDataOfPID01(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::DcmReadDataOfPID1C(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::DcmReadDataOfPID21(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::DcmReadDataOfPID30(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::DcmReadDataOfPID31(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::DcmReadDataOfPID41(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::DcmReadDataOfPID4D(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::DcmReadDataOfPID4E(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::DcmReadDataOfPID91(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::DcmReadDataOfOBDFreezeFrame(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::DcmGetDTCOfOBDFreezeFrame(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::DcmGetAvailableOBDMIDs(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::DcmGetNumTIDsOfOBDMID(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::DcmGetDTRData(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::J1939DcmSetDTCFilter(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::J1939DcmGetNumberOfFilteredDTC(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::J1939DcmGetNextFilteredDTC(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::J1939DcmFirstDTCwithLampStatus(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::J1939DcmClearDTC(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::J1939DcmSetFreezeFrameFilter(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::J1939DcmGetNextFreezeFrame(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::J1939DcmGetNextSPNInFreezeFrame(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::J1939DcmSetRatioFilter(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::J1939DcmGetNextFilteredRatio(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::J1939DcmReadDiagnosticReadiness1(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::J1939DcmReadDiagnosticReadiness2(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::J1939DcmReadDiagnosticReadiness3(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::SetEventDisabled(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::RepIUMPRFaultDetected(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::SetIUMPRDenCondition(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetIUMPRDenCondition(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::RepIUMPRDenRelease(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::SetPtoStatus(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::ReadDataPID01(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetDataOfPID21(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::SetDataOfPID21(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::SetDataOfPID31(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::SetDataOfPID4D(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::SetDataOfPID4E(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetCycleQualified(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::SetCycleQualified(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetDTCSeverityAvailabilityMask(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::GetB1Counter(void){
}

FUNC(void, DEM_CODE) class_Dem_Unused::SetDTR(void){
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

