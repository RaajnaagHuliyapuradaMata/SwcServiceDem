

#ifndef DEM_CLEAR_H
#define DEM_CLEAR_H

#include "Dem_Cfg_Clear.hpp"
#include "Dem_Types.hpp"
#include "Dem_Cfg_Events.hpp"
#include "Dem_Mapping.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

void Dem_ClearMainFunction(void);
void Dem_ClearDtcInit(void);
boolean Dem_ClearIsInProgress (void);

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#endif
