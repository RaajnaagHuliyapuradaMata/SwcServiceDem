/******************************************************************************/
/* File   : ServiceDem.cpp                                                    */
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
#include "Module.hpp"
#include "ServiceDem.hpp"
#include "infServiceDem_Imp.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

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
VAR(module_ServiceDem, SERVICEDEM_VAR) ServiceDem;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, SERVICEDEM_CODE) module_ServiceDem::InitFunction(
      CONSTP2CONST(ConstModule_TypeAbstract, SERVICEDEM_CONST,       SERVICEDEM_APPL_CONST) lptrNvMBlocksRomModule
   ,  CONSTP2CONST(CfgModule_TypeAbstract,   SERVICEDEM_CONFIG_DATA, SERVICEDEM_APPL_CONST) lptrCfgModule
){
#if(STD_ON == ServiceDem_InitCheck)
   if(
         E_OK
      != IsInitDone
   ){
#endif
      if(
            (NULL_PTR != lptrNvMBlocksRomModule)
         && (NULL_PTR != lptrCfgModule)
      ){
         lptrNvMBlocksRom = lptrNvMBlocksRomModule;
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
         ,  SERVICEDEM_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::DeInitFunction(
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
         ,  SERVICEDEM_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::MainFunction(
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
         ,  SERVICEDEM_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::PreInit(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::Shutdown(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::ClearDTC(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::ClearPrestoredMcalFreezeMcalFrame(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetServiceComponentFailed(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetDTCSelectionResult(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetDTCSelectionResultForClearDTC(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetEventUdsStatus(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetMonitorStatus(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetDebouncingOfEvent(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetDTCOfEvent(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetDTCSuppression(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetFaultServiceDetectionCounter(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetIndicatorStatus(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetEventMcalFreezeMcalFrameDataEx(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetEventExtendedDataRecordEx(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetEventMemoryOverflow(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetNumberOfEventMemoryEntries(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::ResetEventDebounceStatus(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::ResetEventStatus(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::RestartOperationCycle(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::PrestoreMcalFreezeMcalFrame(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SelectDTC(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SetServiceComponentAvailable(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SetDTCSuppression(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SetEnableCondition(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SetEventAvailable(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SetEventFailureCycleCounterThreshold(
   void
){
}

FUNC(Std_TypeReturn, SERVICEDEM_CODE) module_ServiceDem::SetEventStatus(
   void
){
   return E_OK;
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SetEventStatusWithMonitorData(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SetStorageCondition(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SetWIRStatus(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetTranslationType(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetDTCStatusAvailabilityMask(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetStatusOfDTC(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetSeverityOfDTC(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetFunctionalUnitOfDTC(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SetDTCFilter(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetNumberOfFilteredDTC(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetNextFilteredDTC(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetNextFilteredDTCAndFDC(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetNextFilteredDTCAndSeverity(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SetMcalFreezeMcalFrameRecordFilter(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetNextFilteredRecord(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetDTCByOccuranceTime(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::DisableDTCRecordUpdate(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::EnableDTCRecordUpdate(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetSizeOfExtendedDataRecordSelection(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetSizeOfMcalFreezeMcalFrameSelection(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetNextExtendedDataRecord(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetNextMcalFreezeMcalFrameData(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SelectExtendedDataRecord(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SelectMcalFreezeMcalFrameData(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetNumberOfMcalFreezeMcalFrameRecords(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::DisableDTCSetting(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::EnableDTCSetting(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::ServiceDcmGetInfoTypeValue08(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::ServiceDcmGetInfoTypeValue0B(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::ServiceDcmReadDataOfPID01(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::ServiceDcmReadDataOfPID1C(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::ServiceDcmReadDataOfPID21(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::ServiceDcmReadDataOfPID30(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::ServiceDcmReadDataOfPID31(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::ServiceDcmReadDataOfPID41(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::ServiceDcmReadDataOfPID4D(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::ServiceDcmReadDataOfPID4E(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::ServiceDcmReadDataOfPID91(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::ServiceDcmReadDataOfOBDMcalFreezeMcalFrame(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::ServiceDcmGetDTCOfOBDMcalFreezeMcalFrame(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::ServiceDcmGetAvailableOBDMIDs(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::ServiceDcmGetNumTIDsOfOBDMID(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::ServiceDcmGetDTRData(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::J1939ServiceDcmSetDTCFilter(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::J1939ServiceDcmGetNumberOfFilteredDTC(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::J1939ServiceDcmGetNextFilteredDTC(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::J1939ServiceDcmFirstDTCwithLampStatus(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::J1939ServiceDcmClearDTC(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::J1939ServiceDcmSetMcalFreezeMcalFrameFilter(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::J1939ServiceDcmGetNextMcalFreezeMcalFrame(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::J1939ServiceDcmGetNextSPNInMcalFreezeMcalFrame(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::J1939ServiceDcmSetRatioFilter(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::J1939ServiceDcmGetNextFilteredRatio(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::J1939ServiceDcmReadDiagnosticReadiness1(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::J1939ServiceDcmReadDiagnosticReadiness2(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::J1939ServiceDcmReadDiagnosticReadiness3(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SetEventDisabled(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::RepIUMPRFaultServiceDetected(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SetIUMPRDenCondition(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetIUMPRDenCondition(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::RepIUMPRDenRelease(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SetPtoStatus(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::ReadDataPID01(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetDataOfPID21(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SetDataOfPID21(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SetDataOfPID31(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SetDataOfPID4D(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SetDataOfPID4E(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetCycleQualified(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SetCycleQualified(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetDTCSeverityAvailabilityMask(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::GetB1Counter(
   void
){
}

FUNC(void, SERVICEDEM_CODE) module_ServiceDem::SetDTR(
   void
){
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

