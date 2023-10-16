#include "Std_Types.hpp"

#include "Dem_IndicatorAttributes.hpp"
#include "Dem_EventStatus.hpp"
#include "Dem_Nvm.hpp"

#if(DEM_CFG_EVT_INDICATOR == DEM_CFG_EVT_INDICATOR_ON)
#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
DEM_ARRAY_DEFINE_CONST(Dem_EvtIndicatorAttributeParam, Dem_AllEventsIndicatorParam, DEM_INDICATOR_ATTRIBUTE_ARRAYLENGTH, DEM_CFG_EVENT_INDICATOR_ATTRIBUTE_PARAMS);
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.hpp"
DEM_ARRAY_DEFINE(Dem_EvtIndicatorAttributeState, Dem_AllEventsIndicatorState, DEM_INDICATOR_ATTRIBUTE_ARRAYLENGTH);
#define DEM_STOP_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

void Dem_IndicatorAttributeInitCheckNvM(void){
    Dem_NvmResultType NvmResult;

   if(Dem_NvMIsInvalidateAllNVMBlocksRequested())
   {

        DEM_MEMSET( &Dem_AllEventsIndicatorState, 0x00, DEM_SIZEOF_VAR(Dem_AllEventsIndicatorState));
        Dem_NvMClearBlockByInvalidate(DEM_NVM_ID_INDICATOR_ATTRIBUTES);
   }
   else{

        NvmResult = Dem_NvmGetStatus (DEM_NVM_ID_INDICATOR_ATTRIBUTES);

        if(NvmResult != DEM_NVM_SUCCESS)
        {

            DEM_MEMSET( &Dem_AllEventsIndicatorState, 0x00, DEM_SIZEOF_VAR(Dem_AllEventsIndicatorState));
            Dem_NvMWriteBlockOnShutdown(DEM_NVM_ID_INDICATOR_ATTRIBUTES);
        }
   }
}

void Dem_IndicatorAttributeInit(void){
   uint32 i;

   for(i = 0u; DEM_INDICATOR_ATTRIBUTE_COUNT > i; i++)
   {
        if(Dem_IsIndicatorAttributeValid(i))
        {
            if(Dem_IndicatorAttribGetFailureCycCtr(i) == 0xFF)
            {
                Dem_IndicatorIncrementBehaviourCounter(Dem_IndicatorAttrib_GetIndicatorId(i), Dem_IndicatorAttrib_GetBehaviour(i));
            }
        }
   }
}

void Dem_SetIndicatorDeActivation(Dem_EventIdType EventId, Dem_UdsStatusByteType isoByteOld, Dem_UdsStatusByteType isoByteNew)
{

   uint8 healingCycCtr;
   uint8 healingCycCtrThreshold;
   uint8 indicatorBehaviour;

   uint16_least currentIndicAttrib = 0;
    Dem_EventIndicatorAttributeIterator it;

   uint8 indicatorId;

   for(Dem_EventIndicatorAttributeIteratorNew(EventId, &it); Dem_EventIndicatorAttributeIsValid(EventId, &it);
            Dem_EventIndicatorAttributeNext(&it))
   {
        currentIndicAttrib = Dem_EventIndicatorAttributeCurrent(&it);

        if((Dem_IsIndicatorAttributeValid(currentIndicAttrib)) && (Dem_IndicatorAttrib_IsApiControl(currentIndicAttrib) == FALSE))
        {

            healingCycCtr = Dem_IndicatorAttribGetHealingCycCtr(currentIndicAttrib);

            indicatorBehaviour = Dem_IndicatorAttrib_GetBehaviour(currentIndicAttrib);
            indicatorId = Dem_IndicatorAttrib_GetIndicatorId(currentIndicAttrib);
            healingCycCtrThreshold = Dem_IndicatorAttrib_GetHealingCycleThreshold(currentIndicAttrib);

            if(Dem_IndicatorAttribGetFailureCycCtr(currentIndicAttrib) == 0xFF)
            {

#if(DEM_CFG_EVTINDICATOR_HEALINGTHRESHOLD == DEM_CFG_EVTINDICATOR_HEALINGTHRESHOLD_ON)
                if((healingCycCtr < healingCycCtrThreshold) && (!Dem_ISO14229ByteIsTestFailedTOC(isoByteOld)) && (!Dem_ISO14229ByteIsTestCompleteTOC(isoByteOld)))
                {
                    healingCycCtr++;
                    Dem_IndicatorAttribSetHealingCycCtr(currentIndicAttrib, healingCycCtr);
                }
#else
                DEM_UNUSED_PARAM(isoByteOld);
#endif

                if(healingCycCtr >= healingCycCtrThreshold)
                {

                    Dem_IndicatorDecrementBehaviourCounter(indicatorId, indicatorBehaviour);

                    Dem_IndicatorAttribSetHealingCycCtr(currentIndicAttrib, 0);

                    Dem_IndicatorAttribSetFailureCycCtr(currentIndicAttrib, 0);
                }

            }
        }
   }
    Dem_UpdateISO14229WIRStatus(EventId);
    DEM_UNUSED_PARAM(isoByteNew);
}

