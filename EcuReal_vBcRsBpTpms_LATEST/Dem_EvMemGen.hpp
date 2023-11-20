

#ifndef DEM_EVMEMGEN_H
#define DEM_EVMEMGEN_H

#include "Dem_EvMemGenTypes.hpp"
#include "Dem_EvMemTypes.hpp"
#include "Dem_EvMemBase.hpp"
#include "Dem_DTCs.hpp"
#include "Dem_GenericNvData.hpp"

#define DEM_EVMEMGEN_MEMORY_BASE   Dem_GenericNvData

#if DEM_CFG_EVMEMGENERIC_SUPPORTED
#define DEM_EVMEMGEN_GET(OBJ)      (OBJ)
#define DEM_EVMEMGEN_SET(OBJ,VAL)  (OBJ) = (VAL)
#define DEM_EVMEMGEN_CLEAROBJ(OBJ) DEM_EVMEM_CLEAROBJ(OBJ)
#else
#define DEM_EVMEMGEN_GET(OBJ)      0
#define DEM_EVMEMGEN_SET(OBJ,VAL)  do {}while(0)
#define DEM_EVMEMGEN_CLEAROBJ(OBJ) do {}while(0)
#endif

DEM_INLINE Dem_DtcIdType Dem_EvMemGenGetDtcIdByOccIndex(uint32 OccIndex)
{
#if DEM_CFG_EVMEMGENERIC_SUPPORTED
    return DEM_EVMEMGEN_GET(DEM_EVMEMGEN_MEMORY_BASE.DtcIdsByOccurrenceTime[OccIndex]);
#else
    DEM_UNUSED_PARAM(OccIndex);
    return 0;
#endif
}

DEM_INLINE void Dem_EvMemGenSetDtcByOccIndex(Dem_DtcIdType DtcId,uint32 OccIndex)
{
#if DEM_CFG_EVMEMGENERIC_SUPPORTED
    DEM_EVMEMGEN_SET(DEM_EVMEMGEN_MEMORY_BASE.DtcIdsByOccurrenceTime[OccIndex],DtcId);
#else
    DEM_UNUSED_PARAM(DtcId);
    DEM_UNUSED_PARAM(OccIndex);
#endif
}

DEM_INLINE Dem_DTCOriginType Dem_EvMemGenGetDtcOrginFromMemId(uint16_least MemId)
{
   Dem_DTCOriginType DtcOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;

   if(Dem_LibGetParamBool(DEM_CFG_EVMEM_SECONDARY_MEMORY_SUPPORTED))
   {
      if(MemId == DEM_CFG_EVMEM_MEMID_SECONDARY)
      {
         DtcOrigin = DEM_DTC_ORIGIN_SECONDARY_MEMORY;
      }
   }

   if(Dem_LibGetParamBool(DEM_CFG_EVMEM_MIRROR_MEMORY_SUPPORTED))
   {

      if(MemId == DEM_CFG_EVMEM_MEMID_MIRROR)
      {
         DtcOrigin = DEM_DTC_ORIGIN_MIRROR_MEMORY;
      }
   }

   return DtcOrigin;
}

DEM_INLINE void Dem_EvMemGenReportEvent(Dem_EventIdType EventId, uint32 FirstOccIndex, uint32 RecntOccIndex)
{
   Dem_DtcIdType DtcId;

   DtcId = Dem_DtcIdFromEventId (EventId);

   if(Dem_isDtcIdValid (DtcId))
   {

      if(!Dem_isDtcIdValid(Dem_EvMemGenGetDtcIdByOccIndex(FirstOccIndex)))
      {

         Dem_EvMemGenSetDtcByOccIndex(DtcId,FirstOccIndex);

         Dem_NvMWriteBlockOnShutdown(DEM_NVM_ID_DEM_GENERIC_NV_DATA);
      }

      if(Dem_EvMemGenGetDtcIdByOccIndex(RecntOccIndex) != DtcId)
      {

         Dem_EvMemGenSetDtcByOccIndex(DtcId,RecntOccIndex);

         Dem_NvMWriteBlockOnShutdown(DEM_NVM_ID_DEM_GENERIC_NV_DATA);
      }
   }
}

DEM_INLINE void Dem_EvMemGenReportFailedEvent(Dem_EventIdType EventId)
{
   if(!Dem_GetEvMemLockInternal())
   {

       if( Dem_EvtParam_GetEventIsStoredInPrimary(EventId) )
       {

           DEM_ENTERLOCK_MON();
           Dem_EvMemGenReportEvent(EventId,DEM_FIRST_FAILED_DTC,DEM_MOST_RECENT_FAILED_DTC);
           DEM_EXITLOCK_MON();
       }
   }
}

DEM_INLINE void Dem_EvMemGenReportConfirmedEvent(Dem_EventIdType EventId, uint16_least MemId)
{

   if(MemId == DEM_CFG_EVMEM_MEMID_PRIMARY)
   {

      Dem_EvMemGenReportEvent(EventId,DEM_FIRST_DET_CONFIRMED_DTC,DEM_MOST_REC_DET_CONFIRMED_DTC);
   }
}

