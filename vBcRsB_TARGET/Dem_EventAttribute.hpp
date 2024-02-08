
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef DEM_EVENTATTRIBUTE_H
#define DEM_EVENTATTRIBUTE_H

#include "Dem_Events.hpp"

#if(DEM_CFG_EVT_ATTRIBUTE == DEM_CFG_EVT_ATTRIBUTE_ON)

typedef struct{
   boolean defect;
   uint8 value;
}Dem_EventAttributeType;

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
extern const Dem_EventAttributeType* Dem_getEventUserAttributes(Dem_EventIdType EventId);
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#define DEM_EVTS_USERATTRIBUTES_INIT(DEFECT, VALUE)   \
{                                                 \
   (DEFECT),									  \
   (VALUE)                                     	  \
}

DEM_INLINE boolean Dem_GetEventAttribute_defect(Dem_EventIdType EventId)
{
   return (Dem_getEventUserAttributes(EventId)->defect);
}

DEM_INLINE uint8 Dem_GetEventAttribute_value(Dem_EventIdType EventId)
{
   return (Dem_getEventUserAttributes(EventId)->value);
}

#endif
#endif

