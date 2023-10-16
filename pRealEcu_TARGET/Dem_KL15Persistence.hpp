
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef DEM_KL15PERSISTENCE_H
#define DEM_KL15PERSISTENCE_H

#include "Dem_Types.hpp"

void Dem_KL15PersistenceMain(void);

void Dem_KL15PersistenceScheduleStorage(void);

Std_ReturnType Dem_KL15PersistenceImmediateStorage(void);

DEM_INLINE void Dem_KL15PersistenceCheckEventStatus(Dem_EventIdType EventId
   ,     Dem_EventStatusType EventStatusOld, Dem_EventStatusType EventStatusNew)
{
    DEM_UNUSED_PARAM(EventId);

   if(((EventStatusOld ^ EventStatusNew) & DEM_UDS_STATUS_PDTC) != 0)
   {
        Dem_KL15PersistenceScheduleStorage();
   }
}

#endif
