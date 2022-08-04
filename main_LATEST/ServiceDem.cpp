/******************************************************************************/
/* File   : ServiceDem.cpp                                                           */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Module.hpp"
#include "ServiceDem.hpp"
#include "infServiceDem_Imp.hpp"

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

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
VAR(module_ServiceDem, DEM_VAR) ServiceDem;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, DEM_CODE) module_ServiceDem::InitFunction(
      CONSTP2CONST(ConstModule_TypeAbstract, DEM_CONST,       DEM_APPL_CONST) lptrConstModule
   ,  CONSTP2CONST(CfgModule_TypeAbstract,   DEM_CONFIG_DATA, DEM_APPL_CONST) lptrCfgModule
){
#if(STD_ON == ServiceDem_InitCheck)
   if(
         E_OK
      != IsInitDone
   ){
#endif
      if(
            (NULL_PTR != lptrConstModule)
         && (NULL_PTR != lptrCfgModule)
      ){
         lptrConst = (const ConstServiceDem_Type*)lptrConstModule;
         lptrCfg   = lptrCfgModule;
      }
      else{
#if(STD_ON == ServiceDem_DevErrorDetect)
         ServiceDet_ReportError(
               0 //TBD: IdModule
            ,  0 //TBD: IdInstance
            ,  0 //TBD: IdApi
            ,  0 //TBD: IdError
         );
#endif
      }
#if(STD_ON == ServiceDem_InitCheck)
      IsInitDone = E_OK;
   }
   else{
#if(STD_ON == ServiceDem_DevErrorDetect)
      ServiceDet_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  DEM_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, DEM_CODE) module_ServiceDem::DeInitFunction(
   void
){
#if(STD_ON == ServiceDem_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == ServiceDem_InitCheck)
      IsInitDone = E_NOT_OK;
   }
   else{
#if(STD_ON == ServiceDem_DevErrorDetect)
      ServiceDet_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  DEM_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, DEM_CODE) module_ServiceDem::MainFunction(
   void
){
#if(STD_ON == ServiceDem_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == ServiceDem_InitCheck)
   }
   else{
#if(STD_ON == ServiceDem_DevErrorDetect)
      ServiceDet_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  DEM_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, DEM_CODE) module_ServiceDem::PreInit(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::Shutdown(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::ClearDTC(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::ClearPrestoredMcalFreezeMcalFrame(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetServiceComponentFailed(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetDTCSelectionResult(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetDTCSelectionResultForClearDTC(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetEventUdsStatus(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetMonitorStatus(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetDebouncingOfEvent(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetDTCOfEvent(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetDTCSuppression(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetFaultServiceDetectionCounter(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetIndicatorStatus(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetEventMcalFreezeMcalFrameDataEx(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetEventExtendedDataRecordEx(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetEventMemoryOverflow(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetNumberOfEventMemoryEntries(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::ResetEventDebounceStatus(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::ResetEventStatus(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::RestartOperationCycle(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::PrestoreMcalFreezeMcalFrame(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::SelectDTC(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::SetServiceComponentAvailable(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::SetDTCSuppression(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::SetEnableCondition(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::SetEventAvailable(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::SetEventFailureCycleCounterThreshold(
   void
){
}

FUNC(Std_TypeReturn, DEM_CODE) module_ServiceDem::SetEventStatus(
   void
){
   return E_OK;
}

FUNC(void, DEM_CODE) module_ServiceDem::SetEventStatusWithMonitorData(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::SetStorageCondition(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::SetWIRStatus(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetTranslationType(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetDTCStatusAvailabilityMask(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetStatusOfDTC(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetSeverityOfDTC(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetFunctionalUnitOfDTC(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::SetDTCFilter(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetNumberOfFilteredDTC(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetNextFilteredDTC(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetNextFilteredDTCAndFDC(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetNextFilteredDTCAndSeverity(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::SetMcalFreezeMcalFrameRecordFilter(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetNextFilteredRecord(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetDTCByOccuranceTime(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::DisableDTCRecordUpdate(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::EnableDTCRecordUpdate(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetSizeOfExtendedDataRecordSelection(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetSizeOfMcalFreezeMcalFrameSelection(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetNextExtendedDataRecord(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetNextMcalFreezeMcalFrameData(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::SelectExtendedDataRecord(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::SelectMcalFreezeMcalFrameData(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetNumberOfMcalFreezeMcalFrameRecords(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::DisableDTCSetting(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::EnableDTCSetting(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::ServiceDcmGetInfoTypeValue08(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::ServiceDcmGetInfoTypeValue0B(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::ServiceDcmReadDataOfPID01(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::ServiceDcmReadDataOfPID1C(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::ServiceDcmReadDataOfPID21(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::ServiceDcmReadDataOfPID30(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::ServiceDcmReadDataOfPID31(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::ServiceDcmReadDataOfPID41(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::ServiceDcmReadDataOfPID4D(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::ServiceDcmReadDataOfPID4E(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::ServiceDcmReadDataOfPID91(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::ServiceDcmReadDataOfOBDMcalFreezeMcalFrame(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::ServiceDcmGetDTCOfOBDMcalFreezeMcalFrame(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::ServiceDcmGetAvailableOBDMIDs(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::ServiceDcmGetNumTIDsOfOBDMID(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::ServiceDcmGetDTRData(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::J1939ServiceDcmSetDTCFilter(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::J1939ServiceDcmGetNumberOfFilteredDTC(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::J1939ServiceDcmGetNextFilteredDTC(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::J1939ServiceDcmFirstDTCwithLampStatus(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::J1939ServiceDcmClearDTC(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::J1939ServiceDcmSetMcalFreezeMcalFrameFilter(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::J1939ServiceDcmGetNextMcalFreezeMcalFrame(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::J1939ServiceDcmGetNextSPNInMcalFreezeMcalFrame(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::J1939ServiceDcmSetRatioFilter(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::J1939ServiceDcmGetNextFilteredRatio(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::J1939ServiceDcmReadDiagnosticReadiness1(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::J1939ServiceDcmReadDiagnosticReadiness2(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::J1939ServiceDcmReadDiagnosticReadiness3(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::SetEventDisabled(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::RepIUMPRFaultServiceDetected(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::SetIUMPRDenCondition(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetIUMPRDenCondition(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::RepIUMPRDenRelease(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::SetPtoStatus(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::ReadDataPID01(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetDataOfPID21(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::SetDataOfPID21(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::SetDataOfPID31(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::SetDataOfPID4D(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::SetDataOfPID4E(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetCycleQualified(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::SetCycleQualified(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetDTCSeverityAvailabilityMask(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::GetB1Counter(
   void
){
}

FUNC(void, DEM_CODE) module_ServiceDem::SetDTR(
   void
){
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

