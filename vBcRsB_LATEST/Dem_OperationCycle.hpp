

#ifndef DEM_OPERATIONCYCLE_H
#define DEM_OPERATIONCYCLE_H

#include "Dem_Cfg_OperationCycle.hpp"
#include "Dem_Cfg_OperationCycle_DataStructures.hpp"
#include "Dem_Types.hpp"

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

extern Dem_OperationCycleList Dem_OperationCycleStates;

#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

DEM_INLINE boolean Dem_IsOperationCycleStarted(Dem_OperationCycleIdType OperationCycleId)
{
    return DEM_OPERATIONCYCLE_ISBITSET(Dem_OperationCycleStates, OperationCycleId);
}

void Dem_OperationCycleInit(void);
void Dem_OperationCycleInitCheckNvm(void);
boolean Dem_OperationCyclesMainFunction(void);

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
#endif

