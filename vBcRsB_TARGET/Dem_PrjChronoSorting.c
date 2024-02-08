#include "Std_Types.hpp"

#include "Dem_ChronoSort.hpp"
#include "Dem_PrjEvmemProjectExtension.hpp"
#include "Dem_EvMem.hpp"
#include "Dem_Dtcs.hpp"

#if(DEM_CFG_REPORT_CHRONOLOGICAL_ORDER_HOOKS_ENABLED)

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

boolean Dem_IsChronoSortEnabled(void){

    return FALSE;
}

static uint32 Dem_ChronoSortGetNewEvMemSortId(uint16_least MemId)
{
}

void Dem_ChronoSortEvMemUpdateSortId(uint16_least LocId,uint16_least MemId,uint16_least StatusOld,uint16_least StatusNew,uint16_least *WriteSts)
{
}

void Dem_ChronoSortDTCFilterInit(void){
}

boolean Dem_ChronoSortSetDTCFilter(Dem_DTCFilterState* DTCFilter)
{

    return FALSE;
}

void Dem_ChronoSortMainFunction(Dem_DTCFilterState* DTCFilter)
{
}

Dem_ReturnGetNextFilteredDTCType Dem_ChronoSortGetNextFilteredDTCID (Dem_DtcIdType* dtcId, uint32* DTC, uint8* DTCStatus)
{
}

Dem_ReturnGetNumberOfFilteredDTCType Dem_ChronoSortGetNumberOfFilteredDTC(uint16* NumberOfFilteredDTC)
{
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#endif
