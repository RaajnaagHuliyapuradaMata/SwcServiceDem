

#ifndef DEM_EVBUFFEVENT_H
#define DEM_EVBUFFEVENT_H

#include "Dem_Types.hpp"
#include "Dem_Cfg_EnvMain.hpp"
#include "Dem_Cfg_EvBuff.hpp"
#include "Dem_Cfg_Nodes.hpp"
#include "Dem_Mapping.hpp"

#if(DEM_CFG_SUPPORT_PROJECTSPECIFIC_FAILUREMEMORY == TRUE)
#include "Dem_PrjSpecificFailureMemoryType.hpp"
#endif
#define Dem_EvBuffEventType uint8
#define C_EVENTTYPE_NOEVENT                        0u
#define C_EVENTTYPE_SET                            1u
#define C_EVENTTYPE_SET_RESET                      2u
#define C_EVENTTYPE_RESET                          3u
#define C_EVENTTYPE_SET_RECONFIRMED                4u
#define C_EVENTTYPE_SET_WAITINGFORMONITORING       5u
#define C_EVENTTYPE_PRESTORE                       6u
#define C_EVENTTYPE_UNROBUST                       7u

#define DEM_CFG_EVBUFF_STORES_ENVDATA_ON		STD_ON
#define DEM_CFG_EVBUFF_STORES_ENVDATA_OFF		STD_OFF
#if((DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON) || (DEM_CFG_FFPRESTORAGESUPPORT == DEM_CFG_FFPRESTORAGESUPPORT_ON))
#define DEM_CFG_EVBUFF_STORES_ENVDATA		DEM_CFG_EVBUFF_STORES_ENVDATA_ON
#else
#define DEM_CFG_EVBUFF_STORES_ENVDATA		DEM_CFG_EVBUFF_STORES_ENVDATA_OFF
#endif

typedef union
{
#if(DEM_CFG_ENVMINSIZE_OF_RAWENVDATA >= 4)

   uint32 EnforceAlignment;
#endif
   uint8  Buffer[DEM_CFG_ENVMINSIZE_OF_RAWENVDATA];
}Dem_EvBuffEnvDataAlignedType;

typedef struct{
#if(DEM_CFG_EVBUFF_STORES_ENVDATA == DEM_CFG_EVBUFF_STORES_ENVDATA_ON)

    Dem_EvBuffEnvDataAlignedType envData;
#endif
    Dem_EvBuffEventType eventType;

#if(DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
   uint8 counter;
#endif

    Dem_EventIdType eventId;

#if(DEM_CFG_DEBUGDATA != DEM_CFG_DEBUGDATA_OFF)
    Dem_DebugDataType debug0;
    Dem_DebugDataType debug1;
#endif

#if(DEM_CFG_SUPPORT_PROJECTSPECIFIC_FAILUREMEMORY == TRUE)
    DemRbProjectSpecificFailureMemoryType  DemRbProjectSpecificFailureMemoryData;
#endif

#if( DEM_BFM_ENABLED == DEM_BFM_ON )
    rba_DemBfm_EnvironmentalData DemRbBfmFailureMemoryData;
#endif
}Dem_EvBuffEvent;

#if(DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
DEM_INLINE Dem_ComponentIdType Dem_FailureEvent__getNodeId (const Dem_EvBuffEvent *fe)
{
    return Dem_NodeIdFromEventId(fe->eventId);
}
#endif

DEM_INLINE void Dem_EvBuffSetCounter (Dem_EvBuffEvent *evBuff, uint8 value)
{
#if(DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
    evBuff->counter = value;
#else
    DEM_UNUSED_PARAM(evBuff);
    DEM_UNUSED_PARAM(value);
#endif
}

DEM_INLINE uint8 Dem_EvBuffGetCounter (const Dem_EvBuffEvent *evBuff)
{
#if(DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
    return evBuff->counter;
#else
    DEM_UNUSED_PARAM(evBuff);
    return 0;
#endif
}

#endif
