#include "Std_Types.hpp"

#include "Dem.hpp"
#include "Rte_Dem.hpp"
#include "Dem_EnvDataElement.hpp"
#include "Dem_Events.hpp"
#include "Dem_EventStatus.hpp"
#include "Dem_EvMem.hpp"
#include "Dem_EvMemGen.hpp"
#include "DemAppInterfaceX.hpp"
#include "Rte_Dem.hpp"
#include "FiM.hpp"
#include "Dem_Cfg_Events_DataStructures.hpp"

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
const Dem_EnvDataElement Dem_Cfg_EnvDataElement[DEM_CFG_ENV_DATAELEMENTS_ARRAYLENGTH] = DEM_CFG_ENV_DATAELEMENTS;
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
#if(DEM_CFG_DEBUGDATA != DEM_CFG_DEBUGDATA_OFF)
#if(DEM_CFG_READDEM_DEBUG0_SUPPORTED)
Std_ReturnType Dem_ReadDebug0(uint8* Buffer, const Dem_InternalEnvData* internalData)
{
    Dem_BigEndian_WriteValue2Buffer(Buffer, internalData->debug0, DEM_SIZEOF_TYPE(Dem_DebugDataType));
   return E_OK;
}
#endif

#if(DEM_CFG_READDEM_DEBUG1_SUPPORTED)
Std_ReturnType Dem_ReadDebug1(uint8* Buffer, const Dem_InternalEnvData* internalData)
{
    Dem_BigEndian_WriteValue2Buffer(Buffer, internalData->debug1, DEM_SIZEOF_TYPE(Dem_DebugDataType));
   return E_OK;
}
#endif
#endif

Std_ReturnType Dem_ReadEventStatusByte( uint8* buffer, const Dem_InternalEnvData* internalData ){
   if(Dem_isEventIdValid(internalData->eventId)){
        *buffer = (uint8)Dem_EvtGetIsoByte( internalData->eventId);
        return E_OK;
   }
   else{
        return E_NOT_OK;
   }
}

#if(DEM_CFG_READDEM_AGINGCTR_UPCNT_SUPPORTED)
Std_ReturnType Dem_ReadAgingCtrUpCnt(uint8* Buffer, const Dem_InternalEnvData* internalData){
   if(internalData->evMemLocation != NULL_PTR){
        *Buffer = (uint8) Dem_EvMemGetEventMemAgingCounterScaled(internalData->evMemLocation);
   }
   else{
        *Buffer = 0;
   }
    return E_OK;
}
#endif

#if(DEM_CFG_READDEM_AGINGCTR_DOWNCNT_SUPPORTED)
Std_ReturnType Dem_ReadAgingCtrDownCnt(uint8* Buffer, const Dem_InternalEnvData* internalData){
   if(internalData->evMemLocation != NULL_PTR){
    	*Buffer = (uint8)(Dem_EvtParam_GetAgingThreshold(internalData->eventId) - Dem_EvMemGetEventMemAgingCounterScaled (internalData->evMemLocation));
   }
   else{
        *Buffer = 0;
   }
    return E_OK;
}
#endif

#if(DEM_CFG_READDEM_OCCCTR_SUPPORTED)
Std_ReturnType Dem_ReadOccCtr(uint8* Buffer, const Dem_InternalEnvData* internalData){
   if(internalData->evMemLocation != NULL_PTR){
   	*Buffer = (uint8)Dem_EvMemGetEventMemOccurrenceCounterByPtr(internalData->evMemLocation);
   }
   else{
   	*Buffer = 0;
   }
   return E_OK;
}
#endif

#if(DEM_CFG_READDEM_OVFLIND_SUPPORTED)
Std_ReturnType Dem_ReadOvflInd(uint8* Buffer, const Dem_InternalEnvData* internalData){
   DEM_UNUSED_PARAM(internalData);
   *Buffer = DEM_BOOL2BIT( Dem_EvMemGenIsOverflow(DEM_DTC_ORIGIN_PRIMARY_MEMORY) );
   return E_OK;
}
#endif

