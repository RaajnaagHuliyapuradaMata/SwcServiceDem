

#ifndef DEM_EVMEMAGING_H
#define DEM_EVMEMAGING_H

#if(DEM_CFG_EVMEM_AGING_METHOD != DEM_CFG_EVMEM_AGING_METHOD_USER)

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
uint16_least      Dem_EvMemGetCurrentAgingCycleCounter(Dem_EventIdType EventId);
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
#include "Dem_Cfg_Events_DataStructures.hpp"

DEM_INLINE uint16_least Dem_EvMemGetCurrentAgingCycleCounterInt(Dem_EventIdType EventId){

#if(DEM_CFG_EVMEM_AGING_METHOD == DEM_CFG_EVMEM_AGING_METHOD_AGINGCYC_DIFF_UP)   || \
    (DEM_CFG_EVMEM_AGING_METHOD == DEM_CFG_EVMEM_AGING_METHOD_AGINGCYC_DIFF_DOWN) || \
    (DEM_CFG_EVMEM_AGING_METHOD == DEM_CFG_EVMEM_AGING_METHOD_AGINGCYC_STORE)
    return Dem_EvMemGetCurrentAgingCycleCounter(EventId);
#else
    DEM_EVMEM_USEVAR(EventId);
    return 0;
#endif
}

#define DEM_EVMEM_AGING_STATE                   ((DEM_EVMEM_STSMASK_TESTCOMPLETE_TAC * DEM_EVMEM_BOOL2DEC(Dem_LibGetParamBool(DEM_CFG_EVMEM_TESTCOMPLETE_TAC_SUPPORTED))) | \
                                                  DEM_EVMEM_STSMASK_CONFIRMED)

#define DEM_EVMEM_AGING_MASK                    ((DEM_EVMEM_STSMASK_TESTFAILED_TAC   * DEM_EVMEM_BOOL2DEC(Dem_LibGetParamBool(DEM_CFG_EVMEM_TESTFAILED_TAC_SUPPORTED)))   | \
                                                 (DEM_EVMEM_STSMASK_TESTCOMPLETE_TAC * DEM_EVMEM_BOOL2DEC(Dem_LibGetParamBool(DEM_CFG_EVMEM_TESTCOMPLETE_TAC_SUPPORTED))) | \
                                                  DEM_EVMEM_STSMASK_TESTFAILED| \
                                                  DEM_EVMEM_STSMASK_CONFIRMED)

#define DEM_EVMEM_TFSLC_AGING_STATE             ((DEM_EVMEM_STSMASK_TESTCOMPLETE_TAC * DEM_EVMEM_BOOL2DEC(Dem_LibGetParamBool(DEM_CFG_EVMEM_TESTCOMPLETE_TAC_SUPPORTED))) | \
                                                  DEM_EVMEM_STSMASK_TESTFAILED_SLC)

#define DEM_EVMEM_TFSLC_AGING_MASK              ((DEM_EVMEM_STSMASK_TESTFAILED_TAC   * DEM_EVMEM_BOOL2DEC(Dem_LibGetParamBool(DEM_CFG_EVMEM_TESTFAILED_TAC_SUPPORTED)))   | \
                                                 (DEM_EVMEM_STSMASK_TESTCOMPLETE_TAC * DEM_EVMEM_BOOL2DEC(Dem_LibGetParamBool(DEM_CFG_EVMEM_TESTCOMPLETE_TAC_SUPPORTED))) | \
                                                  DEM_EVMEM_STSMASK_TESTFAILED| \
                                                  DEM_EVMEM_STSMASK_TESTFAILED_SLC)

DEM_INLINE Dem_boolean_least Dem_EvMemIsAged(Dem_EventIdType EventId, uint16_least LocId, uint16_least StatusNew){
   DEM_EVMEM_USEVAR(LocId);
   DEM_EVMEM_USEVAR(EventId);

   return (Dem_boolean_least)((StatusNew & DEM_EVMEM_STSMASK_AGED) != 0u);
}

