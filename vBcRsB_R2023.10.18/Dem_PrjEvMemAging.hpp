
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef DEM_PRJEVMEMAGING_H
#define DEM_PRJEVMEMAGING_H

DEM_INLINE Dem_boolean_least Dem_EvMemIsAged(Dem_EventIdType EventId, uint16_least LocId, uint16_least StatusNew)
{
}

DEM_INLINE uint16_least Dem_EvMemGetEventMemAgingCounterScaled(const Dem_EvMemEventMemoryType *EventMemory)
{

}

DEM_INLINE void Dem_EvMemSetAgingCounterOnAgingCycle(Dem_EventIdType EventId, uint16_least LocId, uint16_least* StatusNew, uint16_least* WriteSts)
{

}

DEM_INLINE void Dem_EvMemSetAgingCounterOnEventFailed(Dem_EventIdType EventId, uint16_least LocId, uint16_least* StatusNew, uint16_least* WriteSts)
{

}

DEM_INLINE void Dem_EvMemSetAgingCounterOnEventPassed(Dem_EventIdType EventId, uint16_least LocId, uint16_least *StatusNew, uint16_least* WriteSts)
{

}

DEM_INLINE Dem_boolean_least Dem_EvMemIsAgingCalculationAllowed(uint16_least locationStatus)
{
}
#endif

