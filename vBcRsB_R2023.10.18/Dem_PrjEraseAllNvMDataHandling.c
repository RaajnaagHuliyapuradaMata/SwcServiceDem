#include "Std_Types.hpp"


#include "Dem_PrjEraseAllNvMDataHandling.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

Dem_EraseAllRequestType Dem_PrjEraseAllNvMDataHandling(Dem_HashIdCheckResultType HashIdCheckResult)
{
    Dem_EraseAllRequestType eraseAll = DEM_ERASE_ALL_REQUEST_NONE;

   if(HashIdCheckResult == DEM_HASH_ID_MISMATCH)
   {
        eraseAll = DEM_ERASE_ALL_REQUEST_ALL;
   }

    return eraseAll;
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