#if(DEM_CFG_READDEM_SIGNIFICANCE_SUPPORTED)
Std_ReturnType Dem_ReadSignificance(uint8* Buffer, const Dem_InternalEnvData* internalData){
   *Buffer = Dem_EvtParam_GetSignificance(internalData->eventId);
   return E_OK;
}
#endif

#if(DEM_CFG_READDEM_CURRENT_FDC_SUPPORTED)
Std_ReturnType Dem_ReadCurrentFDC(uint8* Buffer, const Dem_InternalEnvData* internalData){
    *Buffer = (uint8)Dem_DtcFaultDetectionRetrieve(Dem_DtcIdFromEventId(internalData->eventId));
   return E_OK;
}
#endif

#if(DEM_CFG_READDEM_MAX_FDC_DURING_CURRENT_CYCLE_SUPPORTED)
Std_ReturnType Dem_ReadMaxFdcDuringCurrentCycle(uint8* Buffer, const Dem_InternalEnvData* internalData){
   if(internalData->evMemLocation != NULL_PTR){
   	*Buffer = (uint8)Dem_EvMemGetMaxFdcDuringCurrentCycleByPtr(internalData->evMemLocation);
   }
   else{
   	*Buffer = 0;
   }
   return E_OK;
}
#endif

#if(DEM_CFG_READDEM_MAX_FDC_SINCE_LAST_CLEAR_SUPPORTED)
Std_ReturnType Dem_ReadMaxFdcSinceLastClear(uint8* Buffer, const Dem_InternalEnvData* internalData){
   if(internalData->evMemLocation != NULL_PTR){
   	*Buffer = (uint8)Dem_EvMemGetMaxFdcSinceLastClearByPtr(internalData->evMemLocation);
   }
   else{
   	*Buffer = 0;
   }
   return E_OK;
}
#endif

#if(DEM_CFG_READDEM_CYCLES_SINCE_FIRST_FAILED_SUPPORTED)
Std_ReturnType Dem_ReadCyclesSinceFirstFailed(uint8* Buffer, const Dem_InternalEnvData* internalData){
   if(internalData->evMemLocation != NULL_PTR){
   	*Buffer = Dem_EvMemGetCyclesSinceFirstFailedByPtr(internalData->evMemLocation);
   }
   else{
   	*Buffer = 0;
   }
   return E_OK;
}
#endif

#if(DEM_CFG_READDEM_CYCLES_SINCE_LAST_FAILED_SUPPORTED)
Std_ReturnType Dem_ReadCyclesSinceLastFailed(uint8* Buffer, const Dem_InternalEnvData* internalData){
   if(internalData->evMemLocation != NULL_PTR){
   	*Buffer = Dem_EvMemGetCyclesSinceLastFailedByPtr(internalData->evMemLocation);
   }
   else{
   	*Buffer = 0;
   }
   return E_OK;
}
#endif

#if(DEM_CFG_READDEM_CYCLES_SINCE_LAST_FAILED_EXCLUDING_TNC_SUPPORTED)
Std_ReturnType Dem_ReadCyclesSinceLastFailedExcludingTNC(uint8* Buffer, const Dem_InternalEnvData* internalData){
   if(internalData->evMemLocation != NULL_PTR){
   	*Buffer = Dem_EvMemGetCyclesSinceLastFailedExcludingTNCByPtr(internalData->evMemLocation);
   }
   else{
   	*Buffer = 0;
   }
   return E_OK;
}
#endif

#if(DEM_CFG_READDEM_FAILED_CYCLES_SUPPORTED)
Std_ReturnType Dem_ReadFailedCycles(uint8* Buffer, const Dem_InternalEnvData* internalData){
   if(internalData->evMemLocation != NULL_PTR){
   	*Buffer = Dem_EvMemGetFailedCyclesByPtr(internalData->evMemLocation);
   }
   else{
   	*Buffer = 0;
   }
   return E_OK;
}
#endif

#if(DEM_CFG_READDEM_EVENT_ID_SUPPORTED)
Std_ReturnType Dem_ReadEventId(uint8* Buffer, const Dem_InternalEnvData* internalData){
    Dem_BigEndian_WriteValue2Buffer(Buffer, internalData->eventId, DEM_SIZEOF_TYPE( Dem_EventIdType ));
    return E_OK;
}
#endif

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
