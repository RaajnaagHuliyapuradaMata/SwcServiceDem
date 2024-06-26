#include "Std_Types.hpp"

#include "Dem.hpp"
#include "Ara_Dem.hpp"
#include "Dem_EvMem.hpp"
#include "Dem_Events.hpp"
#include "Dem_EnvMain.hpp"
#include "Dem_Mapping.hpp"
#include "Dem_DTCs.hpp"
#include "Dem_Cfg.hpp"
#include "Dem_EvMemGen.hpp"
#include "Dem_ConsisChk.hpp"
#include "Dem_Lok_CallEvtStChngdCbk.hpp"
#include "DemAppInterfaceX.hpp"
#include "Ara_Dem.hpp"
#include "FiM.hpp"
#include "Dem_Lib.hpp"

#if(DEM_CFG_EVMEM_PROJECT_EXTENSION)
#include "Dem_PrjEvmemProjectExtension.hpp"
#endif

#include "Dem_ChronoSort.hpp"
#include "Dem_J1939EnvFreezeFrame.hpp"

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
DEM_ARRAY_DEFINE_CONST(Dem_NvmBlockIdType, Dem_EvMemNvmId, DEM_CFG_MAX_NUMBER_EVENT_ENTRY_ALL, DEM_CFG_EVMEMNVMIDS);
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
#if(DEM_CFG_EVMEM_MAX_MEMS > 1)

#if(DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY > 0)
#define DEM_LOCIDLIST_INIT_SECONDARY  (DEM_CFG_MAX_NUMBER_EVENT_ENTRY_PRIMARY + DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY),
#else
#define DEM_LOCIDLIST_INIT_SECONDARY
#endif

#if(DEM_CFG_MAX_NUMBER_EVENT_ENTRY_MIRROR > 0)
#define DEM_LOCIDLIST_INIT_MIRROR  (DEM_CFG_MAX_NUMBER_EVENT_ENTRY_PRIMARY + DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY + DEM_CFG_MAX_NUMBER_EVENT_ENTRY_MIRROR),
#else
#define DEM_LOCIDLIST_INIT_MIRROR
#endif

#define DEM_LOCIDLIST_INIT { \
        0u, \
        DEM_CFG_MAX_NUMBER_EVENT_ENTRY_PRIMARY, \
        DEM_LOCIDLIST_INIT_SECONDARY \
        DEM_LOCIDLIST_INIT_MIRROR \
}
#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
DEM_ARRAY_DEFINE_CONST(uint16_least, Dem_EvMemLocIdList, DEM_CFG_EVMEM_MAX_MEMS+1u, DEM_LOCIDLIST_INIT);
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
#endif

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"
static uint16 Dem_EvMemEvBuffOverflowCounterCopy;
boolean Dem_EvMemIsLocked;
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.hpp"
DEM_ARRAY_DEFINE(Dem_EvMemEventMemoryType, Dem_EvMemEventMemory, DEM_CFG_EVMEM_EVENTMEMORY_LENGTH);
#define DEM_STOP_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.hpp"

#define DEM_MAP_ORIGIN2ID_INVALIDORIGIN    {  0, FALSE  }
#define DEM_MAP_ORIGIN2ID_PERMANENT    DEM_MAP_ORIGIN2ID_INVALIDORIGIN
#define DEM_MAP_ORIGIN2ID_PRIMARY    {  DEM_CFG_EVMEM_MEMID_PRIMARY, TRUE  }

#if(DEM_CFG_MAX_NUMBER_EVENT_ENTRY_MIRROR > 0)
#define DEM_MAP_ORIGIN2ID_MIRROR    {  DEM_CFG_EVMEM_MEMID_MIRROR, TRUE  }
#else
#define DEM_MAP_ORIGIN2ID_MIRROR    DEM_MAP_ORIGIN2ID_INVALIDORIGIN
#endif

#if(DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY > 0)
#define DEM_MAP_ORIGIN2ID_SECONDARY    {  DEM_CFG_EVMEM_MEMID_SECONDARY, TRUE  }
#else
#define DEM_MAP_ORIGIN2ID_SECONDARY    DEM_MAP_ORIGIN2ID_INVALIDORIGIN
#endif

#define DEM_MAP_ORIGIN2ID  {                                        \
        DEM_MAP_ORIGIN2ID_INVALIDORIGIN,    \
        DEM_MAP_ORIGIN2ID_PRIMARY,     \
        DEM_MAP_ORIGIN2ID_MIRROR,     \
        DEM_MAP_ORIGIN2ID_PERMANENT,     \
        DEM_MAP_ORIGIN2ID_SECONDARY         \
}

#if(DEM_DTC_ORIGIN_PRIMARY_MEMORY   != 0x01) \
        || (DEM_DTC_ORIGIN_MIRROR_MEMORY    != 0x02) \
        || (DEM_DTC_ORIGIN_PERMANENT_MEMORY != 0x03) \
        || (DEM_DTC_ORIGIN_SECONDARY_MEMORY != 0x04)
#error mapping of origin to evMemId failure
#endif

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
DEM_ARRAY_DEFINE_CONST(Dem_EvMemMapOrigin2IdType, Dem_EvMemMapOrigin2Id, 5, DEM_MAP_ORIGIN2ID);
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

DEM_INLINE Dem_boolean_least Dem_EvMemIsClearByWriteRequired(uint16_least LocId)
{

   if(Dem_LibGetParamUI8(DEM_CFG_EVMEM_MIRROR) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_MIRROR_ON_CLEAR) )
   {
        if(Dem_EvMemIsOriginMirror(LocId))
        {
            return TRUE;
        }
   }

   if(!Dem_EvMemIsStored (Dem_EvMemGetEventMemStatus (LocId)))
   {
        return TRUE;
   }

    return FALSE;
}

