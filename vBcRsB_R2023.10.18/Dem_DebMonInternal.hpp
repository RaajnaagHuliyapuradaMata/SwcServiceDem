

#ifndef DEM_DEBMONINTERNAL_H
#define DEM_DEBMONINTERNAL_H

#include "Dem_Types.hpp"

typedef Std_ReturnType(*Dem_GetFaultDetectionCounterOfIntDebMonitors)(sint8 * faultDetCtr);

typedef struct{

    Dem_GetFaultDetectionCounterOfIntDebMonitors funcPointer_GetFDC;
}Dem_DebounceMonitorInternal;

#endif