DEM_INLINE uint16_least Dem_EvMemGetEventMemAgingCounterScaled(const Dem_EvMemEventMemoryType *EventMemory){
   uint16_least AgingCounter;

   if(Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_COUNT_DOWN)){
      AgingCounter = Dem_EvtParam_GetAgingThreshold(Dem_EvMemGetEventMemEventIdByPtr(EventMemory)) - Dem_EvMemGetEventMemAgingCounterByPtr(EventMemory);
   }
   else if(Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_AGINGCYC_DIFF_UP)){
      if((Dem_EvMemGetEventMemStatusByPtr(EventMemory) & DEM_EVMEM_STSMASK_TESTFAILED) != 0u){
         AgingCounter = 0;
      }
      else if((Dem_EvMemGetEventMemStatusByPtr(EventMemory) & DEM_EVMEM_STSMASK_AGED) != 0u){
         AgingCounter = Dem_EvtParam_GetAgingThreshold(Dem_EvMemGetEventMemEventIdByPtr(EventMemory));
      }
      else{
         AgingCounter = (uint16_least)((Dem_EvMemAgingCounterType)(Dem_EvMemGetCurrentAgingCycleCounterInt(Dem_EvMemGetEventMemEventIdByPtr(EventMemory)) - Dem_EvMemGetEventMemAgingCounterByPtr(EventMemory)));
      }
   }
   else if(Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_AGINGCYC_DIFF_DOWN)){
      if((Dem_EvMemGetEventMemStatusByPtr(EventMemory) & DEM_EVMEM_STSMASK_TESTFAILED) != 0u){
         AgingCounter = Dem_EvtParam_GetAgingThreshold(Dem_EvMemGetEventMemEventIdByPtr(EventMemory));
      }
      else if((Dem_EvMemGetEventMemStatusByPtr(EventMemory) & DEM_EVMEM_STSMASK_AGED) != 0u){
         AgingCounter = 0;
      }
      else{
         AgingCounter = Dem_EvtParam_GetAgingThreshold(Dem_EvMemGetEventMemEventIdByPtr(EventMemory)) -
         ((uint16_least)((Dem_EvMemAgingCounterType)(Dem_EvMemGetCurrentAgingCycleCounterInt(Dem_EvMemGetEventMemEventIdByPtr(EventMemory)) - Dem_EvMemGetEventMemAgingCounterByPtr(EventMemory))));
      }
   }
   else if(Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_AGINGCYC_STORE)){
      if((Dem_EvMemGetEventMemStatusByPtr(EventMemory) & DEM_EVMEM_STSMASK_TESTFAILED) != 0u){
         AgingCounter = Dem_EvMemGetEventMemAgingCounterByPtr(EventMemory);
      }
      else{
         AgingCounter = (uint16_least)((Dem_EvMemAgingCounterType)(Dem_EvMemGetEventMemAgingCounterByPtr(EventMemory) + Dem_EvtParam_GetAgingThreshold(Dem_EvMemGetEventMemEventIdByPtr(EventMemory))));
      }
   }
   else{
      AgingCounter = Dem_EvMemGetEventMemAgingCounterByPtr(EventMemory);
   }

   return AgingCounter;
}