DEM_INLINE Dem_boolean_least Dem_EvMemIsWriteImmediateRequired(uint16_least LocId)
{

   if(!Dem_LibGetParamBool(DEM_CFG_IMMEDIATE_NV_STORAGE_SUPPORTED))
   {
        return FALSE;
   }

   if(!Dem_Cfg_Dtc_GetNv_Storage (Dem_DtcIdFromEventId (Dem_EvMemGetEventMemEventId (LocId))))
   {
        return FALSE;
   }

   if(!Dem_LibGetParamBool(DEM_CFG_IMMEDIATE_NV_STORAGE_LIMIT_SUPPORTED))
   {
        return TRUE;
   }

   if(Dem_EvMemGetEventMemOccurrenceCounter(LocId) <= Dem_LibGetParamUI16(DEM_CFG_IMMEDIATE_NV_STORAGE_LIMIT))
   {
        return TRUE;
   }

    return FALSE;
}

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
static void Dem_EvMemEventMemoryWriteNotification(uint16_least LocId, uint16_least writeSts)
{
    DEM_UNUSED_PARAM(writeSts);

    Dem_EvMemSetEventMemStatus(LocId, Dem_EvMemGetEventMemStatus(LocId) & (~DEM_EVMEM_STSMASK_READER_COPY_CURRENT));

   if(Dem_EvMemIsClearByWriteRequired(LocId))
   {

        Dem_NvMClearBlockByWrite(Dem_EvMemGetNvmIdFromLocId (LocId));
   }
   else if(Dem_EvMemIsWriteImmediateRequired(LocId))
   {

        Dem_NvMWriteBlockImmediate(Dem_EvMemGetNvmIdFromLocId (LocId));
   }
   else{

        Dem_NvMWriteBlockOnShutdown(Dem_EvMemGetNvmIdFromLocId (LocId));
   }
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

DEM_INLINE Dem_boolean_least Dem_EvMemIsStatusNotificationRequired(uint16_least LocId)
{
    return (Dem_EvMemIsOriginPrimary(LocId) || Dem_EvMemIsOriginSecondary(LocId));
}

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

static void Dem_EvMemSetStatusNotification(uint16_least LocId, Dem_EventIdType EventId, Dem_EvMemActionType actionType)
{
    Dem_UdsStatusByteType isoByteOld, isoByteNew;
    Dem_UdsStatusByteType dtcStByteOld;
   if(Dem_EvMemIsStatusNotificationRequired(LocId))
   {
        if(actionType!=DEM_EVMEM_ACTIONTYPE_NONE)
        {
            DEM_ENTERLOCK_MON();
            Dem_StatusChange_GetOldStatus(EventId, &isoByteOld, &dtcStByteOld);
            if(actionType== DEM_EVMEM_ACTIONTYPE_CONFIRMATION)
            {
                Dem_EvtSt_HandleConfirmation(EventId);
            }else if(actionType == DEM_EVMEM_ACTIONTYPE_DISPLACEMENT)
            {
                Dem_EvtSt_HandleDisplacement(EventId);
            }else if(actionType == DEM_EVMEM_ACTIONTYPE_AGING)
            {
                Dem_EvtSt_HandleAging(EventId);
            }else if(actionType == DEM_EVMEM_ACTIONTYPE_IMMEDIATEAGING)
            {
                Dem_EvtSt_HandleImmediateAging(EventId);
            }else if(actionType == DEM_EVMEM_ACTIONTYPE_SETPENDING)
            {
                Dem_EvtSt_HandlePendingDTC(EventId, TRUE);
            }else if(actionType == DEM_EVMEM_ACTIONTYPE_RESETPENDING)
            {
                Dem_EvtSt_HandlePendingDTC(EventId, FALSE);
            }else if(actionType == DEM_EVMEM_ACTIONTYPE_AGINGOFCONFIRMED)
            {
                Dem_EvtSt_HandleAgingOfConfirmed(EventId);
            }else{

            }

            Dem_SetIndicatorDeActivation_OnEvMemSetStatusNotification(EventId, isoByteOld, Dem_EvtGetIsoByte(EventId));

#if DEM_CFG_DEPENDENCY_PENDING_ON

            if((actionType== DEM_EVMEM_ACTIONTYPE_CONFIRMATION) || (actionType == DEM_EVMEM_ACTIONTYPE_SETPENDING))
            {
                Dem_Dependencies_SetNodePending(EventId , TRUE);
            }

            if((actionType== DEM_EVMEM_ACTIONTYPE_RESETPENDING) || (actionType == DEM_EVMEM_ACTIONTYPE_DISPLACEMENT))
            {
                Dem_Dependencies_SetNodePending(EventId , FALSE);
            }
#endif

            isoByteNew = Dem_EvtGetIsoByte(EventId);

            DEM_EXITLOCK_MON();

            Dem_TriggerOn_EventStatusChange(EventId,isoByteOld,isoByteNew,dtcStByteOld);
        }
   }
}

static void Dem_EvMemClearOldEventStatusNotification(uint16_least LocId, Dem_EventIdType EventIdOld, uint16_least StatusOld)
{
   Dem_UdsStatusByteType isoByteOld, isoByteNew;
   Dem_UdsStatusByteType dtcStByteOld;

   if(Dem_LibGetParamUI8(DEM_CFG_EVCOMB) == Dem_LibGetParamUI8(DEM_CFG_EVCOMB_ONSTORAGE))
   {
   	if(Dem_EvMemIsStatusNotificationRequired (LocId))
   	{
   		if( Dem_EvMemIsStored(StatusOld) && (Dem_EvMemGetEventMemEventId(LocId) != EventIdOld))
   		{
   		    DEM_ENTERLOCK_MON();
   			Dem_StatusChange_GetOldStatus(EventIdOld, &isoByteOld, &dtcStByteOld);
   			Dem_EvtSt_HandleEvCombinationReplacement(EventIdOld);

#if DEM_CFG_DEPENDENCY_PENDING_ON
   			Dem_Dependencies_SetNodePending(EventIdOld , FALSE);
#endif

   			Dem_SetIndicatorDeActivation_OnEvMemClearStatusNotification(EventIdOld,isoByteOld, Dem_EvtGetIsoByte(EventIdOld));

                isoByteNew = Dem_EvtGetIsoByte(EventIdOld);

   			DEM_EXITLOCK_MON();

   			Dem_TriggerOn_EventStatusChange(EventIdOld,isoByteOld,isoByteNew,dtcStByteOld);
   		}
   	}
   }
}

DEM_INLINE void Dem_NotifyEvtDataChange(Dem_EventIdType EventId)
{
#if(DEM_CFG_EVT_DATACHANGEDCALLBACK != DEM_CFG_EVT_DATACHANGEDCALLBACK_OFF)
   if(Dem_EvtParam_GetTriggersDataChangedCallback(EventId))
   {
        (void)DEM_CFG_EVT_DATACHANGEDCALLBACK_FUNC(EventId);
   }
#else
    DEM_UNUSED_PARAM(EventId);
#endif
}

void Dem_EvMemSetStatusWithNotifications(uint16_least LocId, uint16_least StatusNew, uint16_least WriteSts, Dem_EvMemActionType actionType)
{
   Dem_EvMemSetEventMemStatus (LocId, StatusNew);

   if(WriteSts != DEM_EVMEM_WRITEMASK_NO)
   {

      Dem_EvMemEventMemoryWriteNotification (LocId, WriteSts);
      if(((WriteSts & DEM_EVMEM_WRITEMASK_EVENTDATA) != 0u) && (!Dem_EvMemIsOriginMirror(LocId)))
      {

          Dem_NotifyEvtDataChange(Dem_EvMemGetEventMemEventId(LocId));
      }
   }

   Dem_EvMemSetStatusNotification (LocId, Dem_EvMemGetEventMemEventId(LocId), actionType);
}

DEM_INLINE boolean Dem_EvMemProcessPassedEventsReport(Dem_EventIdType eventId, DEM_BITARRAY_CONSTFUNCPARAM(EvMemRecheckEvents))
{
   uint8 tempEnvBuffer[DEM_CFG_ENVMINSIZE_OF_RAWENVDATA];
   if( (Dem_EvtWasPassedReported (EvMemRecheckEvents, eventId)) && (!Dem_EvtSt_GetTestFailed(eventId)) )
   {
        if(Dem_IsEventStorageEnabledByDtcSetting (eventId))
        {
#if(DEM_CFG_EVMEM_EXTENDED_DATA_ON_PASSED_SUPPORTED)
            Dem_EnvCaptureED(eventId, tempEnvBuffer, DEM_CFG_ENVMINSIZE_OF_RAWENVDATA DEM_DEBUGDATA_PARAM(0,0));
#else
            tempEnvBuffer[0] = 0; // misra workaround
#endif
            Dem_EvMemSetEventPassedAllMem(eventId, tempEnvBuffer);
            return TRUE;
        }
   }
    return FALSE;
}

static void Dem_EvMemProcessPassedEvents (void){

#if(DEM_CFG_EVCOMB == DEM_CFG_EVCOMB_ONSTORAGE)
    Dem_EventIdListIterator eventIt;
#endif
   uint16_least       LocId;
    Dem_EventIdType eventId;
    DEM_BITARRAY_DEFINE(Dem_EvMemRecheckEvents,DEM_EVENTID_ARRAYLENGTH);

   if(Dem_EvMemEvBuffOverflowCounterCopy != Dem_EvtBuffer.OverflowCounter)
   {
        DEM_ENTERLOCK_MON();
        Dem_EvMemEvBuffOverflowCounterCopy = Dem_EvtBuffer.OverflowCounter;
        DEM_MEMCPY(&Dem_EvMemRecheckEvents, &Dem_EventWasPassedReported, DEM_SIZEOF_VAR(Dem_EventWasPassedReported));
        Dem_BitArrayClearAll(Dem_EventWasPassedReported,DEM_EVENTID_ARRAYLENGTH);
        DEM_EXITLOCK_MON();

        for(Dem_EvMemEventMemoryPrimaryUserdefLocIteratorNew    (&LocId);
                Dem_EvMemEventMemoryPrimaryUserdefLocIteratorIsValid(&LocId);
                Dem_EvMemEventMemoryPrimaryUserdefLocIteratorNext   (&LocId))
        {

            if(Dem_EvMemIsStored(Dem_EvMemGetEventMemStatus(LocId)))
            {
#if(DEM_CFG_EVCOMB == DEM_CFG_EVCOMB_ONSTORAGE)
                if(!Dem_EvMemIsEventPassedAllowed (Dem_EvMemGetEventMemEventId(LocId), LocId))
                {
                    continue;
                }
                for(Dem_EventIdListIteratorNewFromDtcId (&eventIt, Dem_DtcIdFromEventId(Dem_EvMemGetEventMemEventId(LocId)));
                        Dem_EventIdListIteratorIsValid (&eventIt);
                        Dem_EventIdListIteratorNext (&eventIt))
                {
                    eventId = Dem_EventIdListIteratorCurrent (&eventIt);
                    if(Dem_EvMemProcessPassedEventsReport(eventId, Dem_EvMemRecheckEvents))
                    {
                        break;
                    }
                }
#else
                eventId = Dem_EvMemGetEventMemEventId(LocId);
                (void)Dem_EvMemProcessPassedEventsReport(eventId, Dem_EvMemRecheckEvents);
#endif
            }
        }
   }
}

void Dem_EvMemEraseEventMemory(uint16_least MemId)
{
   uint16_least LocId;

    DEM_ASSERT(Dem_EvMemIsMemIdValid(MemId),DEM_DET_APIID_EVMEMERASEEVENTMEMORY,0);

   for(Dem_EvMemEventMemoryLocIteratorNew     (&LocId, MemId);
         Dem_EvMemEventMemoryLocIteratorIsValid (&LocId, MemId);
         Dem_EvMemEventMemoryLocIteratorNext    (&LocId, MemId))
   {
      if(!Dem_EvMemIsEmpty (Dem_EvMemGetEventMemStatus (LocId)))
      {

         Dem_EvMemSetStatusWithNotifications(LocId,Dem_EvMemSetToEmpty(),DEM_EVMEM_WRITEMASK_CLEAR,DEM_EVMEM_ACTIONTYPE_NONE);

         DEM_EVMEM_CLEAROBJ(Dem_EvMemEventMemory[LocId]);
      }
   }
}

void Dem_EvMemForceClearEventMemoryLocation(uint16_least LocId, uint16_least WriteSts, Dem_EvMemActionType actionType)
{
   uint16_least Status;
   uint16_least StatusNew;

    Status = Dem_EvMemGetEventMemStatus (LocId);

   if(Dem_EvMemIsStored (Status))
   {
      StatusNew = Dem_EvMemSetToDelete (Status);

#if(DEM_CFG_EVMEM_MIRROR_MEMORY_SUPPORTED)
        if(Dem_LibGetParamUI8(DEM_CFG_EVMEM_MIRROR) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_MIRROR_ON_CLEAR))
        {
            if(Dem_EvtParam_GetEventIsStoredInMirror(Dem_EvMemGetEventMemEventId (LocId)))
            {
                if(Dem_EvMemIsTriggerMirrorOnClear (Dem_EvMemGetEventMemEventId (LocId), LocId, Status, StatusNew))
                {
                    Dem_EvMemCopyToMirrorMemory (LocId);
                }
            }
        }
#endif

      Dem_EvMemSetStatusWithNotifications(LocId,StatusNew,WriteSts, actionType);
   }
}

void Dem_EvMemClearEvent(Dem_EventIdType EventId, uint16_least MemId)
{
   uint16_least LocId;

    DEM_ASSERT(Dem_EvMemIsMemIdValid(MemId),DEM_DET_APIID_EVMEMCLEAREVENT,0);

    LocId = Dem_EvMemGetEventMemoryLocIdOfEvent (EventId, MemId);
   if(Dem_EvMemIsEventMemLocIdValid (LocId))
   {
        if(Dem_EvMemGetEventMemEventId (LocId) == EventId)
        {
            Dem_EvMemForceClearEventMemoryLocation(LocId, DEM_EVMEM_WRITEMASK_CLEAR, DEM_EVMEM_ACTIONTYPE_RESETPENDING);
        }
   }
}

uint32 Dem_EvMemGetNewEventMemoryTimeId(uint16_least MemId)
{
   uint32       TimeId;
   uint32       MaxTimeId;
   uint16_least LocId;

    MaxTimeId = 0;
   for(Dem_EvMemEventMemoryLocIteratorNew    (&LocId, MemId);
            Dem_EvMemEventMemoryLocIteratorIsValid(&LocId, MemId);
            Dem_EvMemEventMemoryLocIteratorNext   (&LocId, MemId))
   {
        if( ( (!Dem_LibGetParamBool(DEM_CFG_EVMEM_SHADOW_ENTRIES_TIMEID_SUPPORTED)) &&   Dem_EvMemIsStored(Dem_EvMemGetEventMemStatus(LocId)) ) ||
            (   Dem_LibGetParamBool(DEM_CFG_EVMEM_SHADOW_ENTRIES_TIMEID_SUPPORTED)  && (!Dem_EvMemIsEmpty(Dem_EvMemGetEventMemStatus(LocId))) ) )
        {
            TimeId = Dem_EvMemGetEventMemTimeId(LocId);
            if(MaxTimeId < TimeId)
            {
                MaxTimeId = TimeId;
            }
        }
   }

   if(Dem_LibGetParamBool(DEM_CFG_EVMEM_SHADOW_ENTRIES_TIMEID_SUPPORTED))
   {

        if(MaxTimeId >= DEM_EVMEM_MAX_TIMEID)
        {
            for(Dem_EvMemEventMemoryLocIteratorNew    (&LocId, MemId);
                    Dem_EvMemEventMemoryLocIteratorIsValid(&LocId, MemId);
                    Dem_EvMemEventMemoryLocIteratorNext   (&LocId, MemId))
            {

                Dem_EvMemSetEventMemTimeId(LocId,0);

                Dem_EvMemEventMemoryWriteNotification(LocId, DEM_EVMEM_WRITEMASK_DATA);
            }

            MaxTimeId = 0;      }
   }

   if(MaxTimeId < DEM_EVMEM_MAX_TIMEID)
   {
        MaxTimeId++;
   }

    return MaxTimeId;
}

