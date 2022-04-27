#pragma once
/******************************************************************************/
/* File   : Dem_core.hpp                                                      */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class class_Dem_Functionality{
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

