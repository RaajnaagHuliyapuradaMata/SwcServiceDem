

#ifndef DEM_DTCSTATUSBYTE_H
#define DEM_DTCSTATUSBYTE_H

#include "Dem_ClientBaseHandling.hpp"
#include "Dem_ClientClearMachine.hpp"
#include "Dem_Types.hpp"

#include "Dem_Clear.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

uint8 Dem_DtcStatusByteRetrieve (Dem_DtcIdType dtcId);
uint8 Dem_DtcStatusByteRetrieveWithOrigin (Dem_DtcIdType dtcId, Dem_DTCOriginType DtcOrigin, boolean* DtcStatusIsValid);
void Dem_ClearDTCsEvents(Dem_EventIdType EventId, Dem_DTCOriginType DTCOrigin, Dem_ClientClearMachineType *Dem_ClientClearMachinePtr);
void Dem_ClearAllDTCs(Dem_DTCOriginType DTCOrigin, Dem_ClientClearMachineType *Dem_ClientClearMachinePtr);
void Dem_ClearSingleDTC(Dem_DtcIdType dtcId, Dem_DTCOriginType DTCOrigin, Dem_ClientClearMachineType *Dem_ClientClearMachinePtr);
boolean Dem_IsPendingClearEvent(Dem_EventIdType EventId);

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#endif