#if !DEM_CFG_EVMEM_USERDEF_EVENT_MEM_STORAGE_STRATEGY
DEM_INLINE uint16_least Dem_EvMemGetEventMemoryDisplacementLocation(Dem_EventIdType EventId, Dem_EvBuffEventType EventType, uint16_least MemId)
{
   uint16_least       LocId;
   uint16_least       SearchLocId;
   uint16_least       Prio;
   uint16_least       SearchPrio;
   uint16_least       Active;
   uint16_least       SearchActive;
   uint32             TimeId;
   uint32             SearchTimeId;
#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
   uint16_least       LocIdObdServ02;
#endif
    SearchActive    =  DEM_EVMEM_STSMASK_TESTFAILED;
    SearchTimeId    =  0;
    SearchLocId     =  DEM_EVMEM_INVALID_LOCID;

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)

    LocIdObdServ02 = rba_DemObdBasic_EvMem_GetLocationOfOBDFreezeFrame();

#endif

    SearchPrio      =  Dem_EvtParam_GetEventPriority(EventId);
   if(EventType == C_EVENTTYPE_UNROBUST)
   {
        SearchPrio = SearchPrio + DEM_EVMEM_PRIO_OFFSET;
   }

   for(Dem_EvMemEventMemoryLocIteratorNew    (&LocId, MemId);
            Dem_EvMemEventMemoryLocIteratorIsValid(&LocId, MemId);
            Dem_EvMemEventMemoryLocIteratorNext   (&LocId, MemId))
   {
        if(Dem_EvMemIsStored(Dem_EvMemGetEventMemStatus(LocId)))
        {
            if((    Dem_EvMemIsDisplaceEventMemoryLocAllowed(EventId, LocId))
#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
                    && (rba_DemObdBasic_EvMem_IsDisplaceEventMemoryLocAllowed(EventId, LocId, LocIdObdServ02))
#endif
            )
            {
                Active    =  Dem_EvMemGetEventMemStatus(LocId) & DEM_EVMEM_STSMASK_TESTFAILED;
                TimeId    =  Dem_EvMemGetEventMemTimeId(LocId);
                Prio      =  Dem_EvtParam_GetEventPriority(Dem_EvMemGetEventMemEventId(LocId));
                if((Dem_EvMemGetEventMemStatus(LocId) & DEM_EVMEM_STSMASK_TESTFAILED_SLC) == 0u)
                {
                    Prio = Prio + DEM_EVMEM_PRIO_OFFSET;
                }

                if((Prio > SearchPrio) || ((Prio == SearchPrio) && (Active < SearchActive))
                        || ((Prio == SearchPrio) && (Active == SearchActive) && (TimeId <= SearchTimeId)))
                {
                    SearchLocId = LocId;
                    SearchPrio = Prio;
                    SearchActive = Active;
                    SearchTimeId = TimeId;
                }
         }
      }
   }

   if(SearchLocId != DEM_EVMEM_INVALID_LOCID)
   {
      Dem_EvMemForceClearEventMemoryLocation(SearchLocId, DEM_EVMEM_WRITEMASK_CLEAR, DEM_EVMEM_ACTIONTYPE_DISPLACEMENT);
   }

    return (SearchLocId);
}

DEM_INLINE uint16_least Dem_EvMemGetEventMemoryDisplacementLocationFIFO(Dem_EventIdType EventId, Dem_EvBuffEventType EventType, uint16_least MemId)
{
   uint16_least       LocId;
   uint16_least       SearchLocId;
   uint32             TimeId;
   uint32             SearchTimeId;

    DEM_UNUSED_PARAM(EventType);

    SearchTimeId    =  DEM_EVMEM_MAX_TIMEID;
    SearchLocId     =  DEM_EVMEM_INVALID_LOCID;

   for(   Dem_EvMemEventMemoryLocIteratorNew    (&LocId, MemId);
   		Dem_EvMemEventMemoryLocIteratorIsValid(&LocId, MemId);
   		Dem_EvMemEventMemoryLocIteratorNext   (&LocId, MemId))
   {
   	if(Dem_EvMemIsStored(Dem_EvMemGetEventMemStatus(LocId)))
   	{
   		if(Dem_EvMemIsDisplaceEventMemoryLocAllowed(EventId, LocId))
   		{
   			TimeId = Dem_EvMemGetEventMemTimeId(LocId);
   			if(TimeId <= SearchTimeId)
   			{
   				SearchLocId    = LocId;
   				SearchTimeId   = TimeId;
   			}
   		}
   	}
   }

   if(SearchLocId != DEM_EVMEM_INVALID_LOCID)
   {
   	Dem_EvMemForceClearEventMemoryLocation(SearchLocId, DEM_EVMEM_WRITEMASK_CLEAR, DEM_EVMEM_ACTIONTYPE_DISPLACEMENT);
   }

    return (SearchLocId);
}

uint16_least Dem_EvMemGetEventMemoryStorageLocation(Dem_EventIdType EventId, Dem_EvBuffEventType EventType, uint16_least MemId, Dem_boolean_least isDisplacementSupported, uint16_least displacementStrategy)
{

   uint16_least Status;
   uint16_least LocId;
   uint16_least StorageLocId;
   uint16_least StoragePrio;

    StoragePrio  = DEM_EVMEM_STORAGE_PRIO_UNDEF;
    StorageLocId = DEM_EVMEM_INVALID_LOCID;
   for(Dem_EvMemEventMemoryLocIteratorNew    (&LocId, MemId);
            Dem_EvMemEventMemoryLocIteratorIsValid(&LocId, MemId);
            Dem_EvMemEventMemoryLocIteratorNext   (&LocId, MemId))
   {

        Status = Dem_EvMemGetEventMemStatus(LocId);

        if(Dem_EvMemIsEmpty(Status))
        {
            if(StoragePrio < DEM_EVMEM_STORAGE_PRIO_EMPTY)
            {
                StorageLocId = LocId;
                StoragePrio  = DEM_EVMEM_STORAGE_PRIO_EMPTY;
            }
        }
        else{
            if(Dem_EvMemIsEqualEvent(EventId, Dem_EvMemGetEventMemEventId(LocId)))
            {
                StorageLocId = LocId;
                break;
            }

            if(Dem_EvMemIsDeleted(Status))
            {
                if(StoragePrio < DEM_EVMEM_STORAGE_PRIO_DELETED)
                {
                    StorageLocId = LocId;
                    StoragePrio  = DEM_EVMEM_STORAGE_PRIO_DELETED;
                }
                else{
                    if(Dem_LibGetParamBool(DEM_CFG_EVMEM_SHADOW_ENTRIES_TIMEID_SUPPORTED))
                    {
                        if(StoragePrio == DEM_EVMEM_STORAGE_PRIO_DELETED)
                        {
                            if(Dem_EvMemGetEventMemTimeId(LocId) < Dem_EvMemGetEventMemTimeId(StorageLocId))
                            {
                                StorageLocId = LocId;
                            }
                        }
                    }
                }
            }
        }
   }

   if(StorageLocId == DEM_EVMEM_INVALID_LOCID)
   {
        Dem_EvMemGenReportEventMemoryOverflowByOrigin(Dem_EvMemGenGetDtcOrginFromMemId(MemId));

        if(isDisplacementSupported)
        {
            if(displacementStrategy == DEM_CFG_EVMEM_DISPLACEMENT_STRATEGY_AUTOSAR)
            {
                StorageLocId = Dem_EvMemGetEventMemoryDisplacementLocation(EventId, EventType, MemId);

            }
            else if(displacementStrategy == DEM_CFG_EVMEM_DISPLACEMENT_STRATEGY_FIFO)
            {
                if(Dem_LibGetParamUI8(DEM_CFG_EVMEM_MIRROR_DISPLACEMENT_STRATEGY) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_DISPLACEMENT_STRATEGY_FIFO))
                {
                    StorageLocId = Dem_EvMemGetEventMemoryDisplacementLocationFIFO(EventId, EventType, MemId);
                }
            }
            else{
                DEM_UNUSED_PARAM(StorageLocId);
#if(DEM_CFG_EVMEM_MEMORY_DISPLACEMENT_STRATEGY == DEM_CFG_EVMEM_DISPLACEMENT_STRATEGY_CUST) || (DEM_CFG_EVMEM_MIRROR_DISPLACEMENT_STRATEGY == DEM_CFG_EVMEM_DISPLACEMENT_STRATEGY_CUST)
                StorageLocId = Dem_EvMemGetEventMemoryDisplacementLocationCust(EventId, EventType, (uint16)MemId);
#endif
            }
        }
   }

    return(StorageLocId);
}
#endif

static void Dem_EvMemUpdateFFDataForConfRec(Dem_EventIdType EventId, uint8 FFRecNum, uint16_least LocId, const uint8* EnvData, Dem_EnvTriggerParamType *TriggerParam, uint16_least* WriteSts)
{
    Dem_TriggerType ConfTrigger;
   boolean ConfUpdate;
   uint16_least Counter;
   uint8 FFIndex;

    Dem_EnvGetFFRecordTriggerAndUpdate(FFRecNum, &ConfTrigger, &ConfUpdate );

   if( (Dem_EnvIsTriggerSet(TriggerParam->currentTrigger,ConfTrigger) &&
        (!Dem_EnvIsTriggerSet(TriggerParam->storedTrigger, ConfTrigger) || ConfUpdate))

        || (Dem_EnvIsTriggerSet(Dem_GetSmallerTrigger(TriggerParam->currentTrigger),ConfTrigger) &&
                (!Dem_EnvIsTriggerSet(TriggerParam->storedTrigger, ConfTrigger))))
   {
        FFIndex = Dem_EnvGetIndexFromFFRecNum(EventId, FFRecNum);

        Dem_EnvCopyRawFF(EventId, Dem_EvMemGetEventMemData(LocId), Dem_EvMemGetEventMemDataSize(), FFIndex, EnvData);
        *WriteSts = *WriteSts | DEM_EVMEM_WRITEMASK_EVENTDATA;

        if(!Dem_EnvIsTriggerSet(TriggerParam->storedTrigger, ConfTrigger))
        {
            Counter = Dem_EvMemGetEventMemFreezeFrameCounter(LocId);
            Counter++;

            Dem_EvMemSetEventMemLocFreezeFrameCounter(LocId, Counter);

            *WriteSts = *WriteSts | DEM_EVMEM_WRITEMASK_DATA;
            Dem_EnvSetTrigger(&TriggerParam->matchingTrigger, ConfTrigger);
        }
   }
}

static void Dem_EvMemUpdateExtendedData(Dem_EventIdType EventId, const uint8 *EnvData, uint16_least LocId, Dem_EnvTriggerParamType *TriggerParam)
{
   uint8 EnvDataLocal[DEM_CFG_ENVMINSIZE_OF_RAWENVDATA];

   if(Dem_EnvIsAnyTriggerSet(TriggerParam->currentTrigger))
   {
        if(Dem_EnvHasExtendedData(EventId))
        {
            if(EnvData == NULL_PTR)
            {
                Dem_EnvCaptureED(EventId, EnvDataLocal, DEM_SIZEOF_VAR(EnvDataLocal)DEM_DEBUGDATA_PARAM(0, 0));
                Dem_EnvCopyRawED(EventId, Dem_EvMemGetEventMemData(LocId), Dem_EvMemGetEventMemDataSize(), EnvDataLocal, TriggerParam);
            }
            else{
                Dem_EnvCopyRawED(EventId, Dem_EvMemGetEventMemData(LocId), Dem_EvMemGetEventMemDataSize(), EnvData, TriggerParam);
            }
        }
   }
}

