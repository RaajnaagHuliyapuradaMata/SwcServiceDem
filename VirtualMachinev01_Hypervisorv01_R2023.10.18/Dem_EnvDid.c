#include "Std_Types.hpp"

#include "Dem_Cfg_EnvDid.hpp"
#include "Dem_Cfg_EnvDataElement.hpp"
#include "Dem_EnvDid.hpp"

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
const uint8 Dem_Cfg_EnvDid2DataElement[] = DEM_CFG_ENVDID2DATAELEMENT;
DEM_ARRAY_DEFINE_CONST(Dem_EnvDid, Dem_Cfg_EnvDid, DEM_CFG_ENVDID_ARRAYLENGTH, DEM_CFG_ENVDID);
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
