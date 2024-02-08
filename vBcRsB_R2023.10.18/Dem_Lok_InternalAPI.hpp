

#ifndef DEM_PRV_INTERNALAPI_H
#define DEM_PRV_INTERNALAPI_H

#include "Dem_DTCs.hpp"
#include "Dem_Cfg.hpp"
#include "Dem_EnvMain.hpp"
#include "Dem_Cfg_Events_DataStructures.hpp"

DEM_INLINE uint8 Dem_InternalGetEventPriority (Dem_EventIdType EventId)
{
     return Dem_EvtParam_GetEventPriority(EventId);
}

DEM_INLINE Dem_boolean_least Dem_InternalEvtIsSuppressed (Dem_EventIdType EventId)
{
    return Dem_EvtIsSuppressed(EventId);
}

DEM_INLINE Dem_boolean_least Dem_InternalEvtRequestsWarningIndicator (Dem_EventIdType EventId)
{
    return Dem_EvtParam_GetRequestsWarningIndicator(EventId);
}

DEM_INLINE uint16_least Dem_InternalGetEventMemOccurrenceCounterByPtr(const Dem_EvMemEventMemoryType *EventMemory)
{
    return Dem_EvMemGetEventMemOccurrenceCounterByPtr(EventMemory);
}

DEM_INLINE uint16_least Dem_InternalGetEventMemOccurrenceCounter(uint16_least LocId)
{
    return Dem_InternalGetEventMemOccurrenceCounterByPtr(&Dem_EvMemEventMemory[LocId]);
}

DEM_INLINE Dem_EventIdType Dem_InternalGetEventMemEventId (uint16_least LocId)
{
    return Dem_EvMemGetEventMemEventId(LocId);
}

DEM_INLINE uint32 Dem_InternalGetEventMemTimeId (uint16_least LocId)
{
     return Dem_EvMemGetEventMemTimeId(LocId);
}

DEM_INLINE uint16_least Dem_InternalGetEventMemAgingCounterByPtr(const Dem_EvMemEventMemoryType *EventMemory)
{
    return Dem_EvMemGetEventMemAgingCounterByPtr(EventMemory);
}

DEM_INLINE Dem_boolean_least Dem_InternalIsEvMemLocIdValid(uint16_least LocId)
{
    return Dem_EvMemIsEventMemLocIdValid(LocId);
}

DEM_INLINE void Dem_InternalForceClrEvMemLocOnDisplacement(uint16_least LocId)
{
    Dem_EvMemForceClearEventMemoryLocation(LocId, DEM_EVMEM_WRITEMASK_CLEAR, DEM_EVMEM_ACTIONTYPE_DISPLACEMENT);
}

DEM_INLINE Dem_DtcCodeType Dem_InternalGetDtcCode (Dem_DtcIdType dtcId)
{
    return Dem_GetDtcCode(dtcId);
}

DEM_INLINE Dem_boolean_least Dem_InternalDtcIdIsValid (Dem_DtcIdType dtcId)
{
    return Dem_isDtcIdValid (dtcId);
}

DEM_INLINE Dem_DtcIdType  Dem_InternalDtcIdFromEventId (Dem_EventIdType eventId)
{
    return Dem_DtcIdFromEventId (eventId);
}

#if( (DEM_BFM_ENABLED == DEM_BFM_ON) && (RBA_DEMBFM_ENABLE_DIRECT_ACCESS_INTERFACE == DEM_BFM_ON) )
DEM_INLINE rba_DemBfm_ReturnType Dem_InternalBfmRecordGetDirectReadAccess( rba_DemBfm_LocationDataType location
   ,     rba_DemBfm_Record const **bfmRecord, boolean *isMarkedForDeletion, boolean *isEmpty, boolean *isModified
   ,     boolean *isLockedPerm, boolean *isLockedTemp )
{
   return rba_DemBfm_RecordGetDirectReadAccess(location, bfmRecord, isMarkedForDeletion, isEmpty
   ,     isModified, isLockedPerm, isLockedTemp );
}
#endif

DEM_INLINE void Dem_InternalEnvCopyRawFF(Dem_EventIdType EventId
   ,     uint8* dest
   ,     uint16 destSize
   ,     uint8 ffIndex
   ,     const uint8* src)
{
    Dem_EnvCopyRawFF(EventId, dest, destSize, ffIndex, src);
}

#ifndef DEM_DTCID_ARRAYLENGTH
#error "DEM_DTCID_ARRAYLENGTH is not available in the project, please check if it is modified or deleted "
#else
#define DEM_INTERNAL_DTCID_ARRAYLENGTH  DEM_DTCID_ARRAYLENGTH
#endif

#endif