DEM_INLINE void Dem_EvMemSetAgingCounterOnAgingCycle(Dem_EventIdType EventId, uint16_least LocId, uint16_least* StatusNew, uint16_least* WriteSts){

   Dem_boolean_least IsAgingThresholdReached;

   if(!Dem_EvMemIsAged(EventId, LocId, *StatusNew)){
      if((Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_COUNT_UP)) ||
            (Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_COUNT_DOWN))){
         if(((*StatusNew & DEM_EVMEM_AGING_MASK) == DEM_EVMEM_AGING_STATE)
#if(DEM_CFG_TFSLC_RESET_AFTER_AGING_AND_DISPLACEMENT)
                 || ((*StatusNew & DEM_EVMEM_TFSLC_AGING_MASK) == DEM_EVMEM_TFSLC_AGING_STATE)
#endif
             )
         {
             if(Dem_EvMemGetEventMemAgingCounter(LocId) < Dem_EvtParam_GetAgingThreshold(EventId))
             {
                 Dem_EvMemSetEventMemAgingCounter(LocId, (uint16_least)(Dem_EvMemGetEventMemAgingCounter(LocId) + 1u));
             }

#if(DEM_CFG_TFSLC_RESET_AFTER_AGING_AND_DISPLACEMENT)

             if(Dem_EvMemGetEventMemAgingCounterForTFSLC(LocId) < Dem_EvtParam_GetAgingThresholdForTFSLC(EventId))
             {
                 Dem_EvMemSetEventMemAgingCounterForTFSLC(LocId, (uint16_least)(Dem_EvMemGetEventMemAgingCounterForTFSLC(LocId) + 1u));
             }
#endif
            *WriteSts = *WriteSts | DEM_EVMEM_WRITEMASK_DATA;
         }
         if((*StatusNew & (DEM_EVMEM_STSMASK_CONFIRMED
#if(DEM_CFG_TFSLC_RESET_AFTER_AGING_AND_DISPLACEMENT)
                      | DEM_EVMEM_STSMASK_TESTFAILED_SLC
#endif
         )) != 0u)
         {
            if(Dem_LibGetParamBool(DEM_CFG_EVMEM_TESTFAILED_TAC_SUPPORTED))
            {
               *StatusNew = *StatusNew & (uint16_least)(~(uint16_least)DEM_EVMEM_STSMASK_TESTFAILED_TAC);
            }
            if(Dem_LibGetParamBool(DEM_CFG_EVMEM_TESTCOMPLETE_TAC_SUPPORTED))
            {
               *StatusNew = *StatusNew & (uint16_least)(~(uint16_least)DEM_EVMEM_STSMASK_TESTCOMPLETE_TAC);
            }
         }
      }
   }

   IsAgingThresholdReached = FALSE;
   if((Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_COUNT_UP)) ||
         (Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_COUNT_DOWN))){
       IsAgingThresholdReached = (Dem_boolean_least)((Dem_EvMemGetEventMemAgingCounter(LocId) >= Dem_EvtParam_GetAgingThreshold(EventId)) && (Dem_EvtParam_GetAgingThreshold(EventId) != 0)
#if(DEM_CFG_TFSLC_RESET_AFTER_AGING_AND_DISPLACEMENT)
                                              && (Dem_EvMemGetEventMemAgingCounterForTFSLC(LocId) >= Dem_EvtParam_GetAgingThresholdForTFSLC(EventId))
#endif
                                            );
   }

   if((Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_AGINGCYC_STORE)) ||
         (Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_AGINGCYC_DIFF_UP)) ||
         (Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_AGINGCYC_DIFF_DOWN))){

      Dem_EvMemAgingCounterType AgingCounterDiff;
#if(DEM_CFG_TFSLC_RESET_AFTER_AGING_AND_DISPLACEMENT)
      Dem_EvMemAgingCounterType TFSLCAgingCounterDiff;
      TFSLCAgingCounterDiff = (Dem_EvMemAgingCounterType)(Dem_EvMemGetCurrentAgingCycleCounterInt(EventId) - Dem_EvMemGetEventMemAgingCounterForTFSLC(LocId));
#endif
      AgingCounterDiff = (Dem_EvMemAgingCounterType)(Dem_EvMemGetCurrentAgingCycleCounterInt(EventId) - Dem_EvMemGetEventMemAgingCounter(LocId));

      IsAgingThresholdReached = (Dem_boolean_least)(((uint16_least)AgingCounterDiff >= Dem_EvtParam_GetAgingThreshold(EventId))
#if(DEM_CFG_TFSLC_RESET_AFTER_AGING_AND_DISPLACEMENT)
                                      && ((uint16_least)TFSLCAgingCounterDiff >= Dem_EvtParam_GetAgingThresholdForTFSLC(EventId))
#endif
                          );

   }

   if(IsAgingThresholdReached){
      *StatusNew = *StatusNew | DEM_EVMEM_STSMASK_AGED;
   }
}

