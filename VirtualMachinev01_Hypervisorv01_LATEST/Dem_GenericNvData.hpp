

#ifndef DEM_GENERICNVDATA_H
#define DEM_GENERICNVDATA_H

#include "Dem_OperationCycle.hpp"
#include "Dem_EvMemGenTypes.hpp"

typedef struct{
#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
    rba_DemObdBasic_PidDataType pidData;
#endif

   Dem_OperationCycleList OperationCycleStates;
   Dem_OperationCycleList OperationCycleQualified;

#if DEM_CFG_EVMEMGENERIC_SUPPORTED

   boolean           Overflow[DEM_EVMEMGEN_OVERFLOW_ARRAYSIZE];

   Dem_DtcIdType     DtcIdsByOccurrenceTime[DEM_EVMEMGEN_DTCIDS_BY_OCCURRENCE_TIME_ARRAYSIZE];
#endif
}Dem_GenericNvDataType;

#define DEM_START_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.hpp"
extern Dem_GenericNvDataType Dem_GenericNvData;
#define DEM_STOP_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.hpp"

#endif