DEM_INLINE void Dem_EvMemGenClearDtcByOccurrenceTime(Dem_DTCOriginType DtcOrigin)
{
   DEM_UNUSED_PARAM(DtcOrigin);

   if(DtcOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY)
   {

      DEM_ENTERLOCK_MON();
      DEM_EVMEMGEN_CLEAROBJ(DEM_EVMEMGEN_MEMORY_BASE.DtcIdsByOccurrenceTime);
      DEM_EXITLOCK_MON();

      Dem_NvMClearBlockByWrite(DEM_NVM_ID_DEM_GENERIC_NV_DATA);
   }
}

DEM_INLINE Dem_DtcIdType Dem_EvMemGenGetLastFailedDtcFromGenNvData(void){
   return Dem_EvMemGenGetDtcIdByOccIndex(DEM_MOST_RECENT_FAILED_DTC);
}

DEM_INLINE Dem_DtcIdType Dem_EvMemGenGetLastConfirmedDtcFromGenNvData(void){
   return Dem_EvMemGenGetDtcIdByOccIndex(DEM_MOST_REC_DET_CONFIRMED_DTC);
}

DEM_INLINE void Dem_EvMemGenSetOverflow(Dem_DTCOriginType DtcOrigin)
{
#if DEM_CFG_EVMEMGENERIC_SUPPORTED
    DEM_EVMEMGEN_SET(DEM_EVMEMGEN_MEMORY_BASE.Overflow[DtcOrigin],TRUE);
#else
    DEM_UNUSED_PARAM(DtcOrigin);
#endif
}

DEM_INLINE boolean Dem_EvMemGenIsOverflow(Dem_DTCOriginType DtcOrigin)
{
#if DEM_CFG_EVMEMGENERIC_SUPPORTED
    return (boolean)DEM_EVMEMGEN_GET(DEM_EVMEMGEN_MEMORY_BASE.Overflow[DtcOrigin]);
#else
    DEM_UNUSED_PARAM(DtcOrigin);
    return (boolean)0;
#endif
}

DEM_INLINE void Dem_EvMemGenReportEventMemoryOverflowByOrigin(Dem_DTCOriginType DtcOrigin)
{
   if(!Dem_EvMemGenIsOverflow(DtcOrigin))
   {
      Dem_EvMemGenSetOverflow(DtcOrigin);
      Dem_NvMWriteBlockOnShutdown(DEM_NVM_ID_DEM_GENERIC_NV_DATA);
   }
}

DEM_INLINE void Dem_EvMemGenClearOverflow(Dem_DTCOriginType DtcOrigin)
{
#if DEM_CFG_EVMEMGENERIC_SUPPORTED
    DEM_EVMEMGEN_SET(DEM_EVMEMGEN_MEMORY_BASE.Overflow[DtcOrigin],FALSE);
    Dem_NvMClearBlockByWrite(DEM_NVM_ID_DEM_GENERIC_NV_DATA);
#else
    DEM_UNUSED_PARAM(DtcOrigin);
#endif
}

DEM_INLINE void Dem_EvMemGenInitEventMemoryGen(void){
    Dem_NvmResultType NvmResult;

   if(Dem_NvMIsInvalidateAllNVMBlocksRequested())
   {

        DEM_MEMSET(&Dem_GenericNvData, 0x00, sizeof(Dem_GenericNvDataType));
        Dem_NvMClearBlockByInvalidate(DEM_NVM_ID_DEM_GENERIC_NV_DATA);
   }
   else{

        NvmResult = Dem_NvmGetStatus (DEM_NVM_ID_DEM_GENERIC_NV_DATA);

        if(NvmResult == DEM_NVM_INVALID)
        {

            DEM_EVMEMGEN_CLEAROBJ(DEM_EVMEMGEN_MEMORY_BASE.DtcIdsByOccurrenceTime);
        }

        if(NvmResult == DEM_NVM_SUCCESS)
        {
            uint32 idx;

            for(idx = 0; idx < DEM_EVMEMGEN_DTCIDS_BY_OCCURRENCE_TIME_ARRAYSIZE; idx++)
            {
                if(!(Dem_isDtcIdValid(Dem_EvMemGenGetDtcIdByOccIndex(idx)) ||
                        (Dem_EvMemGenGetDtcIdByOccIndex(idx) == DEM_DTCID_INVALID)))
                {
                    NvmResult = DEM_NVM_FAILED;
                }
            }
        }

        if((NvmResult != DEM_NVM_SUCCESS) && (NvmResult != DEM_NVM_INVALID))
        {

            DEM_EVMEMGEN_CLEAROBJ(DEM_EVMEMGEN_MEMORY_BASE.DtcIdsByOccurrenceTime);
            Dem_NvMWriteBlockOnShutdown(DEM_NVM_ID_DEM_GENERIC_NV_DATA);
        }
   }
}

#endif