static void Dem_EvMemUpdateFreezeFrameData(Dem_EventIdType EventId, const uint8 *EnvData, uint16_least LocId, Dem_EnvTriggerParamType *TriggerParam, uint16_least* WriteSts)
{

   uint16_least Counter;
   uint16_least Threshold;
   uint8 FFRecNum;
   uint8 indx;

   if(Dem_EnvHasFreezeFrame(EventId))
   {
        if(Dem_LibGetParamUI8(DEM_CFG_FFRECNUM) == Dem_LibGetParamUI8(DEM_CFG_FFRECNUM_CALCULATED))
        {

            if(Dem_EnvIsTriggerSet(TriggerParam->currentTrigger, DEM_TRIGGER_ON_TEST_FAILED))
            {
                Counter = Dem_EvMemGetEventMemFreezeFrameCounter(LocId);
                Threshold = Dem_EvtParam_GetMaxNumberFreezeFrameRecords(EventId);
                if(Counter < Threshold)
                {
                    Counter++;
                    *WriteSts = *WriteSts | DEM_EVMEM_WRITEMASK_DATA;
                }

                if((Threshold > 1u) || ((Dem_EvMemGetEventMemFreezeFrameCounter(LocId) == 0u)))
                {
                    Dem_EnvCopyRawFF(EventId, Dem_EvMemGetEventMemData(LocId), Dem_EvMemGetEventMemDataSize(), (uint8) (Counter - 1u), EnvData);
                    *WriteSts = *WriteSts | DEM_EVMEM_WRITEMASK_EVENTDATA;
                }

                Dem_EvMemSetEventMemLocFreezeFrameCounter(LocId, Counter);

            }
        }
        else{
            for(indx = 0; indx < Dem_EvtParam_GetMaxNumberFreezeFrameRecords(EventId); indx++)
            {
                FFRecNum = Dem_EnvGetFFRecNumFromIndex(EventId, indx);
                if(Dem_EnvIsFFRecNumValid(EventId, FFRecNum))
                {
                    Dem_EvMemUpdateFFDataForConfRec(EventId, FFRecNum, LocId, EnvData, TriggerParam, WriteSts);
                }
            }
        }
   }
}

static void Dem_EvMemUpdateEnvData(Dem_EventIdType EventId,const uint8 *EnvData,uint16_least LocId,Dem_TriggerType Trigger,uint16_least *WriteSts, uint8 EnvDataUpdate)
{
    Dem_EnvTriggerParamType TriggerParam;

    TriggerParam.currentTrigger = Trigger;
    TriggerParam.storedTrigger = Dem_EvMemGetEventMemTrigger(LocId);
    TriggerParam.matchingTrigger = DEM_TRIGGER_NONE;

   if( ((EnvDataUpdate == DEM_EVMEM_UPDATE_EXTDATA_AND_FFDATA) || (EnvDataUpdate == DEM_EVMEM_UPDATE_EXTDATA))
            && (Dem_LibGetParamBool(DEM_CFG_EVMEM_EXTENDED_DATA_SUPPORTED)))
   {
        Dem_EvMemUpdateExtendedData(EventId, EnvData, LocId, &TriggerParam );
   }

   if( ((EnvDataUpdate == DEM_EVMEM_UPDATE_EXTDATA_AND_FFDATA) || (EnvDataUpdate == DEM_EVMEM_UPDATE_FFDATA))
            && (Dem_LibGetParamBool(DEM_CFG_EVMEM_FREEZE_FRAME_SUPPORTED)))
   {
        Dem_EvMemUpdateFreezeFrameData(EventId, EnvData, LocId, &TriggerParam, WriteSts);
   }

   if(Dem_EnvIsAnyTriggerSet(TriggerParam.matchingTrigger ))
   {
        Dem_EnvSetTrigger(&TriggerParam.storedTrigger,( TriggerParam.matchingTrigger));
        Dem_EvMemSetEventMemTrigger(LocId,TriggerParam.storedTrigger);
        *WriteSts = *WriteSts | DEM_EVMEM_WRITEMASK_EVENTDATA;
   }
}

void Dem_EvMemSetEventFailed(Dem_EventIdType EventId, uint16_least MemId, const uint8 *EnvData)
{
   uint16_least LocId;
   uint16_least StatusOld;
   uint16_least StatusNew;
   uint16_least Counter;
   uint16_least Threshold;
   uint16_least WriteSts;

    Dem_EventIdType EventIdOld;
    Dem_EvMemActionType actiontype = DEM_EVMEM_ACTIONTYPE_NONE;

   if(!Dem_GetEvMemLockInternal())
   {

        DEM_ASSERT(Dem_isEventIdValid(EventId),DEM_DET_APIID_EVMEMSETEVENTFAILED,0);
        DEM_ASSERT(Dem_EvMemIsMemIdValid(MemId),DEM_DET_APIID_EVMEMSETEVENTFAILED,2);

        if(!Dem_isDtcIdValid (Dem_DtcIdFromEventId (EventId)))
        {
            return;
        }

        WriteSts = DEM_EVMEM_WRITEMASK_NO;

        if(Dem_EvMemIsEventFailedAllowed (EventId, MemId))
        {
            LocId = Dem_EvMemGetEventMemoryStorageLocation (EventId, C_EVENTTYPE_SET, MemId, Dem_EvMemIsEventMemoryDisplacementSupported (MemId), DEM_CFG_EVMEM_MEMORY_DISPLACEMENT_STRATEGY);
            if(Dem_EvMemIsEventMemLocIdValid (LocId))
            {

                if(!Dem_EvMemIsStored (Dem_EvMemGetEventMemStatus (LocId)))
                {
                    DEM_EVMEM_CLEAROBJ(Dem_EvMemEventMemory[LocId]);

                }
                else{
                    Dem_EvMemResetCyclesSinceLastFailed(LocId);
                    Dem_EvMemResetCyclesSinceLastFailedExcludingTNC(LocId);
                }

                StatusOld = Dem_EvMemGetEventMemStatus (LocId);
                StatusNew = StatusOld;

                if((StatusNew & DEM_EVMEM_STSMASK_TESTFAILED_TFC) == 0u)
                {
                    Dem_EvMemIncFailedCycles(LocId);
                }

                StatusNew = StatusNew | DEM_EVMEM_STSMASK_TESTFAILED | DEM_EVMEM_STSMASK_TESTFAILED_SLC | DEM_EVMEM_STSMASK_STORED;

                if(Dem_LibGetParamBool(DEM_CFG_EVMEM_TESTCOMPLETE_TFC_SUPPORTED))
                {
                    StatusNew = StatusNew | DEM_EVMEM_STSMASK_TESTCOMPLETE_TFC;
                }

            	StatusNew = StatusNew | DEM_EVMEM_STSMASK_PENDING | DEM_EVMEM_STSMASK_PENDING_NFC | DEM_EVMEM_STSMASK_TESTFAILED_TFC;
#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
                if(Dem_EvMemIsEdgeTrigger (StatusOld, StatusNew, DEM_EVMEM_STSMASK_PENDING))
                {
                    rba_DemObdBasic_EvMem_StatusNotificationPending(LocId, EventId);
                }
#endif

               if(Dem_EvMemIsEdgeTrigger (StatusOld, StatusNew, DEM_EVMEM_STSMASK_TESTFAILED_TFC))
               {

                   Threshold = Dem_EvtParam_GetFailureConfirmationThreshold(EventId);
                   Counter = Dem_EvMemGetEventMemFailureCounter (LocId);
                   if(Dem_EvMemIsEdgeTrigger (StatusOld, StatusNew, DEM_EVMEM_STSMASK_PENDING))
                   {
                       Counter = 0;
                   }

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
                   rba_DemObdBasic_EvMem_CommonMilDebModifyFailureCounter(LocId, MemId, EventId, &Counter);
#endif

                   if(Counter < Threshold)
                   {
                       Counter++;
                       if(Counter >= Threshold)
                       {
                           StatusNew = StatusNew | DEM_EVMEM_STSMASK_CONFIRMED | DEM_EVMEM_STSMASK_PENDING_CONFIRMED;
#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
                           rba_DemObdBasic_EvMem_StatusNotificationThresholdReached(LocId, EventId, &StatusNew);
#endif
                       }
                       Dem_EvMemSetEventMemFailureCounter (LocId, (uint8) Counter);
                       WriteSts = WriteSts | DEM_EVMEM_WRITEMASK_DATA;
                   }
               }

                if((StatusNew & DEM_EVMEM_STSMASK_PENDING) != 0u)
                {
                    actiontype = DEM_EVMEM_ACTIONTYPE_SETPENDING;
                }

                if((StatusNew & DEM_EVMEM_STSMASK_CONFIRMED) != 0u)
                {
                    actiontype = DEM_EVMEM_ACTIONTYPE_CONFIRMATION;

   			    if(Dem_EvMemIsEdgeTrigger (StatusOld, StatusNew, DEM_EVMEM_STSMASK_CONFIRMED))
   			    {
   			        Dem_EvMemGenReportConfirmedEvent(EventId, MemId);
#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
                        rba_DemObdBasic_EvMem_StatusNotificationConfirmed(LocId, EventId, &StatusNew);
#endif
   			    }
   			}

                if(Dem_LibGetParamBool(DEM_CFG_EVMEM_OCCURRENCE_COUNTER_SUPPORTED))
                {

                    if(!Dem_EvMemIsStored (StatusOld))
                    {
                        Counter = 1;
                        Dem_EvMemSetEventMemOccurrenceCounter (LocId, Counter);
                        WriteSts = WriteSts | DEM_EVMEM_WRITEMASK_OCCCOUNTER;
                    }
                    else
                    {
                        if(Dem_EvMemIsTriggerOccurrenceCounter (EventId, MemId, StatusOld, StatusNew))
                        {
                            Counter = Dem_EvMemGetEventMemOccurrenceCounter (LocId);
                            if(Counter < DEM_CFG_EVMEM_OCCURRENCE_COUNTER_MAX)
                            {
                                Counter++;
                                Dem_EvMemSetEventMemOccurrenceCounter (LocId, Counter);
                                WriteSts = WriteSts | DEM_EVMEM_WRITEMASK_OCCCOUNTER;
                            }
                        }
                    }
                }

                if(Dem_LibGetParamBool(DEM_CFG_EVMEM_AGING_COUNTER_SUPPORTED))
                {
                    Dem_EvMemSetAgingCounterOnEventFailed (EventId, LocId, &StatusNew, &WriteSts);
                }

#if(DEM_CFG_EVMEM_PROJECT_EXTENSION)
                {
                    Dem_EvMemProjectExtensionFailed(EventId, LocId, &WriteSts);
                }
#endif

#if(DEM_CFG_REPORT_CHRONOLOGICAL_ORDER_HOOKS_ENABLED)
                Dem_ChronoSortEvMemUpdateSortId(LocId, MemId,StatusOld, StatusNew,&WriteSts );
#endif

                if(Dem_LibGetParamBool(DEM_CFG_EVMEM_EXTENDED_DATA_SUPPORTED) || Dem_LibGetParamBool(DEM_CFG_EVMEM_FREEZE_FRAME_SUPPORTED))
                {
                    Dem_EvMemUpdateEnvData(EventId,EnvData,LocId,Dem_EvMemGetTriggerOnFailed(StatusOld, StatusNew), &WriteSts, DEM_EVMEM_UPDATE_EXTDATA_AND_FFDATA);
                }

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)

                if(rba_DemObdBasic_EvMem_IsTriggerObdFreezeFrame(EventId, MemId, StatusOld, StatusNew))
                {
                    rba_DemObdBasic_EvMem_CopyFreezeFrame(EventId, Dem_EvMemGetEventMemData (LocId), Dem_EvMemGetEventMemDataSize(), EnvData);
                }
#endif

#if(DEM_CFG_J1939DCM_FREEZEFRAME_SUPPORT || DEM_CFG_J1939DCM_EXPANDED_FREEZEFRAME_SUPPORT)
                if(Dem_J1939EvMem_IsTriggerFreezeFrame(EventId, MemId, StatusOld, StatusNew))
                {
                    Dem_J1939EvMem_CopyFreezeFrame(EventId, Dem_EvMemGetEventMemData (LocId), Dem_EvMemGetEventMemDataSize(), EnvData);
                }
#endif

                EventIdOld = Dem_EvMemGetEventMemEventId(LocId);
                if(Dem_EvMemIsNvStatusChanged (EventId, StatusOld, StatusNew))
                {
                    WriteSts = WriteSts | DEM_EVMEM_WRITEMASK_DATA;
                }

                if(WriteSts != DEM_EVMEM_WRITEMASK_NO)
                {
                    Dem_EvMemSetEventMemEventId (LocId, EventId);

                    Dem_EvMemSetEventMemTimeId (LocId, Dem_EvMemGetNewEventMemoryTimeId (MemId));
                }

   			Dem_EvMemSetStatusWithNotifications(LocId,StatusNew,WriteSts,actiontype);

   			Dem_EvMemClearOldEventStatusNotification(LocId, EventIdOld, StatusOld);

#if(DEM_CFG_EVMEM_MIRROR_MEMORY_SUPPORTED)
                if(Dem_LibGetParamUI8(DEM_CFG_EVMEM_MIRROR) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_MIRROR_ON_FAILED))
                {
                    if(Dem_EvtParam_GetEventIsStoredInMirror(EventId))
                    {
                        if(Dem_EvMemIsTriggerMirrorOnFailed (EventId, MemId, StatusOld, StatusNew))
                        {
                            Dem_EvMemCopyToMirrorMemory (LocId);
                        }
                    }
                }
#endif
            }
        }
   }
}

