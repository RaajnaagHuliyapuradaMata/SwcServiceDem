
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
#warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef DEM_PRJSPECIFICFAILUREMEMORYTYPE_H
#define DEM_PRJSPECIFICFAILUREMEMORYTYPE_H

#include "Dem_Cfg_EvBuff.hpp"
#include "Dem_Types.hpp"

#if(DEM_CFG_SUPPORT_PROJECTSPECIFIC_FAILUREMEMORY == TRUE)

typedef struct{
   uint8 SampleData;
}DemRbProjectSpecificFailureMemoryType;

#endif

#endif
