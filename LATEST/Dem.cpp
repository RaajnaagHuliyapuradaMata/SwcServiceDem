/******************************************************************************/
/* File   : Dem.cpp                                                           */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "module.h"
#include "infDem_Version.h"
#include "infDem_EcuM.h"
#include "infDem_Dcm.h"
#include "infDem_SchM.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class module_Dem:
      public abstract_module
   ,  public infDem_EcuM
{
   public:
      FUNC(void, DEM_CODE) InitFunction   (void);
      FUNC(void, DEM_CODE) DeInitFunction (void);
      FUNC(void, DEM_CODE) GetVersionInfo (void);
      FUNC(void, DEM_CODE) MainFunction   (void);
      FUNC(void, DEM_CODE) PreInit        (void);
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
VAR(module_Dem, DEM_VAR) Dem;
CONSTP2VAR(infEcuMClient, DEM_VAR, DEM_CONST) gptrinfEcuMClient_Dem = &Dem;
CONSTP2VAR(infDcmClient,  DEM_VAR, DEM_CONST) gptrinfDcmClient_Dem  = &Dem;
CONSTP2VAR(infSchMClient, DEM_VAR, DEM_CONST) gptrinfSchMClient_Dem = &Dem;
CONSTP2VAR(infDem_EcuM,   DEM_VAR, DEM_CONST) gptrinfDem_EcuM       = &Dem;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, DEM_CODE) module_Dem::InitFunction(void){
   Dem.IsInitDone = E_OK;
}

FUNC(void, DEM_CODE) module_Dem::DeInitFunction(void){
   Dem.IsInitDone = E_NOT_OK;
}

FUNC(void, DEM_CODE) module_Dem::GetVersionInfo(void){
}

FUNC(void, DEM_CODE) module_Dem::MainFunction(void){
}

FUNC(void, DEM_CODE) module_Dem::PreInit(void){
}

#include "Dem_Unused.h"

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

FUNC(void, DEM_CODE) class_Dem_Unused::SetEventStatus(void){
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

