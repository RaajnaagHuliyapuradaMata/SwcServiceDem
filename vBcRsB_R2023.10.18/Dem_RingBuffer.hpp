

#ifndef DEM_RINGBUFFER_LIB_H
#define DEM_RINGBUFFER_LIB_H

#include "Dem_Array.hpp"

typedef struct{
   uint16 end;
   uint16 lastEmptyLoc;
   uint16 nextEmptyLoc;
   uint16 RingBuffLocIt;
}Dem_RingBuffer;

#define DEM_DEFINE_RINGBUFFER(DATATYPE, NAME, SIZE)                       \
  static Dem_RingBuffer  NAME##_Handler; \
  static DEM_ARRAY_DEFINE(DATATYPE, NAME, SIZE+1u)

#define Dem_RingBuffer__Init(NAME)                                      \
{                                                                       \
   NAME##_Handler.end = (uint16)(DEM_SIZEOF_VAR(NAME) / DEM_SIZEOF_VAR(NAME[0])); \
   NAME##_Handler.lastEmptyLoc = NAME##_Handler.end - 1;                \
}

DEM_INLINE uint16 Dem_RingBuffer__next (const Dem_RingBuffer* rb, uint16 idx)
{
   uint16 result = idx + 1;
   if(result >= rb->end)
   {
      result = 0;
   }
   return result;
}

DEM_INLINE boolean Dem_RingBuffer__isEmpty (const Dem_RingBuffer* rb)
{
   return (Dem_RingBuffer__next (rb, rb->lastEmptyLoc) == rb->nextEmptyLoc);
}

DEM_INLINE boolean Dem_RingBuffer__isFull (const Dem_RingBuffer* rb)
{
   return (rb->lastEmptyLoc == rb->nextEmptyLoc);
}

DEM_INLINE boolean Dem_RingBuffer__insert (Dem_RingBuffer* rb, uint16* insertionIndex)
{
   if(Dem_RingBuffer__isFull (rb)) return FALSE;

   *insertionIndex = rb->nextEmptyLoc;
   rb->nextEmptyLoc = Dem_RingBuffer__next (rb, rb->nextEmptyLoc);

   return TRUE;
}

DEM_INLINE boolean Dem_RingBuffer__remove (Dem_RingBuffer* rb, uint16* removedIndex)
{
   if(Dem_RingBuffer__isEmpty (rb)) return FALSE;

   rb->lastEmptyLoc = Dem_RingBuffer__next (rb, rb->lastEmptyLoc);
   *removedIndex = rb->lastEmptyLoc;

   return TRUE;
}

DEM_INLINE void Dem_RingBuffer__NewIterator (Dem_RingBuffer* rb)
{
    rb->RingBuffLocIt = Dem_RingBuffer__next (rb, rb->lastEmptyLoc);
}
DEM_INLINE boolean Dem_RingBuffer__IteratorIsValid (const Dem_RingBuffer* rb)
{
    return (rb->RingBuffLocIt != rb->nextEmptyLoc);
}
DEM_INLINE void Dem_RingBuffer__IteratorNext (Dem_RingBuffer* rb)
{
    rb->RingBuffLocIt = Dem_RingBuffer__next(rb, rb->RingBuffLocIt);
}

#define Dem_RingBufferIndex__ISINBUFFER(BUFFERNAME, COMPAREFUNCTION, COMPAREVALUE, ISINBUFFER, LOC)             \
    ISINBUFFER = FALSE;                                                                                         \
   for(Dem_RingBuffer__NewIterator (&(BUFFERNAME##_Handler)); Dem_RingBuffer__IteratorIsValid (&(BUFFERNAME##_Handler));    \
    Dem_RingBuffer__IteratorNext (&(BUFFERNAME##_Handler)))                                                     \
   {                                                                                                           \
        if(COMPAREFUNCTION (&(BUFFERNAME[(BUFFERNAME##_Handler).RingBuffLocIt]), COMPAREVALUE))                 \
        {                                                                                                       \
            LOC = (BUFFERNAME##_Handler).RingBuffLocIt;                                                         \
            ISINBUFFER = TRUE;                                                                                  \
            break;                                                                                              \
        }                                                                                           \
   }

#endif