static void Dem_EvMemReaderCopiesUpdate(void){
#if DEM_CFG_EVMEM_READ_FROM_DIFFERENT_TASK
   uint16_least LocId;
   uint16_least Status;

   for(Dem_EvMemEventMemoryAllLocIteratorNew    (&LocId);
         Dem_EvMemEventMemoryAllLocIteratorIsValid(&LocId);
         Dem_EvMemEventMemoryAllLocIteratorNext   (&LocId))
   {
        Status = Dem_EvMemGetEventMemStatus(LocId);
        if((Status & DEM_EVMEM_STSMASK_READER_COPY_CURRENT) != DEM_EVMEM_STSMASK_READER_COPY_CURRENT)
        {
            Dem_EvMemSetEventMemStatus(LocId, Status | DEM_EVMEM_STSMASK_READER_COPY_CURRENT);

            Dem_EvMemReaderCopiesEnterLock();
            Dem_EvMemEventMemory[Dem_EvMemLocId2ReaderCopyLocId(LocId)] = Dem_EvMemEventMemory[LocId];
            Dem_EvMemReaderCopiesExitLock();
        }
   }
#endif
}

static uint16_least Dem_EvMemGetEventMemoryOrReaderCopyLocIdOfEvent(Dem_EventIdType EventId, uint16_least MemId, Dem_boolean_least SearchInReaderCopy)
{
   uint16_least LocId;
   uint16_least LocIdIt;
   uint16_least LocIdOfStoredEvent;

    DEM_ASSERT(Dem_EvMemIsMemIdValid(MemId),DEM_DET_APIID_EVMEMGETEVENTMEMORYLOCIDOFEVENT,0);

    LocIdOfStoredEvent = DEM_EVMEM_INVALID_LOCID;
   for(Dem_EvMemEventMemoryLocIteratorNew(&LocIdIt, MemId);
         Dem_EvMemEventMemoryLocIteratorIsValid(&LocIdIt, MemId);
         Dem_EvMemEventMemoryLocIteratorNext(&LocIdIt, MemId))
   {
        if(SearchInReaderCopy)
        {
            if(Dem_LibGetParamBool(DEM_CFG_EVMEM_READ_FROM_DIFFERENT_TASK))
            {
                DEM_ASSERT_ISLOCKED();
            }
            LocId = Dem_EvMemLocId2ReaderCopyLocId(LocIdIt);
        }
        else{
            LocId = LocIdIt;
        }

        if(Dem_EvMemIsStored (Dem_EvMemGetEventMemStatus (LocId)))
        {
            if(Dem_EvMemIsEqualEvent (EventId, Dem_EvMemGetEventMemEventId (LocId)))
            {
                LocIdOfStoredEvent = LocId;
                break;
            }
        }
   }

    return LocIdOfStoredEvent;
}

uint16_least Dem_EvMemGetEventMemoryLocIdOfEvent(Dem_EventIdType EventId, uint16_least MemId)
{
    return Dem_EvMemGetEventMemoryOrReaderCopyLocIdOfEvent(EventId, MemId, FALSE);
}

Std_ReturnType Dem_EvMemGetReaderCopyOfEvent(
        Dem_EvMemEventMemoryType* ReaderCopy
   ,     Dem_EventIdType EventId
   ,     uint16_least MemId
)
{
   uint16_least LocId;
    Std_ReturnType retval;

   if(ReaderCopy == NULL_PTR)
   {
        return E_NOT_OK;
   }

    Dem_EvMemReaderCopiesEnterLock();
   {

        LocId = Dem_EvMemGetEventMemoryOrReaderCopyLocIdOfEvent(EventId, MemId, TRUE);
        if(Dem_EvMemIsReaderCopyLocIdValid(LocId))
        {

            *ReaderCopy = Dem_EvMemEventMemory[LocId];
            retval = E_OK;
        }
        else{
            retval = E_NOT_OK;
        }
   }
    Dem_EvMemReaderCopiesExitLock();

    return retval;
}

void Dem_EvMemSetEventPassed(Dem_EventIdType EventId, uint16_least MemId, const uint8 *EnvData)
{
   uint16_least StatusOld;
   uint16_least StatusNew;
   uint16_least LocId;
   uint16_least WriteSts;

   if(!Dem_GetEvMemLockInternal())
   {
        DEM_EVMEM_USEVAR(EnvData);

        DEM_ASSERT(Dem_isEventIdValid(EventId), DEM_DET_APIID_EVMEMSETEVENTPASSED,0);
        DEM_ASSERT(Dem_EvMemIsMemIdValid(MemId), DEM_DET_APIID_EVMEMSETEVENTPASSED,2);

        if(!Dem_isDtcIdValid (Dem_DtcIdFromEventId (EventId)))
        {
            return;
        }

        WriteSts = DEM_EVMEM_WRITEMASK_NO;
        LocId = Dem_EvMemGetEventMemoryLocIdOfEvent (EventId, MemId);
        if(Dem_EvMemIsEventMemLocIdValid (LocId))
        {
            if(Dem_EvMemIsEventPassedAllowed (EventId, LocId))
            {

                StatusOld = Dem_EvMemGetEventMemStatus (LocId);
                StatusNew = StatusOld;

                if(Dem_EvMemIsTestFailedSLC(StatusOld))
                {

                    StatusNew = StatusNew & (uint16_least) ~((uint16_least) DEM_EVMEM_STSMASK_TESTFAILED);

                    if(((StatusOld & DEM_EVMEM_STSMASK_PENDING) != 0u) && ((StatusOld & DEM_EVMEM_STSMASK_TESTFAILED_TFC) == 0u))
                    {
                            StatusNew = StatusNew & (uint16_least)(~((uint16_least)(DEM_EVMEM_STSMASK_PENDING_NFC | DEM_EVMEM_STSMASK_PENDING_CONFIRMED)));
                    }

                    if(Dem_LibGetParamBool(DEM_CFG_EVMEM_TESTCOMPLETE_TFC_SUPPORTED))
                    {
                        StatusNew = StatusNew | DEM_EVMEM_STSMASK_TESTCOMPLETE_TFC;
                    }

   				if(Dem_LibGetParamBool(DEM_CFG_EVMEM_AGING_COUNTER_SUPPORTED))
   				{

                        if(Dem_EvtParam_GetAgingAllowed(EventId) && (Dem_EvtParam_GetAgingThreshold(EventId) == 0u))
   				    {

   				        Dem_EvMemForceClearEventMemoryLocation (LocId, DEM_EVMEM_WRITEMASK_CLEAR, DEM_EVMEM_ACTIONTYPE_IMMEDIATEAGING);
   				        StatusNew = Dem_EvMemGetEventMemStatus (LocId);

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
                            rba_DemObdBasic_EvMem_HandleImmediateAgeing(EventId);
#endif
                        }
                        else
                        {
                            Dem_EvMemSetAgingCounterOnEventPassed (EventId, LocId, &StatusNew, &WriteSts);
                        }
                    }

   				if(Dem_EvMemIsNvStatusChanged (EventId, StatusOld, StatusNew))
   				{
   					WriteSts = WriteSts | DEM_EVMEM_WRITEMASK_DATA;
   				}

   				if(Dem_LibGetParamBool (DEM_CFG_EVMEM_EXTENDED_DATA_SUPPORTED) && (Dem_LibGetParamBool(DEM_CFG_EVMEM_EXTENDED_DATA_ON_PASSED_SUPPORTED)))
   				{

                       Dem_EvMemUpdateEnvData(EventId,EnvData,LocId,Dem_EvMemGetTriggerOnPassed(StatusOld, StatusNew), &WriteSts, DEM_EVMEM_UPDATE_EXTDATA);
   				}

   				Dem_EvMemSetStatusWithNotifications(LocId,StatusNew,WriteSts,DEM_EVMEM_ACTIONTYPE_NONE);
   			}
   		}
   	}
   }
}

