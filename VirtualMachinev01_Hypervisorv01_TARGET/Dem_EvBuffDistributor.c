#include "Std_Types.hpp"

#include "Dem_EvBuff.hpp"
#include "Dem_EvBuffDistributor.hpp"
#include "Dem_Cfg.hpp"
#include "Dem_EvMem.hpp"
#include "Dem_EnvMain.hpp"
#include "Dem_Clear.hpp"

#if(DEM_CFG_SUPPORT_PROJECTSPECIFIC_FAILUREMEMORY == TRUE)
#include "Dem_PrjSpecificFailureMemory.hpp"
#endif

#define DEM_START_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.hpp"
static boolean Dem_isDistributionRunning = FALSE;
#define DEM_STOP_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.hpp"

DEM_INLINE void Dem_EvBuffDistributorCallReceivers (const Dem_EvBuffEvent* fe)
{

#if(DEM_CFG_EVBUFF_STORES_ENVDATA == DEM_CFG_EVBUFF_STORES_ENVDATA_OFF)
   uint8 envData[DEM_CFG_ENVMINSIZE_OF_RAWENVDATA];
#else
   const uint8 *envData;
    envData = (fe->envData.Buffer);
#endif

   if(   (fe->eventType == C_EVENTTYPE_SET)
            || (fe->eventType == C_EVENTTYPE_SET_RESET)
#if(DEM_CFG_STOREWAITINGFORMONITORINGEVENT == TRUE)
            || (fe->eventType == C_EVENTTYPE_SET_WAITINGFORMONITORING)
#endif
    )
   {

#if(DEM_CFG_EVBUFF_STORES_ENVDATA == DEM_CFG_EVBUFF_STORES_ENVDATA_OFF)
        Dem_EvBuffEnvCaptureData(fe->eventId, envData  DEM_DEBUGDATA_PARAM(fe->debug0, fe->debug1));
#endif
        Dem_EvMemSetEventFailedAllMem(fe->eventId, envData);
   }

   if(   (fe->eventType == C_EVENTTYPE_RESET)
            || (fe->eventType == C_EVENTTYPE_SET_RESET)
    )
   {

#if(DEM_CFG_EVBUFF_STORES_ENVDATA == DEM_CFG_EVBUFF_STORES_ENVDATA_OFF) && (DEM_CFG_EVMEM_EXTENDED_DATA_ON_PASSED_SUPPORTED)
        if(fe->eventType != C_EVENTTYPE_SET_RESET)
        {
            Dem_EnvCaptureED(fe->eventId, envData, DEM_CFG_ENVMINSIZE_OF_RAWENVDATA DEM_DEBUGDATA_PARAM(fe->debug0,fe->debug1));
        }
#endif
        Dem_EvMemSetEventPassedAllMem(fe->eventId, envData);
   }

   if(fe->eventType == C_EVENTTYPE_UNROBUST)
   {
#if(DEM_CFG_EVBUFF_STORES_ENVDATA == DEM_CFG_EVBUFF_STORES_ENVDATA_OFF)
        Dem_EvBuffEnvCaptureData(fe->eventId, envData  DEM_DEBUGDATA_PARAM(fe->debug0, fe->debug1));
#endif
        Dem_EvMemSetEventUnRobustAllMem(fe->eventId, envData);
   }

#if( DEM_BFM_ENABLED == DEM_BFM_ON )
    rba_DemBfm_EnvReport(fe);
#endif

#if(DEM_CFG_SUPPORT_PROJECTSPECIFIC_FAILUREMEMORY == TRUE)
    Dem_ProjectSpecificFailureMemoryReport(fe);
#endif
}

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"
static Dem_EvBuffEvent tmpEvBuffLocation;
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

void Dem_EvBuffDistributorMainFunction(void){
   Dem_boolean_least performDistribution = FALSE;
   uint32 idx;
   const Dem_EvBuffEvent* fEvent;

   #if( DEM_BFM_ENABLED == DEM_BFM_ON )
   if( rba_DemBfm_DeleteAllIsInProgress() )
   {
   	return;
   }
   #endif

   DEM_ENTERLOCK_MON();
   if(!Dem_isDistributionRunning)
   {
   	performDistribution = TRUE;
   	Dem_isDistributionRunning = TRUE;
   }
   DEM_EXITLOCK_MON();

   while(performDistribution)
   {
   	DEM_ENTERLOCK_MON();

   	fEvent = Dem_EvBuffGetEvent(&idx);

   	if(fEvent == NULL_PTR)
   	{
   		performDistribution = FALSE;
   		Dem_isDistributionRunning = FALSE;
   	}
   	else
   	{
   		DEM_MEMCPY(&tmpEvBuffLocation, fEvent, DEM_SIZEOF_VAR(tmpEvBuffLocation));

            Dem_EvtSetNextReportRelevantForMemories(fEvent->eventId, FALSE);

   		Dem_EvBuffRemoveEvent(idx);
   	}
   	DEM_EXITLOCK_MON();

   	if(performDistribution)
   	{
   		Dem_EvBuffDistributorCallReceivers(&tmpEvBuffLocation);
   	}
   }
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
