

#ifndef DEM_J1939DCM_H
#define DEM_J1939DCM_H

#include "Dem_Types.hpp"

#if(DEM_CFG_J1939DCM != DEM_CFG_J1939DCM_OFF)

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#if(DEM_CFG_J1939DCM_READ_DTC_SUPPORT)

Dem_ReturnSetFilterType Dem_J1939DcmSetDTCFilter(Dem_J1939DcmDTCStatusFilterType DTCStatusFilter
   ,     Dem_DTCKindType DTCKind
   ,     uint8 node
   ,     Dem_J1939DcmLampStatusType* LampStatus);

Dem_ReturnGetNumberOfFilteredDTCType Dem_J1939DcmGetNumberOfFilteredDTC(uint16* NumberOfFilteredDTC);

Dem_ReturnGetNextFilteredElementType Dem_J1939DcmGetNextFilteredDTC(uint32* J1939DTC, uint8* OccurenceCounter);

void Dem_J1939DcmDTCFilterMainFunction(void);

#endif

#if(DEM_CFG_J1939DCM_DM31_SUPPORT)

void Dem_J1939DcmFirstDTCwithLampStatus(uint8 node);

Dem_ReturnGetNextFilteredElementType Dem_J1939DcmGetNextDTCwithLampStatus(Dem_J1939DcmLampStatusType* LampStatus
   ,     uint32* J1939DTC
   ,     uint8* OccurenceCounter);
#endif

#if(DEM_CFG_J1939DCM_CLEAR_SUPPORT != DEM_CFG_J1939DCM_OFF)

Dem_ReturnClearDTCType Dem_J1939DcmClearDTC(Dem_J1939DcmSetClearFilterType DTCTypeFilter, uint8 node);
#endif

#if(DEM_CFG_J1939DCM_FREEZEFRAME_SUPPORT || DEM_CFG_J1939DCM_EXPANDED_FREEZEFRAME_SUPPORT)

Dem_ReturnSetFilterType Dem_J1939DcmSetFreezeFrameFilter(Dem_J1939DcmSetFreezeFrameFilterType FreezeFrameKind, uint8 node);

Dem_ReturnGetNextFilteredElementType Dem_J1939DcmGetNextFreezeFrame(uint32* J1939DTC
   ,     uint8* OccurenceCounter
   ,     uint8* DestBuffer
   ,     uint16* BufSize);

#if(DEM_CFG_J1939DCM_EXPANDED_FREEZEFRAME_SUPPORT)

Dem_ReturnGetNextFilteredElementType Dem_J1939DcmGetNextSPNInFreezeFrame(uint32* SPNSupported, uint8* SPNDataLength);
#endif

#endif

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)

Dem_ReturnSetFilterType Dem_J1939DcmSetRatioFilter(uint16* IgnitionCycleCounter
   ,     uint16* OBDMonitoringConditionsEncountered
   ,     uint8 node);

Dem_ReturnGetNextFilteredElementType Dem_J1939DcmGetNextFilteredRatio(uint16* SPN
   ,     uint16* Numerator
   ,     uint16* Denominator);

Std_ReturnType Dem_J1939DcmReadDiagnosticReadiness1(Dem_J1939DcmDiagnosticReadiness1Type* DataValue, uint8 node);

Std_ReturnType Dem_J1939DcmReadDiagnosticReadiness2(Dem_J1939DcmDiagnosticReadiness2Type* DataValue, uint8 node);

Std_ReturnType Dem_J1939DcmReadDiagnosticReadiness3(Dem_J1939DcmDiagnosticReadiness3Type* DataValue, uint8 node);

#endif

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#endif

#endif