void Dem_EvMemSetEventUnRobust(Dem_EventIdType EventId, uint16_least MemId, const uint8 *EnvData)
{
   uint16_least LocId;
   uint16_least WriteSts;
   uint16_least StatusNew;
   uint16_least StatusOld;

   if(!Dem_GetEvMemLockInternal())
   {

        DEM_ASSERT(Dem_isEventIdValid(EventId), DEM_DET_APIID_EVMEMSETEVENTUNROBUST, 0);
        DEM_ASSERT(Dem_EvMemIsMemIdValid(MemId), DEM_DET_APIID_EVMEMSETEVENTUNROBUST, 1);

        if(!Dem_isDtcIdValid(Dem_DtcIdFromEventId(EventId)))
        {
            return;
        }

        WriteSts = DEM_EVMEM_WRITEMASK_NO;

        if(Dem_EvMemIsEventUnRobustAllowed(EventId, MemId))
        {
            LocId = Dem_EvMemGetEventMemoryStorageLocation(EventId, C_EVENTTYPE_UNROBUST, MemId, FALSE
   ,     DEM_CFG_EVMEM_MEMORY_DISPLACEMENT_STRATEGY);

            if(Dem_EvMemIsEventMemLocIdValid(LocId))
            {

                if(!Dem_EvMemIsStored(Dem_EvMemGetEventMemStatus(LocId)))
                {
                    DEM_EVMEM_CLEAROBJ(Dem_EvMemEventMemory[LocId]);

                }

                StatusOld = Dem_EvMemGetEventMemStatus(LocId);
                StatusNew = StatusOld;

                if((Dem_LibGetParamBool(DEM_CFG_EVMEM_EXTENDED_DATA_SUPPORTED) || Dem_LibGetParamBool(DEM_CFG_EVMEM_FREEZE_FRAME_SUPPORTED))
                        && Dem_LibGetParamBool(DEM_CFG_EVMEM_TRIGGER_ON_FDC_SUPPORTED))
                {
                    Dem_EvMemUpdateEnvData(EventId,EnvData,LocId,DEM_TRIGGER_ON_FDC_THRESHOLD, &WriteSts, DEM_EVMEM_UPDATE_EXTDATA_AND_FFDATA);
                }

#if(DEM_CFG_EVMEM_PROJECT_EXTENSION)
                {
                    Dem_EvMemProjectExtensionUnRobust(EventId, LocId, &WriteSts);
                }
#endif

                if(WriteSts != DEM_EVMEM_WRITEMASK_NO)
                {

                    if(!Dem_EvMemIsTestFailedSLC(Dem_EvMemGetEventMemStatus(LocId)))
                    {

                        Dem_EvMemSetEventMemEventId(LocId, EventId);

                        Dem_EvMemSetEventMemTimeId(LocId, Dem_EvMemGetNewEventMemoryTimeId(MemId));
                    }
                    StatusNew = StatusNew | DEM_EVMEM_STSMASK_STORED;

                    Dem_EvMemSetStatusWithNotifications(LocId, StatusNew, WriteSts, DEM_EVMEM_ACTIONTYPE_NONE);
                }
            }
        }
   }
}

#if(DEM_CFG_EVMEM_MIRROR_MEMORY_SUPPORTED)

#if(!DEM_CFG_EVMEM_USERDEF_MIRROR_MEM_STORAGE_STRATEGY)
uint16_least Dem_EvMemGetMirrorMemoryStorageLocation(Dem_EventIdType EventId, uint16_least MemId, Dem_boolean_least isDisplacementSupported, uint16_least displacementStrategy)
{
    return Dem_EvMemGetEventMemoryStorageLocation(EventId, C_EVENTTYPE_SET, MemId, isDisplacementSupported, displacementStrategy);
}
#endif

void Dem_EvMemCopyToMirrorMemory(uint16_least LocId)
{

   uint16_least    EventMemStatus;
   uint16_least    MirrorMemLocId;
    Dem_EventIdType EventId;
   uint32          TimeId;
   uint16_least WriteSts;

    DEM_ASSERT(Dem_EvMemIsMemIdValid(DEM_CFG_EVMEM_MEMID_MIRROR), DEM_DET_APIID_EVMEMCOPYTOMIRRORMEMORY,0);

   if(Dem_EvMemGetEventMemId(LocId) != DEM_CFG_EVMEM_MEMID_MIRROR)
   {
        EventMemStatus = Dem_EvMemGetEventMemStatus(LocId);
        if(Dem_EvMemIsStored(EventMemStatus))
        {
            EventId = Dem_EvMemGetEventMemEventId(LocId);
            MirrorMemLocId = Dem_EvMemGetMirrorMemoryStorageLocation(EventId, DEM_CFG_EVMEM_MEMID_MIRROR, TRUE, DEM_CFG_EVMEM_MIRROR_DISPLACEMENT_STRATEGY);
            if(Dem_EvMemIsEventMemLocIdValid(MirrorMemLocId))
            {

                TimeId = Dem_EvMemGetNewEventMemoryTimeId(DEM_CFG_EVMEM_MEMID_MIRROR);

                Dem_EvMemEventMemory[MirrorMemLocId] = Dem_EvMemEventMemory[LocId];

                if(Dem_LibGetParamBool(DEM_CFG_EVMEM_EXTENDED_DATA_SUPPORTED) && Dem_LibGetParamBool(DEM_CFG_EVMEM_EXTENDED_DATA_ON_MIRROR_SUPPORTED))
                {
                    WriteSts = DEM_EVMEM_WRITEMASK_NO;
                    Dem_EvMemUpdateEnvData(Dem_EvMemGetEventMemEventId(MirrorMemLocId),NULL_PTR,MirrorMemLocId,DEM_TRIGGER_ON_MIRROR, &WriteSts, DEM_EVMEM_UPDATE_EXTDATA);
                }

                Dem_EvMemSetEventMemTimeId (MirrorMemLocId, TimeId);

                if(Dem_LibGetParamBool(DEM_CFG_EVMEM_MIRROR_MEMORY_DTC_STATUS_STORED))
                {
                    Dem_EvMemSetEventMemDtcStatus(MirrorMemLocId, Dem_DtcStatusByteRetrieve(Dem_DtcIdFromEventId(EventId)));
                }

                Dem_EvMemEventMemoryWriteNotification(MirrorMemLocId, DEM_EVMEM_WRITEMASK_DATA);
            }
        }
   }
}
#endif

static void Dem_EvMemLocationStartFailureCycle(Dem_OperationCycleList operationCycleList, uint16_least LocId)
{
   uint16_least     StatusOld;
   uint16_least     StatusNew;
    Dem_EventIdType  EventId;
   uint16_least     WriteSts;
    Dem_EvMemActionType actionType = DEM_EVMEM_ACTIONTYPE_RESETPENDING;

    WriteSts = DEM_EVMEM_WRITEMASK_NO;
    StatusOld = Dem_EvMemGetEventMemStatus(LocId);
   if(Dem_EvMemIsStored(StatusOld))
   {
        EventId = Dem_EvMemGetEventMemEventId(LocId);
        if(Dem_isEventAffectedByFailureCycleList(EventId, operationCycleList))
        {
            StatusNew = StatusOld;

            Dem_EvtSetNextReportRelevantForMemories(Dem_EvMemGetEventMemEventId (LocId), TRUE);

            StatusNew = StatusNew & (uint16_least) (~((uint16_least) DEM_EVMEM_STSMASK_PENDING));
            if((StatusOld & DEM_EVMEM_STSMASK_PENDING_NFC) != 0u)
            {
                StatusNew = StatusNew | DEM_EVMEM_STSMASK_PENDING;
                actionType = DEM_EVMEM_ACTIONTYPE_NONE;
            }

            StatusNew = StatusNew & (uint16_least) (~((uint16_least) DEM_EVMEM_STSMASK_TESTFAILED_TFC));

            if(
                ((StatusNew & (DEM_EVMEM_STSMASK_PENDING | DEM_EVMEM_STSMASK_CONFIRMED | DEM_EVMEM_STSMASK_TESTFAILED_SLC)) == DEM_EVMEM_STSMASK_TESTFAILED_SLC)
#if(DEM_CFG_TFSLC_RESET_AFTER_AGING_AND_DISPLACEMENT)
            && (Dem_EvMemGetEventMemAgingCounterForTFSLC(LocId) == Dem_EvtParam_GetAgingThresholdForTFSLC(EventId))
#endif
            )
            {
                Dem_EvMemForceClearEventMemoryLocation(LocId, DEM_EVMEM_WRITEMASK_CLEAR, actionType);
                return;
            }

            if(Dem_LibGetParamBool(DEM_CFG_EVMEM_TESTCOMPLETE_TFC_SUPPORTED))
            {
                StatusNew &= (uint16_least) (~((uint16_least) DEM_EVMEM_STSMASK_TESTCOMPLETE_TFC));
            }

            if(Dem_EvMemIsNvStatusChanged(EventId, StatusOld, StatusNew))
            {
                WriteSts = WriteSts | DEM_EVMEM_WRITEMASK_DATA;
            }

            Dem_EvMemSetStatusWithNotifications(LocId, StatusNew, WriteSts, actionType);
        }
   }
}

static void Dem_EvMemLocationStartAgingCycle(Dem_OperationCycleList operationCycleList, uint16_least LocId)
{

   uint16_least StatusOld;
   uint16_least StatusNew;
    Dem_EventIdType EventId;
   uint16_least WriteSts;
    Dem_boolean_least IsCleared;
    Dem_EvMemActionType actiontype;

   if(Dem_LibGetParamBool (DEM_CFG_EVMEM_AGING_COUNTER_SUPPORTED))
   {
        WriteSts = DEM_EVMEM_WRITEMASK_NO;
        IsCleared = FALSE;
        StatusOld = Dem_EvMemGetEventMemStatus (LocId);
        actiontype = DEM_EVMEM_ACTIONTYPE_NONE;
        if(Dem_EvMemIsStored (StatusOld))
        {
            EventId = Dem_EvMemGetEventMemEventId (LocId);

            if(Dem_isEventAffectedByAgingCycleList (EventId, operationCycleList))
            {

                Dem_EvtSetNextReportRelevantForMemories(Dem_EvMemGetEventMemEventId (LocId), TRUE);

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
                if(rba_DemObdBasic_EvMem_IsAgingOfLocationAllowed(LocId))
#endif
                {

                    if(Dem_EvMemIsAgingCalculationAllowed(StatusOld) &&
                            ( ! Dem_LibGetParamBool(DEM_CFG_SUPPORT_AGINGCNTR_ONLY_WHEN_AGING_ALLOWED) || Dem_EvtParam_GetAgingAllowed(EventId) ) )
                    {
                        StatusNew = StatusOld;

                        Dem_EvMemSetAgingCounterOnAgingCycle (EventId, LocId, &StatusNew, &WriteSts);

                        if(Dem_EvMemIsAged (EventId, LocId, StatusNew))
                        {
                            if(Dem_EvtParam_GetAgingAllowed (EventId))
                            {
                                Dem_EvMemForceClearEventMemoryLocation (LocId, DEM_EVMEM_WRITEMASK_CLEAR, DEM_EVMEM_ACTIONTYPE_AGING);
                                IsCleared = TRUE;
                            }
                        }

                        if(!IsCleared)
                        {
#if(DEM_CFG_TFSLC_RESET_AFTER_AGING_AND_DISPLACEMENT)
                            if(Dem_EvtParam_GetAgingAllowed (EventId))
                            {

                                if((Dem_EvMemGetEventMemAgingCounter(LocId) >= Dem_EvtParam_GetAgingThreshold(EventId)) && (Dem_EvtParam_GetAgingThreshold(EventId) != 0u))
                                {
                                    StatusNew = StatusNew & (uint16_least)(~DEM_EVMEM_STSMASK_CONFIRMED);
                                    actiontype = DEM_EVMEM_ACTIONTYPE_AGINGOFCONFIRMED;
                                }
                            }
#endif
                            if(Dem_EvMemIsNvStatusChanged (EventId, StatusOld, StatusNew))
                            {
                                WriteSts = WriteSts | DEM_EVMEM_WRITEMASK_DATA;
                            }

                            Dem_EvMemSetStatusWithNotifications(LocId,StatusNew,WriteSts,actiontype);
                        }
                    }
                }
            }
        }
   }
}

