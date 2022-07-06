/******************************************************************************/
/* File   : Dem.cpp                                                           */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Module.hpp"
#include "Dem.hpp"
#include "infDem_Imp.hpp"

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
CONSTP2VAR(infEcuMClient, DEM_VAR, DEM_CONST) gptrinfEcuMClient_Dem = &Dem;
CONSTP2VAR(infDcmClient,  DEM_VAR, DEM_CONST) gptrinfDcmClient_Dem  = &Dem;
CONSTP2VAR(infSchMClient, DEM_VAR, DEM_CONST) gptrinfSchMClient_Dem = &Dem;
CONSTP2VAR(infDem_EcuM,   DEM_VAR, DEM_CONST) gptrinfDem_EcuM       = &Dem;

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
VAR(module_Dem, DEM_VAR) Dem;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, DEM_CODE) module_Dem::InitFunction(
   CONSTP2CONST(CfgModule_TypeAbstract, DEM_CONFIG_DATA, DEM_APPL_CONST) lptrCfgModule
){
#if(STD_ON == Dem_InitCheck)
   if(
         E_OK
      != IsInitDone
   ){
#endif
      if(NULL_PTR != lptrCfgModule){
         lptrCfg = lptrCfgModule;
      }
      else{
#if(STD_ON == Dem_DevErrorDetect)
         Det_ReportError(
               0 //TBD: IdModule
            ,  0 //TBD: IdInstance
            ,  0 //TBD: IdApi
            ,  0 //TBD: IdError
         );
#endif
      }
#if(STD_ON == Dem_InitCheck)
      IsInitDone = E_OK;
   }
   else{
#if(STD_ON == Dem_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  DEM_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, DEM_CODE) module_Dem::DeInitFunction(
   void
){
#if(STD_ON == Dem_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == Dem_InitCheck)
      IsInitDone = E_NOT_OK;
   }
   else{
#if(STD_ON == Dem_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  DEM_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, DEM_CODE) module_Dem::MainFunction(
   void
){
#if(STD_ON == Dem_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == Dem_InitCheck)
   }
   else{
#if(STD_ON == Dem_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  DEM_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, DEM_CODE) module_Dem::PreInit(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::Shutdown(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::ClearDTC(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::ClearPrestoredFreezeFrame(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetComponentFailed(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetDTCSelectionResult(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetDTCSelectionResultForClearDTC(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetEventUdsStatus(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetMonitorStatus(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetDebouncingOfEvent(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetDTCOfEvent(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetDTCSuppression(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetFaultDetectionCounter(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetIndicatorStatus(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetEventFreezeFrameDataEx(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetEventExtendedDataRecordEx(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetEventMemoryOverflow(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetNumberOfEventMemoryEntries(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::ResetEventDebounceStatus(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::ResetEventStatus(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::RestartOperationCycle(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::PrestoreFreezeFrame(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::SelectDTC(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::SetComponentAvailable(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::SetDTCSuppression(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::SetEnableCondition(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::SetEventAvailable(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::SetEventFailureCycleCounterThreshold(
   void
){
}

FUNC(Std_TypeReturn, DEM_CODE) module_Dem::SetEventStatus(
   void
){
   return E_OK;
}

FUNC(void, DEM_CODE) module_Dem::SetEventStatusWithMonitorData(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::SetStorageCondition(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::SetWIRStatus(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetTranslationType(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetDTCStatusAvailabilityMask(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetStatusOfDTC(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetSeverityOfDTC(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetFunctionalUnitOfDTC(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::SetDTCFilter(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetNumberOfFilteredDTC(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetNextFilteredDTC(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetNextFilteredDTCAndFDC(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetNextFilteredDTCAndSeverity(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::SetFreezeFrameRecordFilter(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetNextFilteredRecord(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetDTCByOccuranceTime(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::DisableDTCRecordUpdate(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::EnableDTCRecordUpdate(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetSizeOfExtendedDataRecordSelection(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetSizeOfFreezeFrameSelection(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetNextExtendedDataRecord(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetNextFreezeFrameData(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::SelectExtendedDataRecord(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::SelectFreezeFrameData(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetNumberOfFreezeFrameRecords(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::DisableDTCSetting(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::EnableDTCSetting(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::DcmGetInfoTypeValue08(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::DcmGetInfoTypeValue0B(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::DcmReadDataOfPID01(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::DcmReadDataOfPID1C(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::DcmReadDataOfPID21(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::DcmReadDataOfPID30(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::DcmReadDataOfPID31(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::DcmReadDataOfPID41(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::DcmReadDataOfPID4D(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::DcmReadDataOfPID4E(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::DcmReadDataOfPID91(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::DcmReadDataOfOBDFreezeFrame(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::DcmGetDTCOfOBDFreezeFrame(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::DcmGetAvailableOBDMIDs(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::DcmGetNumTIDsOfOBDMID(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::DcmGetDTRData(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::J1939DcmSetDTCFilter(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::J1939DcmGetNumberOfFilteredDTC(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::J1939DcmGetNextFilteredDTC(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::J1939DcmFirstDTCwithLampStatus(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::J1939DcmClearDTC(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::J1939DcmSetFreezeFrameFilter(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::J1939DcmGetNextFreezeFrame(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::J1939DcmGetNextSPNInFreezeFrame(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::J1939DcmSetRatioFilter(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::J1939DcmGetNextFilteredRatio(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::J1939DcmReadDiagnosticReadiness1(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::J1939DcmReadDiagnosticReadiness2(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::J1939DcmReadDiagnosticReadiness3(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::SetEventDisabled(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::RepIUMPRFaultDetected(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::SetIUMPRDenCondition(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetIUMPRDenCondition(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::RepIUMPRDenRelease(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::SetPtoStatus(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::ReadDataPID01(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetDataOfPID21(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::SetDataOfPID21(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::SetDataOfPID31(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::SetDataOfPID4D(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::SetDataOfPID4E(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetCycleQualified(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::SetCycleQualified(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetDTCSeverityAvailabilityMask(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::GetB1Counter(
   void
){
}

FUNC(void, DEM_CODE) module_Dem::SetDTR(
   void
){
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

