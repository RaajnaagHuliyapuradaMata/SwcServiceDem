

#ifndef DEM_H
#define DEM_H

#include "Std_Types.hpp"

#define DEM_EVENT_STATUS_FAILED                1
#define DEM_EVENT_STATUS_PASSED                2
#define DEM_EVENT_STATUS_PREPASSED             3
#define DEM_EVENT_STATUS_PREFAILED             4

#define Dem_FR_E_ACCESS                        5
#define Dem_FRIF_E_JLE_SYNC                    6
#define Dem_FRSM_E_CLUSTER_STARTUP             7

#define DemConf_DemEventParameter_DemEventParameter 1u

typedef uint16 Dem_EventIdType;
typedef uint8  Dem_EventStatusType;

extern void Dem_ReportErrorStatus( Dem_EventIdType EventId, Dem_EventStatusType EventStatus);

#endif