static void Dem_EvMemLocationStartOperationCycle (Dem_OperationCycleList operationCycleList, uint16_least LocId)
{
    Dem_EventIdType EventId;
   uint16_least WriteSts = DEM_EVMEM_WRITEMASK_NO;
   uint16_least Status;

    Status = Dem_EvMemGetEventMemStatus (LocId);

   if(Dem_EvMemIsStored (Status))
   {
        EventId = Dem_EvMemGetEventMemEventId (LocId);
        if(Dem_isEventAffectedByOperationCycleList (EventId, operationCycleList))
        {
            if((Status & DEM_EVMEM_STSMASK_TESTFAILED_SLC) == DEM_EVMEM_STSMASK_TESTFAILED_SLC)
            {
                if( Dem_LibGetParamBool(DEM_CFG_READDEM_CYCLES_SINCE_FIRST_FAILED_SUPPORTED) )
                {
                    Dem_EvMemIncCyclesSinceFirstFailed(LocId);
                    WriteSts = WriteSts | DEM_EVMEM_WRITEMASK_DATA;
                }
                if( Dem_LibGetParamBool(DEM_CFG_READDEM_CYCLES_SINCE_LAST_FAILED_SUPPORTED) )
                {
                    Dem_EvMemIncCyclesSinceLastFailed(LocId);
                    WriteSts = WriteSts | DEM_EVMEM_WRITEMASK_DATA;
                }
                if( Dem_LibGetParamBool(DEM_CFG_READDEM_CYCLES_SINCE_LAST_FAILED_EXCLUDING_TNC_SUPPORTED) && Dem_EvtSt_GetTestCompleteTOC(EventId))
                {
                    Dem_EvMemIncCyclesSinceLastFailedExcludingTNC(LocId);
                    WriteSts = WriteSts | DEM_EVMEM_WRITEMASK_DATA;
                }
            }
            if( Dem_LibGetParamBool(DEM_CFG_READDEM_MAX_FDC_DURING_CURRENT_CYCLE_SUPPORTED) )
            {
                Dem_EvMemSetMaxFdcDuringCurrentCycle(LocId, 0);
                WriteSts = WriteSts | DEM_EVMEM_WRITEMASK_DATA;
            }
#if(DEM_CFG_EVMEM_PROJECT_EXTENSION)
            {
                Dem_EvMemProjectExtensionStartOpCycle(LocId, &WriteSts);
            }
#endif
        }
   }

   if(WriteSts != DEM_EVMEM_WRITEMASK_NO)
   {

        Dem_EvMemEventMemoryWriteNotification (LocId, WriteSts);
   }
}

void Dem_EvMemStartOperationCycle(Dem_OperationCycleList operationCycleList, uint16_least MemId)
{
   uint16_least LocId;
   if(!Dem_GetEvMemLockInternal())
   {

        DEM_ASSERT(Dem_EvMemIsMemIdValid(MemId),DEM_DET_APIID_EVMEMSTARTOPERATIONCYCLE,0);

        for(Dem_EvMemEventMemoryLocIteratorNew    (&LocId, MemId);
                Dem_EvMemEventMemoryLocIteratorIsValid(&LocId, MemId);
                Dem_EvMemEventMemoryLocIteratorNext   (&LocId, MemId))
        {
            Dem_EvMemLocationStartFailureCycle (operationCycleList, LocId);
            Dem_EvMemLocationStartAgingCycle (operationCycleList, LocId);
            Dem_EvMemLocationStartOperationCycle (operationCycleList, LocId);
        }
   }
}

uint16_least Dem_EvMemGetEventMemoryStatusOfDtc(Dem_DtcIdType DtcId, uint16_least MemId)
{
   uint16_least LocId;
   uint16_least Status;

    DEM_ASSERT(Dem_EvMemIsMemIdValid(MemId),DEM_DET_APIID_EVMEMGETEVENTMEMORYSTATUSOFDTC,0);

    Status = 0;
   for(Dem_EvMemEventMemoryLocIteratorNew    (&LocId, MemId);
            Dem_EvMemEventMemoryLocIteratorIsValid(&LocId, MemId);
            Dem_EvMemEventMemoryLocIteratorNext   (&LocId, MemId))
   {
        if(Dem_EvMemIsStored(Dem_EvMemGetEventMemStatus(LocId)))
        {
            if(DtcId == Dem_DtcIdFromEventId(Dem_EvMemGetEventMemEventId(LocId)))
            {
                Status = Status | Dem_EvMemGetEventMemStatus(LocId);
                if(Dem_LibGetParamUI8(DEM_CFG_EVCOMB) != Dem_LibGetParamUI8(DEM_CFG_EVCOMB_ONRETRIEVAL))
                {
                    break;
                }
            }
        }
   }

    return Status & (DEM_EVMEM_STSMASK_PENDING | DEM_EVMEM_STSMASK_CONFIRMED);
}

uint16_least Dem_EvMemGetEventMemoryStatusOfEvent(Dem_EventIdType EventId, uint16_least MemId)
{
   uint16_least LocId;
   uint16_least Status;

    DEM_ASSERT(Dem_EvMemIsMemIdValid(MemId),DEM_DET_APIID_EVMEMGETEVENTMEMORYSTATUSOFEVENT,0);

    LocId = Dem_EvMemGetEventMemoryLocIdOfEvent(EventId, MemId);
   if(Dem_EvMemIsEventMemLocIdValid(LocId))
   {
        Status = Dem_EvMemGetEventMemStatus(LocId) & (DEM_EVMEM_STSMASK_PENDING | DEM_EVMEM_STSMASK_CONFIRMED);
   }
   else{
        Status = 0;
   }

    return Status;
}

static uint16_least Dem_EvMemGetPrioOfLocation(uint16_least LocId)
{
   uint16_least      Status;

    Status = Dem_EvMemGetEventMemStatus(LocId);
   if((Status & DEM_EVMEM_STSMASK_CONFIRMED) != 0u)
   {
        return 2;
   }
   if((Status & DEM_EVMEM_STSMASK_TESTFAILED_SLC) != 0u)
   {
        return 1;
   }

    return 0;
}

uint16_least Dem_EvMemGetEventMemoryLocIdOfDtcWithVisibility(Dem_DtcIdType DtcId, uint16_least MemId, Dem_boolean_least ShadowEntriesVisible)
{
   uint32            TimeId;
   uint32            SearchTimeId;
   uint16_least      LocId;
   uint16_least      SearchLocId;
   uint16_least      Prio;
   uint16_least      SearchPrio;

    DEM_ASSERT(Dem_EvMemIsMemIdValid(MemId),DEM_DET_APIID_EVMEMGETEVENTMEMORYSTATUSOFDTC,0);
    DEM_ASSERT(Dem_isDtcIdValid(DtcId),DEM_DET_APIID_EVMEMGETEVENTMEMORYSTATUSOFDTC,1);

    SearchPrio     = 0;
    SearchLocId    = DEM_EVMEM_INVALID_LOCID;

    SearchTimeId   = DEM_EVMEM_MAX_TIMEID;
   if(Dem_LibGetParamUI8(DEM_CFG_EVMEM_EVENTSEARCH1) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_EVENTSEARCH1_MOSTRECENT))
   {
        SearchTimeId = 0;
   }

   for(Dem_EvMemEventMemoryLocIteratorNew     (&LocId, MemId);
            Dem_EvMemEventMemoryLocIteratorIsValid(&LocId, MemId);
            Dem_EvMemEventMemoryLocIteratorNext   (&LocId, MemId))
   {
        if( Dem_EvMemIsVisible(Dem_EvMemGetEventMemStatus(LocId), ShadowEntriesVisible))
        {
            if(DtcId ==  Dem_DtcIdFromEventId(Dem_EvMemGetEventMemEventId(LocId)))
            {
                Prio      = Dem_EvMemGetPrioOfLocation(LocId);
                TimeId    = Dem_EvMemGetEventMemTimeId(LocId);

                if( (Prio >  SearchPrio) || ( (Prio == SearchPrio) &&
                   ( ((TimeId >= SearchTimeId) && (Dem_LibGetParamUI8(DEM_CFG_EVMEM_EVENTSEARCH1) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_EVENTSEARCH1_MOSTRECENT))) ||
                     ((TimeId <= SearchTimeId) && (Dem_LibGetParamUI8(DEM_CFG_EVMEM_EVENTSEARCH1) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_EVENTSEARCH1_FIRST))) ) ) )
                {
                    SearchLocId       = LocId;
                    SearchTimeId      = TimeId;
                    SearchPrio        = Prio;
                    if(Dem_LibGetParamUI8(DEM_CFG_EVCOMB) != Dem_LibGetParamUI8(DEM_CFG_EVCOMB_ONRETRIEVAL))
                    {
                        break;
                    }
                }
            }
        }
   }
    return(SearchLocId);
}

#if DEM_CFG_EVMEM_SHADOW_MEMORY_SUPPORTED

void Dem_EvMemClearShadowMemory(Dem_EventIdType EventId, uint16_least MemId)
{
   uint16_least LocId;

    DEM_ASSERT(Dem_EvMemIsMemIdValid(MemId), DEM_DET_APIID_EVMEMCLEARSHADOWMEMORY,0);

    LocId = Dem_EvMemGetEventMemoryLocIdOfEvent (EventId, MemId);
   if(Dem_EvMemIsDeleted(Dem_EvMemGetEventMemStatus(LocId)))
   {
        DEM_EVMEM_CLEAROBJ(Dem_EvMemEventMemory[LocId]);

        Dem_EvMemEventMemoryWriteNotification(LocId, DEM_EVMEM_WRITEMASK_CLEAR);

   }
}

