

#ifndef DEM_DISTURBANCEMEMORY_H
#define DEM_DISTURBANCEMEMORY_H

#include "Dem_Types.hpp"

#include "Dem_Array.hpp"
#include "rba_DiagLib_Bits8.hpp"
#include "rba_DiagLib_Bits16.hpp"
#include "Dem_Events.hpp"
#include "Dem_Cfg_DistMem.hpp"
#include "Dem_Cfg_EnvMain.hpp"
#if(DEM_CFG_DIST_MEM_CALLBACK_ON_DISTURBANCE == DEM_CFG_DIST_MEM_CALLBACK_ON_DISTURBANCE_ON)
#include "Dem_PrjDisturbanceMemory.hpp"
#endif

#if(DEM_CFG_DISTURBANCE_MEMORY == DEM_CFG_DISTURBANCE_MEMORY_ON)

#define DEM_DIST_MEM_BP_FLAG_TEST_CURRENT      (0u)
#define DEM_DIST_MEM_BP_FLAG_TEST_DISTURBED    (1u)
#define DEM_DIST_MEM_BP_UPDATE_EXTN_DATA       (2u)

typedef uint8 Dem_DistMemLocationStatusType;
#define DEM_DIST_MEM_ISBITSET      rba_DiagLib_Bit8IsBitSet
#define DEM_DIST_MEM_OVERWRITEBIT  rba_DiagLib_Bit8OverwriteBit
#define DEM_DIST_MEM_CLEARBIT      rba_DiagLib_Bit8ClearBit
#define DEM_DIST_MEM_SETBIT        rba_DiagLib_Bit8SetBit

#define DEM_DIST_MEM_INVALID_LOC  		0u

#define DEM_DIST_MEM_INIT_STATUS_BYTE	0u

#define DEM_DIST_MEM_NEW_ENTRY_STATUS_BYTE ((uint8)(1u<<DEM_DIST_MEM_BP_FLAG_TEST_CURRENT) | (uint8)(1u<<DEM_DIST_MEM_BP_UPDATE_EXTN_DATA))

#define DEM_DIST_MEM_MAX_DIST_CTR_LIMIT  255u

typedef struct{
   uint8 disturbanceCtr;
#if(DEM_CFG_DIST_MEM_EXTENDED_DATA_USED == STD_ON)
   uint8 extData[DEM_CFG_DIST_MEM_EXT_DATA_SIZE];
#endif
   Dem_EventIdType eventId;
   #if(DEM_CFG_DEBUGDATA != DEM_CFG_DEBUGDATA_OFF)
   Dem_DebugDataType debug0;
   Dem_DebugDataType debug1;
   #endif
#if(DEM_CFG_DIST_MEM_CALLBACK_ON_DISTURBANCE == DEM_CFG_DIST_MEM_CALLBACK_ON_DISTURBANCE_ON)
   Dem_DistMemPrjDataType distMemPrjData;
#endif
}Dem_DistMemLocationType;

#define DEM_START_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.hpp"
DEM_ARRAY_DECLARE( Dem_DistMemLocationType, Dem_DistMemLocations, (DEM_CFG_DISTURBANCE_MEMORY_ARRAYLENGTH));
#define DEM_STOP_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.hpp"
extern uint8 Dem_DistMemNextEmptyIndex;
#define DEM_STOP_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"
DEM_ARRAY_DECLARE( Dem_DistMemLocationStatusType, Dem_DistMemLocationsStatus, (DEM_CFG_DISTURBANCE_MEMORY_ARRAYLENGTH));
extern uint8 Dem_DistMemReadIndex;
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

DEM_INLINE Dem_EventIdType Dem_DistMemGetStoredEventId (uint8 DistMemIndex)
{
   return Dem_DistMemLocations[DistMemIndex].eventId;
}

DEM_INLINE void Dem_DistMemSetStoredEventId (uint8 DistMemIndex , Dem_EventIdType EventId)
{
   Dem_DistMemLocations[DistMemIndex].eventId = EventId;
}

