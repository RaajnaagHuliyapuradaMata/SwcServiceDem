

#ifndef DEM_EVMEMAPI_H
#define DEM_EVMEMAPI_H

#include "Dem_EvMemTypes.hpp"
#include "Dem_Cfg_EvMem.hpp"

typedef struct{

  Dem_DtcIdType            DtcId;
  Dem_DTCOriginType        DTCOrigin;
  uint8                    ReqCounter;

  uint8                    DemCounter;
  boolean                  IsValid;
  Dem_EvMemEventMemoryType EventMemory;
}Dem_EvMemDTCRecordType;

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"
extern Dem_EvMemDTCRecordType Dem_EvMemDTCRecord;
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

void Dem_EvMemApiMainFunction(void);

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

DEM_INLINE Dem_boolean_least Dem_EvMemIsDtcKindValid (Dem_DTCKindType DTCKind)
{
    return (DTCKind == DEM_DTC_KIND_ALL_DTCS);
}

DEM_INLINE Dem_boolean_least Dem_EvMemIsDtcOriginValid (Dem_DTCOriginType  *DTCOrigin)
{
   if(*DTCOrigin == DEM_DTC_ORIGIN_USERDEFINED_MEMORY)
   {
        *DTCOrigin = DEM_DTC_ORIGIN_SECONDARY_MEMORY;
   }
    return (
               (*DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY)
#if DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY > 0
            || (*DTCOrigin == DEM_DTC_ORIGIN_SECONDARY_MEMORY)
#endif
#if(DEM_CFG_MAX_NUMBER_EVENT_ENTRY_MIRROR > 0) || DEM_CFG_EVMEM_SHADOW_MEMORY_SUPPORTED
            || (*DTCOrigin == DEM_DTC_ORIGIN_MIRROR_MEMORY)
#endif
           );
}

#endif
