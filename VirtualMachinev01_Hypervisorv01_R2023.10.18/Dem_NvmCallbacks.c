#include "Std_Types.hpp"

#include "Dem_NvmCallbacks.hpp"
#include "Dem_EventStatus.hpp"
#include "Dem_DisturbanceMemory.hpp"
#include "Dem_GenericNvData.hpp"
#include "Dem_EvMemBase.hpp"
#include "Dem_EvBuff.hpp"
#include "Dem_Cfg.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback(void* NvMBuffer, uint16_least LocId)
{

    DEM_MEMCPY(NvMBuffer, &Dem_EvMemEventMemory[LocId], DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType));
    return E_OK;
}

Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback(void* NvMBuffer, uint16_least LocId)
{

    DEM_MEMCPY(&Dem_EvMemEventMemory[LocId], NvMBuffer, DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType));
    return E_OK;
}

#if(DEM_CFG_FFPRESTORAGE_NONVOLATILE == DEM_CFG_FFPRESTORAGE_NONVOLATILE_ON)
Std_ReturnType Dem_PreStoredFFWriteRamBlockToNvCallback(void* NvMBuffer, uint16_least LocId)
{
    DEM_ENTERLOCK_MON();
   if((Dem_EvtBuffer.Locations[LocId].eventType == C_EVENTTYPE_PRESTORE) && (Dem_isEventIdValid(Dem_EvtBuffer.Locations[LocId].eventId)))
   {

        DEM_MEMCPY(NvMBuffer, &Dem_EvtBuffer.Locations[LocId], DEM_SIZEOF_TYPE(Dem_EvBuffEvent));
   }
   else{
        DEM_MEMSET(NvMBuffer, 0u, DEM_SIZEOF_TYPE(Dem_EvBuffEvent));
   }

    DEM_EXITLOCK_MON();
    return E_OK;
}

Std_ReturnType Dem_PreStoredFFReadRamBlockFromNvCallback(void* NvMBuffer, uint16_least LocId)
{
    DEM_ENTERLOCK_MON();

    DEM_MEMCPY(&Dem_EvtBuffer.Locations[LocId], NvMBuffer, DEM_SIZEOF_TYPE(Dem_EvBuffEvent));
    DEM_EXITLOCK_MON();
    return E_OK;
}
#endif

Std_ReturnType Dem_EventStatusByteWriteRamBlockToNvCallback(void* NvMBuffer)
{

    DEM_MEMCPY(NvMBuffer, &Dem_AllEventsStatusByte, DEM_SIZEOF_VAR(Dem_AllEventsStatusByte));
    return E_OK;
}

Std_ReturnType Dem_EventStatusByteReadRamBlockFromNvCallback(void* NvMBuffer)
{

   DEM_MEMCPY(&Dem_AllEventsStatusByte, NvMBuffer, DEM_SIZEOF_VAR(Dem_AllEventsStatusByte));

#if DEM_CFG_CUSTOMIZABLEDTCSTATUSBYTE

    DEM_MEMCPY(&Dem_AllEventsStatusByteCust, NvMBuffer, DEM_SIZEOF_VAR(Dem_AllEventsStatusByte));
#endif

    return E_OK;
}

#if(DEM_CFG_ALLOW_HISTORY == DEM_CFG_ALLOW_HISTORY_ON)
Std_ReturnType Dem_HistoryStatusByteWriteRamBlockToNvCallback(void* NvMBuffer)
{
    DEM_ENTERLOCK_MON();

    DEM_MEMCPY(NvMBuffer, &Dem_AllEventsHistoryStatus, DEM_SIZEOF_VAR(Dem_AllEventsHistoryStatus));
    DEM_EXITLOCK_MON();
    return E_OK;
}

Std_ReturnType Dem_HistoryStatusByteReadRamBlockFromNvCallback(void* NvMBuffer)
{
    DEM_ENTERLOCK_MON();

    DEM_MEMCPY(&Dem_AllEventsHistoryStatus, NvMBuffer, DEM_SIZEOF_VAR(Dem_AllEventsHistoryStatus));
    DEM_EXITLOCK_MON();
    return E_OK;
}
#endif

#if(DEM_CFG_DISTURBANCE_MEMORY == DEM_CFG_DISTURBANCE_MEMORY_ON)
Std_ReturnType Dem_DistMemWriteRamBlockToNvCallback(void* NvMBuffer)
{
    DEM_ENTERLOCK_MON();

    DEM_MEMCPY(NvMBuffer, &Dem_DistMemLocations, DEM_SIZEOF_VAR(Dem_DistMemLocations));
    DEM_EXITLOCK_MON();
    return E_OK;
}

Std_ReturnType Dem_DistMemReadRamBlockFromNvCallback(void* NvMBuffer)
{
    DEM_ENTERLOCK_MON();

    DEM_MEMCPY(&Dem_DistMemLocations, NvMBuffer, DEM_SIZEOF_VAR(Dem_DistMemLocations));
    DEM_EXITLOCK_MON();
    return E_OK;
}
#endif

Std_ReturnType Dem_GenericNVDataWriteRamBlockToNvCallback(void* NvMBuffer)
{
    DEM_MEMCPY(NvMBuffer, &Dem_GenericNvData, DEM_SIZEOF_VAR(Dem_GenericNvData));
    return E_OK;
}

Std_ReturnType Dem_GenericNVDataReadRamBlockFromNvCallback(void* NvMBuffer)
{

    DEM_MEMCPY(&Dem_GenericNvData, NvMBuffer, DEM_SIZEOF_VAR(Dem_GenericNvData));
    return E_OK;
}

#if(DEM_CFG_EVT_INDICATOR == DEM_CFG_EVT_INDICATOR_ON)
Std_ReturnType Dem_EventIndicatorWriteRamBlockToNvCallback(void* NvMBuffer)
{
    DEM_ENTERLOCK_MON();

    DEM_MEMCPY(NvMBuffer, &Dem_AllEventsIndicatorState, DEM_SIZEOF_VAR(Dem_AllEventsIndicatorState));
    DEM_EXITLOCK_MON();
    return E_OK;
}

Std_ReturnType Dem_EventIndicatorReadRamBlockFromNvCallback(void* NvMBuffer)
{
    DEM_ENTERLOCK_MON();

    DEM_MEMCPY(&Dem_AllEventsIndicatorState, NvMBuffer, DEM_SIZEOF_VAR(Dem_AllEventsIndicatorState));
    DEM_EXITLOCK_MON();
    return E_OK;
}
#endif

#if(DEM_CFG_ERASE_ALL_DATA_SUPPORTED == DEM_CFG_ERASE_ALL_WITH_HASHID_CHECK)
Std_ReturnType Dem_HashIdWriteRamBlockToNvCallback(void* NvMBuffer)
{

    DEM_MEMCPY(NvMBuffer, &Dem_HashIdInNvm, DEM_SIZEOF_VAR(Dem_HashIdInNvm));
    return E_OK;
}

Std_ReturnType Dem_HashIdReadRamBlockFromNvCallback(void* NvMBuffer)
{

    DEM_MEMCPY(&Dem_HashIdInNvm, NvMBuffer, DEM_SIZEOF_VAR(Dem_HashIdInNvm));
    return E_OK;
}
#endif

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
