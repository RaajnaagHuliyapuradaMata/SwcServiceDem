

#ifndef DEM_DEPENDENCY_H
#define DEM_DEPENDENCY_H

#include "Dem_Cfg_Nodes.hpp"
#include "Dem_Cfg_StorageCondition.hpp"
#include "Dem_Cfg_Main.hpp"
#include "Dem_Dependencies.hpp"
#include "Dem_Mapping.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#if(DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)

void Dem_DependencyInit(void);
void Dem_RecheckNodeNotRecoverableRequest(void);
void Dem_DependencyMainFunction(void);

#else

DEM_INLINE void Dem_DependencyInit(void) {}
DEM_INLINE void Dem_RecheckNodeNotRecoverableRequest(void) {}
DEM_INLINE void Dem_DependencyMainFunction(void) {}

#endif

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#endif