void Dem_SetIndicatorActivation(Dem_EventIdType EventId, Dem_UdsStatusByteType isoByteOld, Dem_UdsStatusByteType isoByteNew)
{

   uint8 failureCycCtr;
   uint8 failureCycCtrThreshold;
   uint8 indicatorBehaviour;

   uint8 indicatorId;
   Dem_boolean_least anyIndicatorOn = FALSE;

   uint16_least currentIndicAttrib = 0;
   Dem_EventIndicatorAttributeIterator it;

   for(Dem_EventIndicatorAttributeIteratorNew(EventId, &it); Dem_EventIndicatorAttributeIsValid(EventId, &it);
   		Dem_EventIndicatorAttributeNext(&it))
   {
   	currentIndicAttrib = Dem_EventIndicatorAttributeCurrent(&it);

   	if((Dem_IsIndicatorAttributeValid(currentIndicAttrib)) && (Dem_IndicatorAttrib_IsApiControl(currentIndicAttrib) == FALSE))
   	{

   		failureCycCtr = Dem_IndicatorAttribGetFailureCycCtr(currentIndicAttrib);

   		if(failureCycCtr < 0xFF)
   		{

   			failureCycCtrThreshold = Dem_IndicatorAttrib_GetFailureCycleThreshold(currentIndicAttrib);
   			indicatorId = Dem_IndicatorAttrib_GetIndicatorId(currentIndicAttrib);
   			indicatorBehaviour = Dem_IndicatorAttrib_GetBehaviour(currentIndicAttrib);

#if(DEM_CFG_EVTINDICATOR_FAILURETHRESHOLD == DEM_CFG_EVTINDICATOR_FAILURETHRESHOLD_ON)
   			if((failureCycCtr < failureCycCtrThreshold) && Dem_ISO14229ByteIsTestFailedTOC(isoByteNew) && (!Dem_ISO14229ByteIsTestFailedTOC(isoByteOld)))
   			{
   				failureCycCtr++;
   			}
#else
   			DEM_UNUSED_PARAM(isoByteOld);
   			DEM_UNUSED_PARAM(isoByteNew);
#endif

   			if(failureCycCtr >= failureCycCtrThreshold)
   			{

   				Dem_IndicatorIncrementBehaviourCounter(indicatorId, indicatorBehaviour);

   				failureCycCtr = 0xFF;
   				anyIndicatorOn = TRUE;
   			}

   			Dem_IndicatorAttribSetFailureCycCtr(currentIndicAttrib, failureCycCtr);
   		}
   		else
   		{
   			anyIndicatorOn = TRUE;
   		}

   		Dem_IndicatorAttribSetHealingCycCtr(currentIndicAttrib, 0);
   	}
   }

   if(anyIndicatorOn)
   {
        Dem_EvtSt_HandleIndicatorOn(EventId);
   }
}

Dem_boolean_least Dem_isAnyIndicatorAttribOn (Dem_EventIdType EventId)
{

   Dem_EventIndicatorAttributeIterator it;
   uint16_least currentIndicAttrib = 0;
   Dem_boolean_least retVal = FALSE;

   for( Dem_EventIndicatorAttributeIteratorNew(EventId, &it);
         Dem_EventIndicatorAttributeIsValid(EventId, &it);
         Dem_EventIndicatorAttributeNext(&it)
   )
   {
       currentIndicAttrib = Dem_EventIndicatorAttributeCurrent(&it);

       if(Dem_IsIndicatorAttributeValid(currentIndicAttrib))
       {
           if(Dem_IndicatorAttribGetFailureCycCtr(currentIndicAttrib) == 0xFF)
           {
               retVal = TRUE;
               break;
           }
       }
   }

   return retVal;
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
#endif

