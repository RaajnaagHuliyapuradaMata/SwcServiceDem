#ifndef DEM_DCM_H
#define DEM_DCM_H

#include "Dem_Types.hpp"
#include "Dcm_Types.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
Dem_DTCTranslationFormatType Dem_GetTranslationType(void);
Std_ReturnType Dem_GetDTCStatusAvailabilityMask(uint8* DTCStatusMask);
Dem_ReturnGetStatusOfDTCType Dem_GetStatusOfDTC(uint32 DTC, Dem_DTCKindType DTCKind, Dem_DTCOriginType DTCOrigin, uint8* DTCStatus);
Dem_ReturnGetSeverityOfDTCType Dem_GetSeverityOfDTC(uint32 DTC, Dem_DTCSeverityType* DTCSeverity);
Dem_ReturnGetFunctionalUnitOfDTCType Dem_GetFunctionalUnitOfDTC(uint32 DTC, uint8* DTCFunctionalUnit);

Dem_ReturnSetFilterType Dem_SetDTCFilter(uint8 DTCStatusMask
   ,     Dem_DTCKindType DTCKind
   ,     Dem_DTCFormatType DTCFormat
   ,     Dem_DTCOriginType DTCOrigin
   ,     Dem_FilterWithSeverityType FilterWithSeverity
   ,     Dem_DTCSeverityType DTCSeverityMask
   ,     Dem_FilterForFDCType FilterForFaultDetectionCounter);

Dem_ReturnGetNumberOfFilteredDTCType Dem_GetNumberOfFilteredDTC(uint16* NumberOfFilteredDTC);
Dem_ReturnGetNextFilteredDTCType Dem_GetNextFilteredDTC(uint32* DTC, uint8* DTCStatus);
Dem_ReturnGetNextFilteredDTCType Dem_GetNextFilteredDTCAndFDC(uint32* DTC, sint8* DTCFaultDetectionCounter);

Dem_ReturnGetNextFilteredDTCType Dem_GetNextFilteredDTCAndSeverity(uint32* DTC
   ,     uint8* DTCStatus
   ,     Dem_DTCSeverityType* DTCSeverity
   ,     uint8* DTCFunctionalUnit);

Dem_ReturnSetFilterType Dem_SetFreezeFrameRecordFilter(Dem_DTCFormatType DTCFormat, uint16* NumberOfFilteredRecords);
Dem_ReturnGetNextFilteredDTCType Dem_GetNextFilteredRecord(uint32* DTC, uint8* RecordNumber);

#if(DEM_CFG_EVMEMGENERIC_SUPPORTED != FALSE)
Dem_ReturnGetDTCByOccurrenceTimeType Dem_GetDTCByOccurrenceTime(Dem_DTCRequestType DTCRequest, Dem_DTCKindType DTCKind, uint32* DTC);
#endif

Dem_ReturnDisableDTCRecordUpdateType Dem_DisableDTCRecordUpdate(uint32 DTC, Dem_DTCOriginType DTCOrigin);
Std_ReturnType Dem_EnableDTCRecordUpdate(void);

Dem_ReturnGetFreezeFrameDataByDTCType Dem_GetFreezeFrameDataByDTC(uint32            DTC
   ,     Dem_DTCKindType   DTCKind
   ,     Dem_DTCOriginType DTCOrigin
   ,     uint8             RecordNumber
   ,     uint8*            DestBuffer
   ,     uint16*           BufSize
                                                                  );

Dem_ReturnGetSizeOfFreezeFrameByDTCType Dem_GetSizeOfFreezeFrameByDTC(uint32              DTC
   ,     Dem_DTCKindType     DTCKind
   ,     Dem_DTCOriginType   DTCOrigin
   ,     uint8               RecordNumber
   ,     uint16*             SizeOfFreezeFrame
                                                                      );

Dem_ReturnGetExtendedDataRecordByDTCType Dem_GetExtendedDataRecordByDTC(uint32              DTC
   ,     Dem_DTCKindType     DTCKind
   ,     Dem_DTCOriginType   DTCOrigin
   ,     uint8               ExtendedDataNumber
   ,     uint8*              DestBuffer
   ,     uint16*             BufSize
                                                                        );

Dem_ReturnGetSizeOfExtendedDataRecordByDTCType Dem_GetSizeOfExtendedDataRecordByDTC(uint32             DTC
   ,     Dem_DTCKindType    DTCKind
   ,     Dem_DTCOriginType  DTCOrigin
   ,     uint8              ExtendedDataNumber
   ,     uint16*            SizeOfExtendedDataRecord
                                                                                    );

Dem_ReturnClearDTCType Dem_DcmCheckClearParameter(uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin);

#if(DEM_CFG_CHECKAPICONSISTENCY == TRUE)
Dem_ReturnClearDTCType Dem_ClearDTC(uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin);
#endif

Dem_ReturnControlDTCSettingType Dem_DisableDTCSetting(Dem_DTCGroupType DTCGroup, Dem_DTCKindType DTCKind);
Dem_ReturnControlDTCSettingType Dem_EnableDTCSetting(Dem_DTCGroupType DTCGroup, Dem_DTCKindType DTCKind);
void Dem_DcmCancelOperation(void);
Std_ReturnType Dem_GetDTCSelectionResult(uint8 ClientId);
Std_ReturnType Dem_GetDTCSelectionResultForClearDTC(uint8 ClientId);
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#endif
