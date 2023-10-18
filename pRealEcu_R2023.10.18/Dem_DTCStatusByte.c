#include "Std_Types.hpp"

#include "Dem_Dcm.hpp"
#include "Dem_DTCStatusByte.hpp"
#include "Dem_Cfg_DTCs.hpp"
#include "Dem_Cfg_DTC_DataStructures.hpp"
#include "Dem_DTCs.hpp"
#include "Dem_Events.hpp"
#include "Dem_EventRecheck.hpp"
#include "Dem_Main.hpp"
#include "Dem_EvMem.hpp"
#include "Dem_EventStatus.hpp"
#include "Dem_Deb.hpp"
#include "Dem_DTCFilter.hpp"
#include "Dem_Dependencies.hpp"
#include "Dem_Lib.hpp"
#include "Dem_Mapping.hpp"
#include "Dem_EvBuff.hpp"

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"
static Dem_EventIdType Dem_PendingClearEventId;
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

uint8 Dem_DtcStatusByteRetrieve (Dem_DtcIdType dtcId)
{
   Dem_EventIdListIterator eventIt;
   Dem_EventIdType eventId;
   uint8 isobyte_OR = 0,  isoByte = DEM_ISO14229BYTE_INITVALUE;
   Dem_boolean_least isEventAssigned = FALSE;

   if(Dem_DtcIsSupported(dtcId))
   {
   	for(Dem_EventIdListIteratorNewFromDtcId(&eventIt, dtcId);
   			Dem_EventIdListIteratorIsValid(&eventIt);
   			Dem_EventIdListIteratorNext(&eventIt))
   	{
   		eventId = Dem_EventIdListIteratorCurrent(&eventIt);

   		if(!Dem_EvtIsSuppressed(eventId))
   		{
   			//isoByte_AND &= Dem_EvtGetIsoByte(eventId);
   			isobyte_OR  |= Dem_EvtGetIsoByte4DtcCalculation(eventId);
   			isEventAssigned = TRUE;
   		}
   	}
   	if(isEventAssigned) {
   		isoByte = (isobyte_OR );

#if DEM_CFG_EVCOMB != DEM_CFG_EVCOMB_DISABLED
   		if(Dem_ISO14229ByteIsTestFailedTOC(isoByte))
   		{
   			Dem_ISO14229ByteSetTestCompleteTOC(&isoByte, TRUE);
   		}
   		if(Dem_ISO14229ByteIsTestFailedSLC(isoByte))
   		{
   			Dem_ISO14229ByteSetTestCompleteSLC(&isoByte, TRUE);
   		}
#endif

   	}
   }

   return isoByte;
}

uint8 Dem_DtcStatusByteRetrieveWithOrigin (Dem_DtcIdType dtcId, Dem_DTCOriginType DtcOrigin, boolean* DtcStatusIsValid)
{
   uint16_least  LocId;

   *DtcStatusIsValid = TRUE;
   if( Dem_LibGetParamBool(DEM_CFG_EVMEM_MIRROR_MEMORY_DTC_STATUS_STORED) )
   {
   	if(DtcOrigin == DEM_DTC_ORIGIN_MIRROR_MEMORY)
   	{
   		LocId = Dem_EvMemGetMemoryLocIdOfDtcAndOrigin(dtcId, DtcOrigin);
   		if(Dem_EvMemIsEventMemLocIdValid(LocId))
   		{
   			return Dem_EvMemGetEventMemDtcStatus(LocId);
   		}
   		else
   		{
   			*DtcStatusIsValid = FALSE;
   			return 0;
   		}
   	}
   }

   return Dem_DtcStatusByteRetrieve(dtcId);
}

void Dem_ClearDTCsEvents(Dem_EventIdType EventId, Dem_DTCOriginType DTCOrigin, Dem_ClientClearMachineType *Dem_ClientClearMachinePtr)
{
   if(Dem_EvtClearEventAllowed(EventId))
   {
        if((Dem_EventUsesOrigin(EventId, DTCOrigin))
                || (!Dem_EventIdIsDtcAssigned(EventId) && (DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY)))
        {
            if(Dem_ClientClearMachinePtr->NumberOfEventsProcessed < DEM_CFG_CLEAR_MAX_NO_OF_EVENTS_PER_CYCLE)
            {
                Dem_ClientClearMachinePtr->NumberOfEventsProcessed++;

                Dem_PendingClearEventId = EventId;

                Dem_EvBuffClear(EventId);

                Dem_EvMemClearEventAndOrigin(EventId, DTCOrigin);
                Dem_ClearEvent(EventId, TRUE);
                Dem_PendingClearEventId = DEM_EVENTID_INVALID;
            }
            else{
                Dem_ClientClearMachinePtr->IsClearInterrupted = TRUE;
            }
        }
   }
   else if(Dem_EvtParam_GetClearAllowedBehavior(EventId) == DEM_ONLY_THIS_CYCLE_AND_READINESS)
   {
        Dem_ClearEvent(EventId, FALSE);
   }
   else{

   }
}
void Dem_ClearAllDTCs(Dem_DTCOriginType DTCOrigin, Dem_ClientClearMachineType *Dem_ClientClearMachinePtr)
{
    Dem_EventIdType eventId;

   if(Dem_ClientClearMachinePtr->IsNewClearRequest)
   {
        Dem_EventIdIteratorNew(&(Dem_ClientClearMachinePtr->EvtIt));
   }

   if(DTCOrigin != DEM_DTC_ORIGIN_MIRROR_MEMORY)
   {
        while(Dem_EventIdIteratorIsValid(&(Dem_ClientClearMachinePtr->EvtIt)))
        {
            eventId = Dem_EventIdIteratorCurrent(&(Dem_ClientClearMachinePtr->EvtIt));
            Dem_ClearDTCsEvents(eventId, DTCOrigin, Dem_ClientClearMachinePtr);
            if(!Dem_ClientClearMachinePtr->IsClearInterrupted)
            {
                Dem_EventIdIteratorNext(&(Dem_ClientClearMachinePtr->EvtIt));
            }
            else{
                return;
            }
        }
        Dem_NvMClearBlockByWrite(DEM_NVM_ID_EVT_STATUSBYTE);
#if(DEM_CFG_EVT_INDICATOR == DEM_CFG_EVT_INDICATOR_ON)
        Dem_NvMClearBlockByWrite(DEM_NVM_ID_INDICATOR_ATTRIBUTES);
#endif
        Dem_NodeRecheckOnClear();
   }
   else{
        while(Dem_EventIdIteratorIsValid(&(Dem_ClientClearMachinePtr->EvtIt)))
        {
            eventId = Dem_EventIdIteratorCurrent(&(Dem_ClientClearMachinePtr->EvtIt));
            Dem_EvMemClearEventAndOrigin(eventId, DTCOrigin);
            Dem_EventIdIteratorNext(&(Dem_ClientClearMachinePtr->EvtIt));
        }
   }
}

