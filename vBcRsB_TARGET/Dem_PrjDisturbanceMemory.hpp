
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef DEM_PRJ_DISTURBANCEMEMORY_H
#define DEM_PRJ_DISTURBANCEMEMORY_H

#include "Dem_cfg_DistMem.hpp"
#include "Dem_Types.hpp"

#if(DEM_CFG_DIST_MEM_CALLBACK_ON_DISTURBANCE)

typedef struct{

   uint8 projspecData1;
}Dem_DistMemPrjDataType;

#define DEM_CFG_DIST_MEM_PRJ_DATA_SIZE 1u

void Dem_GetNextDisturbanceMemProjData(uint8 distIdx, uint8* DestBuffer);

void  Dem_PrjDistMemCallbackOnDisturbance(Dem_EventIdType EventId);

#endif
#endif
