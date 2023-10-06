

#ifndef DEM_ENVDID_H
#define DEM_ENVDID_H

#include "Dem_Types.hpp"
#include "Dem_Array.hpp"
#include "Dem_EnvDataElement.hpp"
#include "Dem_Cfg_EnvDid.hpp"

typedef struct{
   uint16 dataElementIndex;
   uint16 identifier;
}Dem_EnvDid;
#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
extern const uint8 Dem_Cfg_EnvDid2DataElement[];
DEM_ARRAY_DECLARE_CONST(Dem_EnvDid, Dem_Cfg_EnvDid, DEM_CFG_ENVDID_ARRAYLENGTH);
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

DEM_INLINE void Dem_EnvDIDCapture(uint8 didId, uint8** start, const uint8* end, const Dem_InternalEnvData *internalEnvData)
{
   uint16_least i;
   for(i = Dem_Cfg_EnvDid[didId - 1].dataElementIndex;
   	 i < Dem_Cfg_EnvDid[didId].dataElementIndex;
   	 i++)
   {
   	Dem_EnvDACapture(Dem_Cfg_EnvDid2DataElement[i], start, end, internalEnvData);
   }
}

DEM_INLINE Dem_boolean_least Dem_EnvDIDRetrieveRaw(uint8 didId, uint8** start, const uint8* end, const uint8** src, const Dem_InternalEnvData* internalEnvData)
{
   uint16_least i;

   for(i = Dem_Cfg_EnvDid[didId - 1].dataElementIndex;
   	 i < Dem_Cfg_EnvDid[didId].dataElementIndex;
   	 i++)
   {
   	if(!Dem_EnvDARetrieve(Dem_Cfg_EnvDid2DataElement[i], start, end, src, internalEnvData))
   	{
   		return FALSE;
   	}
   }
   return TRUE;
}

DEM_INLINE Dem_boolean_least Dem_EnvDIDRetrieve(uint8 didId, uint8** start, const uint8* end, const uint8** src, const Dem_InternalEnvData* internalEnvData)
{
   if((end - *start) < 2)
   {
   	return FALSE;
   }
   **start = (uint8) ((Dem_Cfg_EnvDid[didId].identifier / 256u) & 0xFFu);
   (*start)++;
   **start = (uint8)((Dem_Cfg_EnvDid[didId].identifier) & 0xFFu);
   (*start)++;

   return Dem_EnvDIDRetrieveRaw(didId, start, end, src, internalEnvData);
}

DEM_INLINE Dem_boolean_least Dem_EnvDIDRetrieveSpecificDid (uint8 didId, uint16 identifier, uint8** start, const uint8* end, const uint8** src, const Dem_InternalEnvData* internalEnvData)
{
   uint16_least i;

   if(Dem_Cfg_EnvDid[didId].identifier == identifier)
   {
   	for(i = Dem_Cfg_EnvDid[didId - 1].dataElementIndex;
   		 i < Dem_Cfg_EnvDid[didId].dataElementIndex;
   		 i++)
   	{
   		if(!Dem_EnvDARetrieve(Dem_Cfg_EnvDid2DataElement[i], start, end, src, internalEnvData))
   		{
   			return FALSE;
   		}
   	}
   	return TRUE;
   }
   else
   {
   	for(i = Dem_Cfg_EnvDid[didId - 1].dataElementIndex;
   		 i < Dem_Cfg_EnvDid[didId].dataElementIndex;
   		 i++)
   	{
   		*src += Dem_EnvDAGetSizeOf(Dem_Cfg_EnvDid2DataElement[i]);
   	}
   }

   return FALSE;
}

DEM_INLINE uint16 Dem_EnvDIDGetSize(uint8 didId)
{
   uint16_least i;
   uint16 byteSize = 2;

   for(i = Dem_Cfg_EnvDid[didId - 1].dataElementIndex;
   	 i < Dem_Cfg_EnvDid[didId].dataElementIndex;
   	 i++)
   {
   	byteSize += Dem_EnvDAGetSizeOf(Dem_Cfg_EnvDid2DataElement[i]);
   }
   return byteSize;
}

#endif