void Dem_ClearSingleDTC(Dem_DtcIdType dtcId, Dem_DTCOriginType DTCOrigin, Dem_ClientClearMachineType *Dem_ClientClearMachinePtr)
{
    Dem_EventIdType eventId;

   if((Dem_ClientClearMachinePtr->IsNewClearRequest) || (!Dem_EventIdListIteratorIsValid(&(Dem_ClientClearMachinePtr->EvtListIt))))
   {
        Dem_EventIdListIteratorNewFromDtcId(&(Dem_ClientClearMachinePtr->EvtListIt), dtcId);
   }

   if(DTCOrigin != DEM_DTC_ORIGIN_MIRROR_MEMORY)
   {
        while(Dem_EventIdListIteratorIsValid(&(Dem_ClientClearMachinePtr->EvtListIt)))
        {
            eventId = Dem_EventIdListIteratorCurrent(&(Dem_ClientClearMachinePtr->EvtListIt));
            Dem_ClearDTCsEvents(eventId, DTCOrigin, Dem_ClientClearMachinePtr);
            if(!Dem_ClientClearMachinePtr->IsClearInterrupted)
            {
                Dem_EventIdListIteratorNext(&(Dem_ClientClearMachinePtr->EvtListIt));
            }
            else{
                return;
            }
        }
        Dem_NvMClearBlockByWrite(DEM_NVM_ID_EVT_STATUSBYTE);
#if(DEM_CFG_EVT_INDICATOR == DEM_CFG_EVT_INDICATOR_ON)
        Dem_NvMClearBlockByWrite(DEM_NVM_ID_INDICATOR_ATTRIBUTES);
#endif
        Dem_NodeRecheckOnClear();
   }
   else{
        while(Dem_EventIdListIteratorIsValid(&(Dem_ClientClearMachinePtr->EvtListIt)))
        {
            eventId = Dem_EventIdListIteratorCurrent(&(Dem_ClientClearMachinePtr->EvtListIt));
            Dem_EvMemClearEventAndOrigin(eventId, DTCOrigin);
            Dem_EventIdListIteratorNext(&(Dem_ClientClearMachinePtr->EvtListIt));
        }
   }
}

boolean Dem_IsPendingClearEvent(Dem_EventIdType EventId)
{
    return (EventId == Dem_PendingClearEventId);
}

Dem_ReturnGetStatusOfDTCType Dem_GetStatusOfDTC(uint32 DTC
   ,  Dem_DTCKindType DTCKind
   ,  Dem_DTCOriginType DTCOrigin
   ,  uint8* DTCStatus)
{
   boolean DtcStatusIsValid;

   Dem_DtcIdType dtcId = Dem_DtcIdFromDtcCode (DTC);

   if(!Dem_DtcIsSupported(dtcId))
   {
   	return DEM_STATUS_WRONG_DTC;
   }

   if(!Dem_EvMemIsDtcOriginValid (&DTCOrigin))
   {
        return DEM_STATUS_WRONG_DTCORIGIN;
   }

   if(!Dem_DtcUsesOrigin(dtcId,DTCOrigin))
   {
   	return DEM_STATUS_WRONG_DTC;
   }

   if((DTCKind != DEM_DTC_KIND_ALL_DTCS) && (DTCKind != Dem_Cfg_Dtc_GetKind (dtcId)))
   {
   	return DEM_STATUS_WRONG_DTCKIND;
   }

   *DTCStatus =Dem_DtcStatusByteRetrieveWithOrigin(dtcId, DTCOrigin, &DtcStatusIsValid) & ((uint8)DEM_CFG_DTCSTATUS_AVAILABILITYMASK);
   if(!DtcStatusIsValid )
   {
   	return DEM_STATUS_FAILED;
   }
   return DEM_STATUS_OK;
}
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

