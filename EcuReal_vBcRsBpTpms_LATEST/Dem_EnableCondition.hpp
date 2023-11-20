

#ifndef DEM_ENABLECONDITION_H
#define DEM_ENABLECONDITION_H

#include "Dem_Types.hpp"
#include "Dem_Cfg_EnableCondition.hpp"

#if(DEM_CFG_ENABLECONDITION == DEM_CFG_ENABLECONDITION_ON)

typedef struct{
   Dem_EnCoList isActive;
}Dem_EnCoState;

#define DEM_START_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.hpp"
extern Dem_EnCoState Dem_EnCoAllStates;
#define DEM_STOP_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.hpp"

#endif

DEM_INLINE Dem_boolean_least Dem_EnCoAreAllFulfilled (Dem_EnCoList enableConditionList)
{
#if(DEM_CFG_ENABLECONDITION == DEM_CFG_ENABLECONDITION_ON)
   return ((enableConditionList & Dem_EnCoAllStates.isActive) == enableConditionList);
#else
   DEM_UNUSED_PARAM(enableConditionList);
   return TRUE;
#endif
}

DEM_INLINE Dem_boolean_least Dem_EnCoFulfilled (Dem_EnCoList enableConditionBitmask)
{
    return Dem_EnCoAreAllFulfilled (enableConditionBitmask);
}

#if(DEM_CFG_ENABLECONDITION == DEM_CFG_ENABLECONDITION_ON)
void Dem_EnCoCallbacks(void);
#endif

#endif

