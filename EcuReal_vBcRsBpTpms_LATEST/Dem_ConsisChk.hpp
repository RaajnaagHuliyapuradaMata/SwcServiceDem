
#ifndef DEM_CONSISCHK_H
#define DEM_CONSISCHK_H

#include "Dem_EvMemGen.hpp"
#include "Dem_EventStatus.hpp"
#include "Dem_IndicatorAttributes.hpp"

DEM_INLINE void Dem_StatusByteConsistencyCheck(uint16_least LocId, uint16_least Status)
{

   if(Dem_EvMemIsOriginPrimary(LocId) || Dem_EvMemIsOriginSecondary(LocId))
   {
        Dem_EventIdType EventId;
        EventId = Dem_EvMemGetEventMemEventId(LocId);

        if(Dem_LibGetParamBool(DEM_CFG_EVMEM_STATUS_BYTE_CONSISTENCY_PREFERENCE ==
                                DEM_CFG_EVMEM_STATUS_BYTE_CONSISTENCY_PREFERENCE_EVENT_MEMORY))
        {

            Dem_EvtSt_SetTestFailed(EventId, (Status & DEM_EVMEM_STSMASK_TESTFAILED) != 0u);
        }

   	if((Status & (DEM_EVMEM_STSMASK_PENDING | DEM_EVMEM_STSMASK_CONFIRMED
#if(DEM_CFG_TFSLC_RESET_AFTER_AGING_AND_DISPLACEMENT)
   	        | DEM_EVMEM_STSMASK_TESTFAILED_SLC
#endif
   	)) != 0u)
   	{
   		Dem_EvtSt_SetTestFailedSLC(EventId,TRUE);
   		Dem_EvtSt_SetTestCompleteSLC(EventId,TRUE);
            if((Status & (DEM_EVMEM_STSMASK_CONFIRMED)) != 0u)
            {
                Dem_EvtSt_SetConfirmedDTC(EventId,TRUE);
            }
            if((Status & (DEM_EVMEM_STSMASK_PENDING)) != 0u)
            {
               Dem_EvtSt_SetPendingDTC(EventId,TRUE);
            }

            Dem_IndicatorAttribute_ConsistencyCheck(EventId, Status);

   	}
   }
}

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

void Dem_ConsistencyCheckForDTC(void);

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#endif
