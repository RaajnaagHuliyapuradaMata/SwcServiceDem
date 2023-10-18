

#ifndef DEM_EVENTFHANDLING_H
#define DEM_EVENTFHANDLING_H

#include "Dem_Types.hpp"
#include "Dem_Cfg_Events.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

void Dem_ReportErrorStatusDisableQueue (void);
void Dem_ReportErrorStatusEnableQueue (void);
void Dem_PreInitErrorQueue(void);

#if(DEM_CFG_CHECKAPICONSISTENCY == TRUE)

Std_ReturnType Dem_GetEventFailed_GeneralEvtInfo(Dem_EventIdType EventId, boolean* EventFailed);
#endif

void Dem_EvtProcessPassedAndFailed (Dem_EventIdType EventId, Dem_EventStatusType EventStatus
                      DEM_DEBUGDATA_PARAM(Dem_DebugDataType debug0_ul, Dem_DebugDataType debug1_ul));

Dem_boolean_least Dem_EvtsRestoreFailurefromPreviousIC (Dem_EventIdType EventId);

#if(DEM_CFG_SETEVENTSTATUSCALLNOTIFICATION == DEM_CFG_SETEVENTSTATUSCALLNOTIFICATION_ON)

void Dem_SetEventStatusCallNotification (Dem_EventIdType EventId, boolean fault, Dem_DebugDataType debug0, Dem_DebugDataType debug1);

#endif

#if(DEM_CFG_SUSPICIOUS_SUPPORT)
void Dem_SetEventSuspicion_Internal (Dem_EventIdType EventId, boolean suspicion);
#endif

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
#endif
