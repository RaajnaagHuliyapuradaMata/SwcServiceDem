
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef DEM_PRJEVMEMPROJECTEXTENSION_H
#define DEM_PRJEVMEMPROJECTEXTENSION_H

#include "Rte_Dem_Type.hpp"

typedef struct{
   uint8 mycounter;
}Dem_EvMemProjectExtensionType;

void Dem_EvMemProjectExtensionInit(void);

void Dem_EvMemProjectExtensionMain(void);

void Dem_EvMemProjectExtensionUnRobust(Dem_EventIdType EventId, uint16_least LocId, uint16_least *writeSts);

void Dem_EvMemProjectExtensionFailed(Dem_EventIdType EventId, uint16_least LocId, uint16_least *writeSts);

void Dem_EvMemProjectExtensionStartOpCycle(uint16_least LocId, uint16_least *writeSts);

#endif
