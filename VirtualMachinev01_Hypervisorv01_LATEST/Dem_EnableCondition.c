#include "Std_Types.hpp"

#include "Dem.hpp"
#include "Ara_Dem.hpp"
#include "Dem_Events.hpp"
#include "Dem_EnableCondition.hpp"
#include "Dem_Lock.hpp"
#include "Dem_Lok_Det.hpp"
#include "Dem_Cfg_Events_DataStructures.hpp"

#define DEM_START_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.hpp"
#if(DEM_CFG_ENABLECONDITION == DEM_CFG_ENABLECONDITION_ON)
Dem_EnCoState Dem_EnCoAllStates = { DEM_CFG_ENCO_INITIALSTATE };
static Dem_EnCoList Dem_EnCoReEnabledBitMask = 0;
#endif
#define DEM_STOP_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
Std_ReturnType Dem_SetEnableCondition (uint8 EnableConditionID
   ,     boolean ConditionFulfilled)
{
#if(DEM_CFG_ENABLECONDITION == DEM_CFG_ENABLECONDITION_ON)

    Dem_EnCoList enableConditionBitmask = (Dem_EnCoList)(1u << EnableConditionID);
    Dem_boolean_least isEnCoAlreadyFulfilled;

   if(EnableConditionID >=  DEM_ENABLECONDITION_COUNT)
   {
        DEM_DET(DEM_DET_APIID_SETENABLECONDITION, DEM_E_WRONG_CONFIGURATION);
        DEM_ASSERT_ISNOTLOCKED();
        return E_NOT_OK;
   }

    DEM_ENTERLOCK_MON();

   if(ConditionFulfilled)
   {
        isEnCoAlreadyFulfilled = Dem_EnCoFulfilled (enableConditionBitmask);

        if(!isEnCoAlreadyFulfilled)
        {
            Dem_EnCoReEnabledBitMask |= enableConditionBitmask;
        }
        Dem_EnCoAllStates.isActive |= enableConditionBitmask;
   }
   else{
        Dem_EnCoAllStates.isActive &= (Dem_EnCoList)(~enableConditionBitmask);
   }

    DEM_EXITLOCK_MON();

    return E_OK;

#else
    DEM_UNUSED_PARAM(EnableConditionID);
    DEM_UNUSED_PARAM(ConditionFulfilled);
    return E_NOT_OK;
#endif
}

#if(DEM_CFG_ENABLECONDITION == DEM_CFG_ENABLECONDITION_ON)
void Dem_EnCoCallbacks(void){
    Dem_EventIdIterator eventIt;
    Dem_EventIdType eventId;
    Dem_EnCoList enableCondition;
    Dem_EnCoList currentEnCoReEnabledBitMask;

   if(Dem_EnCoReEnabledBitMask != 0)
   {
        DEM_ENTERLOCK_MON();

        currentEnCoReEnabledBitMask = Dem_EnCoReEnabledBitMask;
        Dem_EnCoReEnabledBitMask = 0;

        DEM_EXITLOCK_MON();

        for(Dem_EventIdIteratorNew(&eventIt); Dem_EventIdIteratorIsValid(&eventIt); Dem_EventIdIteratorNext(&eventIt))
        {
            eventId = Dem_EventIdIteratorCurrent(&eventIt);
            enableCondition = Dem_EvtParam_GetEnableConditions(eventId);

            if((enableCondition != 0) && ((currentEnCoReEnabledBitMask & enableCondition) != 0))
            {
                if(Dem_EnCoAreAllFulfilled(enableCondition))
                {
                    DEM_ENTERLOCK_MON();
                    Dem_EvtSetInitMonitoring (eventId, DEM_INIT_MONITOR_REENABLED);
                    DEM_EXITLOCK_MON();
                }
            }
        }
   }
}
#endif
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