DEM_INLINE uint8 Dem_DistMemGetStoredDisturbanceCounter (uint8 DistMemIndex)
{
   return Dem_DistMemLocations[DistMemIndex].disturbanceCtr;
}

DEM_INLINE Dem_boolean_least Dem_DistMemEvtGetTestCurrent_Flag (uint8 DistMemIndex)
{
   return DEM_DIST_MEM_ISBITSET (Dem_DistMemLocationsStatus[DistMemIndex], DEM_DIST_MEM_BP_FLAG_TEST_CURRENT);
}

DEM_INLINE void Dem_DistMemEvtWriteTestCurrent_Flag (uint8 DistMemIndex , Dem_boolean_least setBit )
{
   DEM_DIST_MEM_OVERWRITEBIT (&Dem_DistMemLocationsStatus[DistMemIndex], DEM_DIST_MEM_BP_FLAG_TEST_CURRENT , setBit);
}

DEM_INLINE Dem_boolean_least Dem_DistMemEvtGetTestDisturbed_Flag (uint8 DistMemIndex)
{
   return DEM_DIST_MEM_ISBITSET (Dem_DistMemLocationsStatus[DistMemIndex], DEM_DIST_MEM_BP_FLAG_TEST_DISTURBED);
}

DEM_INLINE void Dem_DistMemEvtSetTestDisturbed_Flag (uint8 DistMemIndex)
{
   DEM_DIST_MEM_SETBIT (&Dem_DistMemLocationsStatus[DistMemIndex], DEM_DIST_MEM_BP_FLAG_TEST_DISTURBED);
}

DEM_INLINE Dem_boolean_least Dem_DistMemIsUpdateEvtExtDataNecessary (uint8 DistMemIndex)
{
   return DEM_DIST_MEM_ISBITSET (Dem_DistMemLocationsStatus[DistMemIndex], DEM_DIST_MEM_BP_UPDATE_EXTN_DATA);
}

DEM_INLINE void Dem_DistMemRequestUpdateEvtExtData (uint8 DistMemIndex)
{
   DEM_DIST_MEM_SETBIT (&Dem_DistMemLocationsStatus[DistMemIndex], DEM_DIST_MEM_BP_UPDATE_EXTN_DATA);
}

DEM_INLINE void Dem_DistMemClearUpdateEvtExtData (uint8 DistMemIndex)
{
   DEM_DIST_MEM_CLEARBIT (&Dem_DistMemLocationsStatus[DistMemIndex], DEM_DIST_MEM_BP_UPDATE_EXTN_DATA);
}

DEM_INLINE void Dem_DistMemSetStatusByte (uint8 DistMemIndex , uint8 newStatus)
{
   Dem_DistMemLocationsStatus[DistMemIndex] = newStatus;
}

#if(DEM_CFG_DIST_MEM_EXTENDED_DATA_USED == STD_ON)
DEM_INLINE void Dem_DistMemGetEnvData (uint8 DistMemIndex ,uint8* dest, uint8 size)
{
   DEM_MEMCPY(dest, Dem_DistMemLocations[DistMemIndex].extData , size );
}
#endif

DEM_INLINE Dem_boolean_least Dem_DistMemIsFull (void){
   return (Dem_DistMemNextEmptyIndex == 0);
}

DEM_INLINE Dem_boolean_least Dem_DistMemIsReportFailedNecessary (Dem_EventIdType eventId, Dem_EventStatusType eventStatus)
{
   return (   ((eventStatus==DEM_EVENT_STATUS_FAILED) || (eventStatus==DEM_EVENT_STATUS_PREFAILED))
   	   && (Dem_EvtIsEventStoredInDistMem(eventId) || !Dem_DistMemIsFull()));
}

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

void Dem_DistMemReportFailed(Dem_EventIdType EventId
   						 DEM_DEBUGDATA_PARAM(Dem_DebugDataType debug0, Dem_DebugDataType debug1));
void Dem_DistMemReportPassed(Dem_EventIdType EventId);

void Dem_DistMemInitCheckNvM(void);
void Dem_DistMemInit(void);
void Dem_DistMemMainFunction(void);

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#endif

#endif
