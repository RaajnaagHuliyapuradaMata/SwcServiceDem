
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
#warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef DEM_PRJSPECIFICFAILUREMEMORY_H
#define DEM_PRJSPECIFICFAILUREMEMORY_H

#error "The Dem_PrjSpecificFailureMemory is a template file, to be used only when the DemRbSupportProjectSpecificFailureMemory is enabled in the project,  \
        This template shall be modified to user's need and this error message can be removed.                                   \
        \
        If the DemRbSupportProjectSpecificFailureMemory parameter is not enabled, Kindly remove this file from project"

#include "Dem_EvBuffEvent.hpp"

#if(DEM_CFG_SUPPORT_PROJECTSPECIFIC_FAILUREMEMORY == TRUE)

void Dem_ProjectSpecificFailureMemoryCapture(Dem_EventIdType EventId,Dem_EvBuffEventType eventType,DemRbProjectSpecificFailureMemoryType  *PrjFailureMemory);

void Dem_ProjectSpecificFailureMemoryReport(const Dem_EvBuffEvent *evBuff);

#endif

#endif
