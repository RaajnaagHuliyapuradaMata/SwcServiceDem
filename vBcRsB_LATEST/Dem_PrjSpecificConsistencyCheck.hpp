
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
#warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef DEM_PRJSPECIFICCONSISTENCYCHECK_H
#define DEM_PRJSPECIFICCONSISTENCYCHECK_H

#include "Dem_EvBuffEvent.hpp"

#error "The Dem_PrjSpecificConistencyCheck is a template file, to be used only when the DemRbSupportProjectSpecificConsistencyCheck is enabled in the project,  \
        This template shall be modified to user's need and this error message can be removed.                                   \
        \
        If the  parameter is not enabled, Kindly remove this file from project"

#if(DEM_CFG_SUPPORT_PROJECTSPECIFIC_CONSISTENCYCHECK == DEM_CFG_CONSISTENCY_CHECK_ON)

void Dem_ProjectSpecificConsistencyCheck();

#endif

#endif