DEM_INLINE void Dem_EvMemSetAgingCounterOnEventFailed(Dem_EventIdType EventId, uint16_least LocId, uint16_least* StatusNew, uint16_least* WriteSts){
   if( ! Dem_LibGetParamBool(DEM_CFG_SUPPORT_AGINGCNTR_ONLY_WHEN_AGING_ALLOWED) || Dem_EvtParam_GetAgingAllowed(EventId) ){
        *StatusNew = *StatusNew & (uint16_least)(~((uint16_least)DEM_EVMEM_STSMASK_AGED));
        if((Dem_EvMemGetEventMemStatus(LocId) & DEM_EVMEM_STSMASK_TESTFAILED) == 0u)
        {
            if((Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_COUNT_UP)) ||
                    (Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_COUNT_DOWN)))
            {
                Dem_EvMemSetEventMemAgingCounter(LocId,0);
#if(DEM_CFG_TFSLC_RESET_AFTER_AGING_AND_DISPLACEMENT)
                Dem_EvMemSetEventMemAgingCounterForTFSLC(LocId, 0);
#endif
                *WriteSts = *WriteSts | DEM_EVMEM_WRITEMASK_DATA;
            }
            if((Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_AGINGCYC_STORE)) ||
                    (Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_AGINGCYC_DIFF_UP)) ||
                    (Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_AGINGCYC_DIFF_DOWN)))
            {
                Dem_EvMemSetEventMemAgingCounter(LocId,Dem_EvMemGetCurrentAgingCycleCounterInt(EventId));

#if(DEM_CFG_TFSLC_RESET_AFTER_AGING_AND_DISPLACEMENT)
                Dem_EvMemSetEventMemAgingCounterForTFSLC(LocId, (uint16_least)(Dem_EvMemGetCurrentAgingCycleCounterInt(EventId)));
#endif
                *WriteSts = *WriteSts | DEM_EVMEM_WRITEMASK_DATA;
            }
        }

        if((Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_COUNT_UP)) ||
                (Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_COUNT_DOWN)))
        {

#if(DEM_CFG_TFSLC_RESET_AFTER_AGING_AND_DISPLACEMENT)
            if((*StatusNew & (DEM_EVMEM_STSMASK_TESTFAILED_SLC | DEM_EVMEM_STSMASK_AGED)) == DEM_EVMEM_STSMASK_TESTFAILED_SLC)
#else
            if((*StatusNew & (DEM_EVMEM_STSMASK_CONFIRMED | DEM_EVMEM_STSMASK_AGED)) == DEM_EVMEM_STSMASK_CONFIRMED)
#endif
            {
                if(Dem_LibGetParamBool(DEM_CFG_EVMEM_TESTFAILED_TAC_SUPPORTED))
                {
                    *StatusNew = *StatusNew | DEM_EVMEM_STSMASK_TESTFAILED_TAC;
                }
                if(Dem_LibGetParamBool(DEM_CFG_EVMEM_TESTCOMPLETE_TAC_SUPPORTED))
                {
                    *StatusNew = *StatusNew | DEM_EVMEM_STSMASK_TESTCOMPLETE_TAC;
                }
            }
        }
   }
}

DEM_INLINE void Dem_EvMemSetAgingCounterOnEventPassed(Dem_EventIdType EventId, uint16_least LocId, uint16_least *StatusNew, uint16_least* WriteSts){
   if( ! Dem_LibGetParamBool(DEM_CFG_SUPPORT_AGINGCNTR_ONLY_WHEN_AGING_ALLOWED) || Dem_EvtParam_GetAgingAllowed(EventId) ){
        if((Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_AGINGCYC_STORE)) ||
                (Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_AGINGCYC_DIFF_UP)) ||
                (Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_AGINGCYC_DIFF_DOWN)))
        {
            if((Dem_EvMemGetEventMemStatus(LocId) & DEM_EVMEM_STSMASK_TESTFAILED) != 0u)
            {
                Dem_EvMemSetEventMemAgingCounter(LocId,(uint16_least)(Dem_EvMemGetCurrentAgingCycleCounterInt(EventId)));
#if(DEM_CFG_TFSLC_RESET_AFTER_AGING_AND_DISPLACEMENT)
                Dem_EvMemSetEventMemAgingCounterForTFSLC(LocId, (uint16_least)(Dem_EvMemGetCurrentAgingCycleCounterInt(EventId)));
#endif
                *WriteSts = *WriteSts | DEM_EVMEM_WRITEMASK_DATA;
            }
        }

        if((Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_COUNT_UP)) ||
                (Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_AGING_METHOD_COUNT_DOWN)))
        {

#if(DEM_CFG_TFSLC_RESET_AFTER_AGING_AND_DISPLACEMENT)
            if((*StatusNew & (DEM_EVMEM_STSMASK_TESTFAILED_SLC | DEM_EVMEM_STSMASK_AGED)) == DEM_EVMEM_STSMASK_TESTFAILED_SLC)
#else
            if((*StatusNew & (DEM_EVMEM_STSMASK_CONFIRMED | DEM_EVMEM_STSMASK_AGED)) == DEM_EVMEM_STSMASK_CONFIRMED)
#endif
            {
                if(Dem_LibGetParamBool(DEM_CFG_EVMEM_TESTCOMPLETE_TAC_SUPPORTED))
                {
                    *StatusNew = *StatusNew | DEM_EVMEM_STSMASK_TESTCOMPLETE_TAC;
                }
            }
        }
   }
}

DEM_INLINE Dem_boolean_least Dem_EvMemIsAgingCalculationAllowed(uint16_least locationStatus){
    return ((locationStatus & (DEM_EVMEM_STSMASK_CONFIRMED
#if(DEM_CFG_TFSLC_RESET_AFTER_AGING_AND_DISPLACEMENT)
            | DEM_EVMEM_STSMASK_TESTFAILED_SLC
#endif
    )) != 0u);
}

#endif
#endif

