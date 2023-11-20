#include "Std_Types.hpp"

#include "Dem.hpp"
#include "Rte_Dem.hpp"
#include "Dem_PrjDisturbanceMemory.hpp"
#include "Dem_Deb.hpp"
#include "Dem_Events.hpp"
#include "Dem_DisturbanceMemory.hpp"
#include "Dem_EventStatus.hpp"

#if(DEM_CFG_DIST_MEM_CALLBACK_ON_DISTURBANCE)

DEM_INLINE Dem_DistMemPrjDataType* Dem_GetPrjDataDisturbanceMemory_BasePtr(uint8 RecIdx)
{
    return (&Dem_DistMemLocations[RecIdx].distMemPrjData);
}

DEM_INLINE uint8 Dem_GetPrjDataDisturbanceMemory_projspecData1(uint8 RecIdx)
{

    return (Dem_GetPrjDataDisturbanceMemory_BasePtr(RecIdx)->projspecData1);
}

DEM_INLINE uint8 Dem_SetPrjDataDisturbanceMemory_projspecData1(uint8 RecIdx , uint8 setVal)
{

    Dem_GetPrjDataDisturbanceMemory_BasePtr(RecIdx)->projspecData1 = setVal;
}

void Dem_GetNextDisturbanceMemProjData(uint8 distIdx, uint8* DestBuffer)
{

   *DestBuffer = Dem_GetPrjDataDisturbanceMemory_projspecData1(distIdx);
    DestBuffer++;
}

void  Dem_PrjDistMemCallbackOnDisturbance(Dem_EventIdType EventId)

{
}

#endif

