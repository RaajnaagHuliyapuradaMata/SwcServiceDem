#include "Std_Types.hpp"

#include "Dem.hpp"
#include "Rte_Dem.hpp"
#include "Dem_DebBase.hpp"
#include "Dem_DebSharing.hpp"
#include "Dem_DebArTime.hpp"
#include "Dem_DebCtrBaseClass.hpp"
#include "Dem_DebMonInternal.hpp"
#include "DemAppInterfaceX.hpp"
#include "Rte_Dem.hpp"
#include "FiM.hpp"
#include "Dem_Lib.hpp"

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
DEM_CFG_DEB_DEFINE_ALL_PARAMSETS
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

#if( (DEM_CFG_DEBCOUNTERBASECLASS == DEM_CFG_DEBCOUNTERBASECLASS_ON) && (!defined DEM_DEB_FORCE_CONST_CONFIG) )
#define DEM_START_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.hpp"
Dem_DebClass Dem_Cfg_DebClasses[DEM_CFG_DEB_NUMBEROFCLASSES] = DEM_CFG_DEB_CLASSES;
#define DEM_STOP_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.hpp"
#else
#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
const Dem_DebClass Dem_Cfg_DebClasses[DEM_CFG_DEB_NUMBEROFCLASSES] = DEM_CFG_DEB_CLASSES;
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
#endif

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
void Dem_DebSwitchToAlternativeParameters(void){
#if( (DEM_CFG_DEBCOUNTERBASECLASS == DEM_CFG_DEBCOUNTERBASECLASS_ON) && (!defined DEM_DEB_FORCE_CONST_CONFIG) )
    Dem_Cfg_DebClasses[DEM_DEBMETH_IDX_ARCTRBASECLASS].paramSet = &Dem_Cfg_DebCounterBaseClass_Paramsets[DemConf_DemRbDebounceCounterSet_Alternative];
#endif
}

Std_ReturnType Dem_DebSwitchToParameters(uint8 CounterParamSetId)
{
    Std_ReturnType ReturnValue = E_NOT_OK;

#if( ((DEM_CFG_DEBCOUNTERBASECLASS == DEM_CFG_DEBCOUNTERBASECLASS_ON) && (DEMRB_DEBOUNCECOUNTERSETS_SIZE != 0))\
    && (!defined DEM_DEB_FORCE_CONST_CONFIG) )

   if(CounterParamSetId < DEMRB_DEBOUNCECOUNTERSETS_SIZE)
   {
         Dem_Cfg_DebClasses[DEM_DEBMETH_IDX_ARCTRBASECLASS].paramSet = &Dem_Cfg_DebCounterBaseClass_Paramsets[CounterParamSetId];
        ReturnValue = E_OK;
   }
   else{

   }
#endif

   return ReturnValue;
}
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
