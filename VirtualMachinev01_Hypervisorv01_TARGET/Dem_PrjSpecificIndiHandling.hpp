
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
#warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef DEM_PRJSPECIFICINDIHANDLING_H
#define DEM_PRJSPECIFICINDIHANDLING_H

#include "Dem_Cfg_Events.hpp"
#include "Dem_Types.hpp"

#define Dem_isAnyIndicatorAttribOn(X)            (FALSE)

#define Dem_IndicatorAttributeInitCheckNvM()     do {}while(0);

DEM_INLINE void Dem_ClearIndicatorAttributes(Dem_EventIdType EventId,Dem_UdsStatusByteType isoByteOld, Dem_UdsStatusByteType isoByteNew)
{
}

DEM_INLINE void Dem_SetIndicatorDeActivation_OnEvMemSetStatusNotification(Dem_EventIdType EventId, Dem_UdsStatusByteType isoByteOld, Dem_UdsStatusByteType isoByteNew)   {}

DEM_INLINE void Dem_SetIndicatorDeActivation_OnEvMemClearStatusNotification(Dem_EventIdType EventId, Dem_UdsStatusByteType isoByteOld, Dem_UdsStatusByteType isoByteNew)  {}

DEM_INLINE void Dem_SetIndicatorDeActivation_OnOperationCycleChange(Dem_EventIdType EventId, Dem_UdsStatusByteType isoByteOld, Dem_UdsStatusByteType isoByteNew)  {}

DEM_INLINE Dem_boolean_least Dem_EvtRequestsWarningIndicator (Dem_EventIdType EventId){}

void Dem_IndicatorAttribute_ConsistencyCheck(Dem_EventIdType EventId, uint16_least EventStatus );

void Dem_SetIndicatorDeActivation(Dem_EventIdType EventId, Dem_UdsStatusByteType isoByteOld, Dem_UdsStatusByteType isoByteNew);

void Dem_SetIndicatorActivation(Dem_EventIdType EventId, Dem_UdsStatusByteType isoByteOld, Dem_UdsStatusByteType isoByteNew);

void Dem_IndicatorAttributeMainFunction(void);

void Dem_IndicatorAttributeInit(void);

#define Dem_IndicatorAttributeShutdown()         do {}while(0);

#endif