uint16_least Dem_EvMemGetShadowMemoryLocIdOfDtc(Dem_DtcIdType DtcId, uint16_least MemId)
{
   uint32            TimeId;
   uint32            SearchTimeId;
   uint16_least      LocId;
   uint16_least      SearchLocId;
   uint16_least      Confirmed;
   uint16_least      SearchConfirmed;

    DEM_ASSERT(Dem_EvMemIsMemIdValid(MemId), DEM_DET_APIID_EVMEMGETSHADOWMEMORYLOCIDOFDTC,0);
    DEM_ASSERT(Dem_isDtcIdValid(DtcId), DEM_DET_APIID_EVMEMGETSHADOWMEMORYLOCIDOFDTC,1);

    SearchConfirmed   = 0;
    SearchLocId       = DEM_EVMEM_INVALID_LOCID;

    SearchTimeId      = DEM_EVMEM_MAX_TIMEID;
   if(Dem_LibGetParamUI8(DEM_CFG_EVMEM_EVENTSEARCH1) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_EVENTSEARCH1_MOSTRECENT))
   {
        SearchTimeId = 0;
   }

   for(Dem_EvMemEventMemoryLocIteratorNew    (&LocId, MemId);
            Dem_EvMemEventMemoryLocIteratorIsValid(&LocId, MemId);
            Dem_EvMemEventMemoryLocIteratorNext   (&LocId, MemId))
   {
        if(Dem_EvMemIsDeleted(Dem_EvMemGetEventMemStatus(LocId)))
        {
            if(DtcId ==  Dem_DtcIdFromEventId(Dem_EvMemGetEventMemEventId(LocId)))
            {
                Confirmed = Dem_EvMemGetEventMemStatus(LocId) & DEM_EVMEM_STSMASK_CONFIRMED;
                if(Dem_LibGetParamBool(DEM_CFG_EVMEM_SHADOW_ENTRIES_TIMEID_SUPPORTED))
                {
                    TimeId =  Dem_EvMemGetEventMemTimeId(LocId);
                }
                else{
                    TimeId = 0;
                }

                if( (Confirmed >  SearchConfirmed) || ( (Confirmed == SearchConfirmed) &&
                   ( ((TimeId >= SearchTimeId) && (Dem_LibGetParamUI8(DEM_CFG_EVMEM_EVENTSEARCH1) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_EVENTSEARCH1_MOSTRECENT))) ||
                     ((TimeId <= SearchTimeId) && (Dem_LibGetParamUI8(DEM_CFG_EVMEM_EVENTSEARCH1) == Dem_LibGetParamUI8(DEM_CFG_EVMEM_EVENTSEARCH1_FIRST))) ) ) )
                {
                    SearchLocId       = LocId;
                    SearchTimeId      = TimeId;
                    SearchConfirmed   = Confirmed;
                    if(Dem_LibGetParamUI8(DEM_CFG_EVCOMB) != Dem_LibGetParamUI8(DEM_CFG_EVCOMB_ONRETRIEVAL))
                    {
                        break;
                    }
                }
            }
        }
   }
    return(SearchLocId);
}
#endif

Dem_NvmBlockIdType Dem_EvMemGetNvmIdFromLocId(uint16_least LocId)
{

    DEM_ASSERT(Dem_EvMemIsEventMemLocIdValid(LocId),DEM_DET_APIID_EVMEMGETNVMIDFROMLOCID,0);

    return Dem_EvMemNvmId[LocId];
}

static void Dem_EvMemNvMReadEventMemoryInit(uint16_least LocId)
{
   uint16_least Status;
    Dem_NvmResultType NvmResult;
    Dem_EventIdType EventId;

    DEM_ASSERT(Dem_EvMemIsEventMemLocIdValid(LocId),DEM_DET_APIID_EVMEMNVMREADEVENTMEMORYINIT,0);

   if(Dem_NvMIsInvalidateAllNVMBlocksRequested())
   {
        DEM_EVMEM_CLEAROBJ(Dem_EvMemEventMemory[LocId]);
        Dem_NvMClearBlockByInvalidate(Dem_EvMemGetNvmIdFromLocId (LocId));
   }
   else{

        NvmResult = Dem_NvmGetStatus (Dem_EvMemGetNvmIdFromLocId (LocId));

        if(NvmResult == DEM_NVM_INVALID)
        {
            DEM_EVMEM_CLEAROBJ(Dem_EvMemEventMemory[LocId]);
        }

        if(NvmResult == DEM_NVM_SUCCESS)
        {
            Status = Dem_EvMemGetEventMemStatus (LocId);

            if((Status & (DEM_EVMEM_STSMASK_STORED | DEM_EVMEM_STSMASK_DELETED)) == (DEM_EVMEM_STSMASK_STORED | DEM_EVMEM_STSMASK_DELETED))
            {
                NvmResult = DEM_NVM_FAILED;
            }
            else{
                if(!Dem_EvMemIsEmpty (Status))
                {
                    EventId = Dem_EvMemGetEventMemEventId (LocId);

                    if(!Dem_isEventIdValid (EventId))
                    {
                        NvmResult = DEM_NVM_FAILED;
                    }

                    else
                    {
                        if(!Dem_isDtcIdValid (Dem_DtcIdFromEventId (EventId)))
                        {
                            NvmResult = DEM_NVM_FAILED;
                        }
                    }
                }
            }
        }

        if((NvmResult != DEM_NVM_SUCCESS) && (NvmResult != DEM_NVM_INVALID))
        {
            DEM_EVMEM_CLEAROBJ(Dem_EvMemEventMemory[LocId]);

            Dem_EvMemEventMemoryWriteNotification (LocId, DEM_EVMEM_WRITEMASK_CLEAR);
        }
   }

    Dem_EvMemSetEventMemStatus(LocId, Dem_EvMemGetEventMemStatus(LocId) & (~DEM_EVMEM_STSMASK_READER_COPY_CURRENT));
}

void Dem_EvMemInit(void){

   uint16_least Status;
   uint16_least LocId;

    Dem_EventIdIterator eventIt;

   for(Dem_EventIdIteratorNew     (&eventIt);
            Dem_EventIdIteratorIsValid (&eventIt);
            Dem_EventIdIteratorNext    (&eventIt))
   {
        Dem_EvtSt_SetPendingDTC(Dem_EventIdIteratorCurrent(&eventIt), FALSE);

        if(Dem_LibGetParamBool (DEM_CFG_EVMEM_RESET_CONFIRMED_BIT_ON_OVERFLOW))
        {
            Dem_EvtSt_SetConfirmedDTC(Dem_EventIdIteratorCurrent(&eventIt), FALSE);
#if(DEM_CFG_TFSLC_RESET_AFTER_AGING_AND_DISPLACEMENT)
            if(Dem_EvtParam_GetAgingThresholdForTFSLC(Dem_EventIdIteratorCurrent(&eventIt)) > 0)
            {
                Dem_EvtSt_SetTestFailedSLC(Dem_EventIdIteratorCurrent(&eventIt), FALSE);
            }
#endif
        }
   }

   for(Dem_EvMemEventMemoryAllLocIteratorNew    (&LocId);
        Dem_EvMemEventMemoryAllLocIteratorIsValid(&LocId);
        Dem_EvMemEventMemoryAllLocIteratorNext   (&LocId))
   {
       Dem_EvMemNvMReadEventMemoryInit (LocId);
       Status = Dem_EvMemGetEventMemStatus (LocId);
       if(Dem_EvMemIsStored (Status))
       {
           Status = Status & (~Dem_EvMemGetRamStsMask(Dem_EvMemGetEventMemEventId(LocId)));

           Dem_EvMemSetStatusWithNotifications(LocId,Status,DEM_EVMEM_WRITEMASK_NO,DEM_EVMEM_ACTIONTYPE_NONE);

           Dem_StatusByteConsistencyCheck(LocId, Status);
       }
   }

   Dem_EvMemGenInitEventMemoryGen();

   //Consistency check for the LastFailedDTC and LastConfirmedDTC in the Event memory
   Dem_ConsistencyCheckForDTC();
#if(DEM_CFG_EVMEM_PROJECT_EXTENSION)
   {
       Dem_EvMemProjectExtensionInit();
   }
#endif

   Dem_EvMemReaderCopiesUpdate();
}

void Dem_EvMemInitCausality(void){
   uint16_least Status;
   uint16_least LocId;

    DEM_ENTERLOCK_MON();

   for(Dem_EvMemEventMemoryAllLocIteratorNew    (&LocId);
            Dem_EvMemEventMemoryAllLocIteratorIsValid(&LocId);
            Dem_EvMemEventMemoryAllLocIteratorNext   (&LocId))
   {
        if(!Dem_EvMemIsOriginMirror(LocId))
        {
            Status = Dem_EvMemGetEventMemStatus (LocId);
            if(Dem_EvMemIsStored (Status) && !Dem_EvMemIsDeleted(Status) && Dem_EvMemIsTestFailedSLC(Status))
            {
                Dem_EventIdType evtId = Dem_EvMemGetEventMemEventId (LocId);
                if(Dem_isEventIdValid(evtId))
                {
                    if(Dem_EvtSt_GetTestFailed(evtId)){
                        Dem_EvtSetCausal(evtId, TRUE);
                    }
                }
            }
        }
   }

    DEM_EXITLOCK_MON();
}

void Dem_EvMemMainFunction(void){
    Dem_EvMemProcessPassedEvents();
    Dem_EvMemApiMainFunction();
    Dem_EvMemFdcUpdate();
#if(DEM_CFG_EVMEM_PROJECT_EXTENSION)
   {
        Dem_EvMemProjectExtensionMain();
   }
#endif
    Dem_EvMemReaderCopiesUpdate();
}

Std_ReturnType Dem_LockEventMemory (boolean Lock)
{
    Dem_EvMemIsLocked = Lock;
    return E_OK;
}

boolean Dem_GetEvMemLock(void){
    return Dem_GetEvMemLockInternal();
}

#if(DEM_CFG_READDEM_MAX_FDC_DURING_CURRENT_CYCLE_SUPPORTED || DEM_CFG_READDEM_MAX_FDC_SINCE_LAST_CLEAR_SUPPORTED)

void Dem_EvMemFdcUpdate (void){
   uint16_least Status;
   uint16_least LocId;
   sint8 fdc;
    Dem_EventIdType eventId;
   uint16_least WriteSts;

   for(Dem_EvMemEventMemoryAllLocIteratorNew    (&LocId);
            Dem_EvMemEventMemoryAllLocIteratorIsValid(&LocId);
            Dem_EvMemEventMemoryAllLocIteratorNext   (&LocId))
   {
        Status = Dem_EvMemGetEventMemStatus (LocId);
        if(Dem_EvMemIsStored (Status)
                && (Dem_EvMemIsOriginPrimary(LocId) || Dem_EvMemIsOriginSecondary(LocId) ) )
        {
            if((Dem_EvMemGetMaxFdcDuringCurrentCycle(LocId) < 127) ||
                    (Dem_EvMemGetMaxFdcSinceLastClear(LocId) < 127))
            {
                WriteSts = DEM_EVMEM_WRITEMASK_NO;
                eventId = Dem_EvMemGetEventMemEventId(LocId);
                fdc = Dem_DtcFaultDetectionRetrieve(Dem_DtcIdFromEventId(eventId));

                if(DEM_CFG_READDEM_MAX_FDC_DURING_CURRENT_CYCLE_SUPPORTED
                        && (Dem_EvMemGetMaxFdcDuringCurrentCycle(LocId) < fdc))
                {
                    Dem_EvMemSetMaxFdcDuringCurrentCycle(LocId,  fdc);
                    WriteSts = WriteSts | DEM_EVMEM_WRITEMASK_DATA;
                }
                if(DEM_CFG_READDEM_MAX_FDC_SINCE_LAST_CLEAR_SUPPORTED
                        && (Dem_EvMemGetMaxFdcSinceLastClear(LocId) < fdc))
                {
                    Dem_EvMemSetMaxFdcSinceLastClear(LocId, fdc);
                    WriteSts = WriteSts | DEM_EVMEM_WRITEMASK_DATA;
                }

                if(WriteSts != DEM_EVMEM_WRITEMASK_NO)
                {

                    Dem_EvMemSetEventMemStatus(LocId, Dem_EvMemGetEventMemStatus(LocId) & (~DEM_EVMEM_STSMASK_READER_COPY_CURRENT));
                    Dem_NvMWriteBlockOnShutdown(Dem_EvMemGetNvmIdFromLocId (LocId));
                }
            }
        }
   }
}

#endif

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

