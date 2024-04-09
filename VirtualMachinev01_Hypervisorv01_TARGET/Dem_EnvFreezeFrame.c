#include "Std_Types.hpp"

#include "Dem_Types.hpp"
#include "Dem_Array.hpp"
#include "Dem_EnvFreezeFrame.hpp"
#include "Dem_Cfg_EnvFreezeFrame.hpp"
#include "Dem_Cfg_EnvDid.hpp"

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
const uint8 Dem_Cfg_EnvFreezeFrame2Did[] = DEM_CFG_ENVFREEZEFRAME2DID;
DEM_ARRAY_DEFINE_CONST(Dem_EnvFreezeFrame, Dem_Cfg_EnvFreezeFrame, DEM_CFG_ENVFREEZEFRAME_ARRAYLENGTH, DEM_CFG_ENVFREEZEFRAME);
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
