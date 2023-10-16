#include "Std_Types.hpp"

#include "Dem_ClientClearMachine.hpp"

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"
Dem_ClientClearMachineType Dem_ClientClearMachine;
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"
