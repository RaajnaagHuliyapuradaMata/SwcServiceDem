

#ifndef DEM_BITARRAY_H
#define DEM_BITARRAY_H

#include "Dem_Types.hpp"
#include "Dem_Array.hpp"
#include "Dem_Lock.hpp"

#define DEM_BITARRAY_DATAELEMENTS( BITCOUNT )            ((((BITCOUNT)-1u) >> 5u)+1UL)

#define DEM_BITARRAY_DECLARE( VARNAME, BITCOUNT )        DEM_ARRAY_DECLARE(uint32, VARNAME, DEM_BITARRAY_DATAELEMENTS(BITCOUNT))
#define DEM_BITARRAY_DECLARE_CONST( VARNAME, BITCOUNT )  DEM_ARRAY_DECLARE(const uint32, VARNAME, DEM_BITARRAY_DATAELEMENTS(BITCOUNT))
#define DEM_BITARRAY_DEFINE( VARNAME, BITCOUNT )         DEM_ARRAY_DEFINE(uint32, VARNAME, DEM_BITARRAY_DATAELEMENTS(BITCOUNT))
#define DEM_BITARRAY_DEFINE_CONST( VARNAME, BITCOUNT )   DEM_ARRAY_DEFINE(const uint32, VARNAME, DEM_BITARRAY_DATAELEMENTS(BITCOUNT))

#define DEM_BITARRAY_FUNCPARAM(VARNAME)                  DEM_ARRAY_FUNCPARAM(uint32,VARNAME)
#define DEM_BITARRAY_CONSTFUNCPARAM(VARNAME)             DEM_ARRAY_CONSTFUNCPARAM(uint32,VARNAME)

#define DEM_BITARRAY_ELEMENT_BITSIZE \
    (DEM_SIZEOF_TYPE(uint32) * 8u)

DEM_INLINE void Dem_BitArraySetBit(DEM_BITARRAY_FUNCPARAM(buffer), uint32 bit_position)
{

   const uint32 element_pos = ((uint32)(bit_position / DEM_BITARRAY_ELEMENT_BITSIZE));
   const uint32 local_bitpos = ((uint32)(bit_position % DEM_BITARRAY_ELEMENT_BITSIZE));
   const uint32 mask =
            ((uint32) 1) << local_bitpos;

   buffer[element_pos] |= mask;
    return;
}

DEM_INLINE void Dem_BitArrayClearBit(DEM_BITARRAY_FUNCPARAM(buffer), uint32 bit_position)
{

   const uint32 element_pos = ((uint32)(bit_position / DEM_BITARRAY_ELEMENT_BITSIZE));
   const uint32 local_bitpos = ((uint32)(bit_position % DEM_BITARRAY_ELEMENT_BITSIZE));
   const uint32 mask =
            ((uint32) 1) << local_bitpos;

   buffer[element_pos] &= (uint32) ~ mask;
    return;
}

DEM_INLINE void Dem_BitArrayOverwriteBit(DEM_BITARRAY_FUNCPARAM(buffer)
   ,     uint32 bit_position, Dem_boolean_least will_bit_be_set)
{
   if(will_bit_be_set) {
        Dem_BitArraySetBit(buffer, bit_position);
   }else {
        Dem_BitArrayClearBit(buffer, bit_position);
   }
    return;
}

DEM_INLINE Dem_boolean_least Dem_BitArrayIsBitSet(DEM_BITARRAY_CONSTFUNCPARAM(buffer), uint32 bit_position)
{

   const uint32 element_pos = ((uint32)(bit_position / DEM_BITARRAY_ELEMENT_BITSIZE));
   const uint32 local_bitpos = ((uint32)(bit_position % DEM_BITARRAY_ELEMENT_BITSIZE));
   const uint32 mask =
            ((uint32) 1) << local_bitpos;

    return (buffer[element_pos] & mask) != 0u;
}

DEM_INLINE void Dem_BitArrayClearAll (DEM_BITARRAY_FUNCPARAM(buffer), uint32 number_of_bits)
{
   uint32 i;
   for(i = 0; i < DEM_BITARRAY_DATAELEMENTS(number_of_bits); i++) {
        buffer[i] = 0U;
   }
    return;
}

#endif

