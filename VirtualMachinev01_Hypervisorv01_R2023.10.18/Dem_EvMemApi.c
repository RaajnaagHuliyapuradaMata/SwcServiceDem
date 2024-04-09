#include "Std_Types.hpp"

#include "Dem.hpp"
#include "Dem_Dcm.hpp"
#include "Rte_Dem.hpp"
#include "Dem_EvMemApi.hpp"
#include "Dem_EvMem.hpp"
#include "Dem_Lock.hpp"
#include "Dem_EnvMain.hpp"
#include "Dem_Mapping.hpp"
#include "Dem_DTCs.hpp"
#include "Dem_Cfg.hpp"
#include "Dem_Cfg_Events_DataStructures.hpp"

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"
static Dem_DtcIdType DemDtcIdCopy;
static uint32 DemDtcCodeCopy;
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
uint16_least Dem_EvMemGetMemoryLocIdOfDtcAndOriginWithVisibility(Dem_DtcIdType DtcId, Dem_DTCOriginType DTCOrigin, Dem_boolean_least ShadowEntriesVisible)
{
   if(DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY)
   {
   	return Dem_EvMemGetEventMemoryLocIdOfDtcWithVisibility (DtcId, DEM_CFG_EVMEM_MEMID_PRIMARY, ShadowEntriesVisible);
   }

#if DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY > 0
   if(DTCOrigin == DEM_DTC_ORIGIN_SECONDARY_MEMORY)
   {
   	return Dem_EvMemGetEventMemoryLocIdOfDtcWithVisibility (DtcId, DEM_CFG_EVMEM_MEMID_SECONDARY, ShadowEntriesVisible);
   }
#endif

#if(DEM_CFG_MAX_NUMBER_EVENT_ENTRY_MIRROR > 0)
   if(DTCOrigin == DEM_DTC_ORIGIN_MIRROR_MEMORY)
   {
   	return Dem_EvMemGetEventMemoryLocIdOfDtc (DtcId, DEM_CFG_EVMEM_MEMID_MIRROR);
   }
#elif DEM_CFG_EVMEM_SHADOW_MEMORY_SUPPORTED
   if(DTCOrigin == DEM_DTC_ORIGIN_MIRROR_MEMORY)
   {
   	return Dem_EvMemGetShadowMemoryLocIdOfDtc(DtcId, DEM_CFG_EVMEM_MEMID_SHADOW);
   }
#endif

   return DEM_EVMEM_INVALID_LOCID;
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#if DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x04 || DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x06
#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"
Dem_EvMemDTCRecordType Dem_EvMemDTCRecord;
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"
DEM_INLINE void Dem_EvMemInvalidateSyncDataRecord(void){
   DEM_ENTERLOCK_DCM();

   Dem_EvMemDTCRecord.DtcId = DEM_DTCID_INVALID;

    DEM_EXITLOCK_DCM();
}

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
static Dem_boolean_least Dem_EvMemReqSyncDataRecord(Dem_DtcIdType DtcId, Dem_DTCOriginType DTCOrigin)
{

   Dem_boolean_least returnStatus;

   DEM_ENTERLOCK_DCM();

   if((Dem_EvMemDTCRecord.DtcId != DtcId) || (Dem_EvMemDTCRecord.DTCOrigin != DTCOrigin))
   {
   	Dem_EvMemDTCRecord.DtcId = DtcId;
   	Dem_EvMemDTCRecord.DTCOrigin = DTCOrigin;
   	Dem_EvMemDTCRecord.ReqCounter++;
   }
   returnStatus = (Dem_boolean_least)(Dem_EvMemDTCRecord.ReqCounter == Dem_EvMemDTCRecord.DemCounter);

   DEM_EXITLOCK_DCM();

   return returnStatus;
}
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
#endif
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
void Dem_EvMemApiMainFunction(void){
#if DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x04 || DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x06

   uint16_least LocId;
   Dem_DtcIdType DtcIdStored;
   Dem_DTCOriginType DTCOriginStored;
   uint8 ReqCounterStored;

   DEM_ENTERLOCK_DCM();

   DtcIdStored = Dem_EvMemDTCRecord.DtcId;
   DTCOriginStored = Dem_EvMemDTCRecord.DTCOrigin;
   ReqCounterStored = Dem_EvMemDTCRecord.ReqCounter;

   if(ReqCounterStored != Dem_EvMemDTCRecord.DemCounter)
   {
   	Dem_EvMemDTCRecord.IsValid = FALSE;
   	if(Dem_isDtcIdValid (DtcIdStored))
   	{
   		LocId = Dem_EvMemGetMemoryLocIdOfDtcAndOriginWithVisibility(DtcIdStored, DTCOriginStored, Dem_EvMemGetShadowVisibility());
   		Dem_EvMemDTCRecord.IsValid = (boolean) Dem_EvMemIsEventMemLocIdValid (LocId);
   		if(Dem_EvMemDTCRecord.IsValid)
   		{
   			Dem_EvMemDTCRecord.EventMemory = Dem_EvMemEventMemory[LocId];
   		}
   	}
   	Dem_EvMemDTCRecord.DemCounter = ReqCounterStored;
   }

   DEM_EXITLOCK_DCM();

#endif
}

#if DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x04 || DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x06

Dem_ReturnDisableDTCRecordUpdateType Dem_DisableDTCRecordUpdate(uint32 DTC,Dem_DTCOriginType DTCOrigin)
{
   DEM_UNUSED_PARAM(DTC);
   DEM_UNUSED_PARAM(DTCOrigin);

    Dem_EvMemInvalidateSyncDataRecord ();
   return DEM_DISABLE_DTCRECUP_OK;
}

Std_ReturnType Dem_EnableDTCRecordUpdate(void){
   return E_OK;
}

#endif

#if DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x06

Dem_ReturnGetExtendedDataRecordByDTCType Dem_GetExtendedDataRecordByDTC(uint32 DTC
   ,  Dem_DTCKindType DTCKind
   ,  Dem_DTCOriginType DTCOrigin
   ,  uint8 ExtendedDataNumber
   ,  uint8* DestBuffer
   ,  uint16* BufSize)
{
   Dem_DtcIdType DtcId;
   Dem_EventIdType EventId;
   Dem_TriggerType Trigger;

   if(!Dem_EvMemIsDtcKindValid (DTCKind))
   {
   	DEM_DET(DEM_DET_APIID_GETEXTENDEDDATARECORDBYDTC, DEM_E_WRONG_CONFIGURATION);
   	return DEM_RECORD_WRONG_DTCKIND;
   }

   if(!Dem_EvMemIsDtcOriginValid (&DTCOrigin))
   {
   	DEM_DET(DEM_DET_APIID_GETEXTENDEDDATARECORDBYDTC, DEM_E_WRONG_CONFIGURATION);
   	return DEM_RECORD_WRONG_DTCORIGIN;
   }

   if((DestBuffer==NULL_PTR) || (BufSize==NULL_PTR))
   {
       return DEM_RECORD_WRONG_BUFFERSIZE;
   }

   if(DTC != DemDtcCodeCopy)
   {
       DemDtcIdCopy = Dem_DtcIdFromDtcCode (DTC);
       DemDtcCodeCopy = DTC;
   }
   DtcId = DemDtcIdCopy;

   if(!Dem_DtcIsSupported (DtcId))
   {
   	DEM_DET(DEM_DET_APIID_GETEXTENDEDDATARECORDBYDTC, DEM_E_WRONG_CONFIGURATION);
   	return DEM_RECORD_WRONG_DTC;
   }

   EventId = Dem_DtcIdGetFirstEventId (DtcId);

   if(!Dem_EnvIsEDRNumberValid (EventId, ExtendedDataNumber, &Trigger))
   {

       if( (ExtendedDataNumber < 0x01) || (ExtendedDataNumber > 0xEF) )
       {
           DEM_DET(DEM_DET_APIID_GETEXTENDEDDATARECORDBYDTC, DEM_E_WRONG_CONFIGURATION);
       }
   	return DEM_RECORD_WRONG_NUMBER;
   }

   if(!Dem_EvMemReqSyncDataRecord (DtcId, DTCOrigin))
   {
   	return DEM_RECORD_PENDING;
   }

   if(!Dem_EvMemDTCRecord.IsValid)
   {
   	*BufSize = 0;
   	return DEM_RECORD_OK;
   }

   if(!Dem_EnvIsTriggerSet(Dem_EvMemGetEventMemTriggerByPtr(&Dem_EvMemDTCRecord.EventMemory), Trigger))
   {
   	*BufSize = 0;
   	return DEM_RECORD_OK;
   }

   return Dem_EnvRetrieveEDR (Dem_EvMemGetEventMemEventIdByPtr(&(Dem_EvMemDTCRecord.EventMemory)), ExtendedDataNumber, DestBuffer, BufSize, Dem_EvMemGetEventMemDataByPtr (&(Dem_EvMemDTCRecord.EventMemory)), &(Dem_EvMemDTCRecord.EventMemory));
}

Dem_ReturnGetSizeOfExtendedDataRecordByDTCType Dem_GetSizeOfExtendedDataRecordByDTC(uint32 DTC
   ,  Dem_DTCKindType DTCKind
   ,  Dem_DTCOriginType DTCOrigin
   ,  uint8 ExtendedDataNumber
   ,  uint16* SizeOfExtendedDataRecord)
{
   Dem_DtcIdType DtcId;
   Dem_EventIdType EventId;
   Dem_TriggerType Trigger;

   if(!Dem_EvMemIsDtcKindValid (DTCKind))
   {
   	DEM_DET(DEM_DET_APIID_GETSIZEOFEXTENDEDDATARECORDBYDTC, DEM_E_WRONG_CONFIGURATION);
   	return DEM_GET_SIZEOFEDRBYDTC_W_DTCKI;
   }

   if(!Dem_EvMemIsDtcOriginValid (&DTCOrigin))
   {
   	DEM_DET(DEM_DET_APIID_GETSIZEOFEXTENDEDDATARECORDBYDTC, DEM_E_WRONG_CONFIGURATION);
   	return DEM_GET_SIZEOFEDRBYDTC_W_DTCOR;
   }

   if(DTC != DemDtcCodeCopy)
   {
       DemDtcIdCopy = Dem_DtcIdFromDtcCode (DTC);
       DemDtcCodeCopy = DTC;
   }
   DtcId = DemDtcIdCopy;

   if(!Dem_DtcIsSupported (DtcId))
   {
   	DEM_DET(DEM_DET_APIID_GETSIZEOFEXTENDEDDATARECORDBYDTC, DEM_E_WRONG_CONFIGURATION);
   	return DEM_GET_SIZEOFEDRBYDTC_W_DTC;
   }

   EventId = Dem_DtcIdGetFirstEventId (DtcId);

   if((!Dem_EnvIsEDRNumberValid (EventId, ExtendedDataNumber, &Trigger)) && (ExtendedDataNumber != 0xFF))
   {
   	DEM_DET(DEM_DET_APIID_GETSIZEOFEXTENDEDDATARECORDBYDTC, DEM_E_WRONG_CONFIGURATION);
   	return DEM_GET_SIZEOFEDRBYDTC_W_RNUM;
   }

   if(ExtendedDataNumber == 0xFF)
   {
   	return Dem_EnvGetSizeOfED(EventId, SizeOfExtendedDataRecord);
   }
   else
   {
       return Dem_EnvGetSizeOfEDR (EventId, ExtendedDataNumber, SizeOfExtendedDataRecord);
   }
}
#endif

#if DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x04

Dem_ReturnGetFreezeFrameDataByDTCType Dem_GetFreezeFrameDataByDTC(uint32 DTC
   ,  Dem_DTCKindType DTCKind
   ,  Dem_DTCOriginType DTCOrigin
   ,  uint8 RecordNumber
   ,  uint8* DestBuffer
   ,  uint16* BufSize)
{
   Dem_DtcIdType DtcId;
   uint8 RecordIndex;
   Dem_EventIdType EventId;

   if(!Dem_EvMemIsDtcKindValid (DTCKind))
   {
   	DEM_DET(DEM_DET_APIID_GETFREEZEFRAMEDATABYDTC, DEM_E_WRONG_CONFIGURATION);
   	return DEM_GET_FFDATABYDTC_WRONG_DTCKIND;
   }

   if(!Dem_EvMemIsDtcOriginValid (&DTCOrigin))
   {
   	DEM_DET(DEM_DET_APIID_GETFREEZEFRAMEDATABYDTC, DEM_E_WRONG_CONFIGURATION);
   	return DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN;
   }

   if((DestBuffer==NULL_PTR) || (BufSize==NULL_PTR))
   {
       return DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE;
   }

   if(DTC != DemDtcCodeCopy)
   {
        DemDtcIdCopy = Dem_DtcIdFromDtcCode (DTC);
        DemDtcCodeCopy = DTC;
   }
    DtcId = DemDtcIdCopy;

   if(!Dem_DtcIsSupported (DtcId))
   {
   	DEM_DET(DEM_DET_APIID_GETFREEZEFRAMEDATABYDTC, DEM_E_WRONG_CONFIGURATION);
   	return DEM_GET_FFDATABYDTC_WRONG_DTC;
   }

   EventId = Dem_DtcIdGetFirstEventId (DtcId);

   if(RecordNumber == 0xFFu)
   {
        DEM_DET(DEM_DET_APIID_GETFREEZEFRAMEDATABYDTC, DEM_E_WRONG_CONFIGURATION);
        return DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER;
   }

   if(!Dem_EnvIsFFRecNumValid(EventId,RecordNumber))
   {
   	return DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER;
   }

   if(!Dem_EvMemReqSyncDataRecord (DtcId, DTCOrigin))
   {
   	return DEM_GET_FFDATABYDTC_PENDING;
   }

   if(!Dem_EvMemDTCRecord.IsValid)
   {
   	*BufSize = 0;
   	return DEM_GET_FFDATABYDTC_OK;
   }

   RecordIndex = Dem_EnvGetIndexFromFFRecNum (EventId, RecordNumber);

   if(! Dem_EnvIsFFRecNumStored(&Dem_EvMemDTCRecord.EventMemory, RecordNumber))
   {
        *BufSize = 0;
        return DEM_GET_FFDATABYDTC_OK;
   }

    return Dem_EnvRetrieveFF (Dem_EvMemGetEventMemEventIdByPtr(&(Dem_EvMemDTCRecord.EventMemory)), DestBuffer, BufSize, RecordIndex, Dem_EvMemGetEventMemDataByPtr (&(Dem_EvMemDTCRecord.EventMemory)), &(Dem_EvMemDTCRecord.EventMemory));
}

Dem_ReturnGetSizeOfFreezeFrameByDTCType Dem_GetSizeOfFreezeFrameByDTC(uint32 DTC
   ,  Dem_DTCKindType DTCKind
   ,  Dem_DTCOriginType DTCOrigin
   ,  uint8 RecordNumber
   ,  uint16* SizeOfFreezeFrame)
{
   Dem_DtcIdType DtcId;
   uint8  NoOfFreezeFrames;
   Dem_EventIdType EventId;
   Dem_ReturnGetSizeOfFreezeFrameByDTCType ReturnSts;

   if(!Dem_EvMemIsDtcKindValid (DTCKind))
   {
   	DEM_DET(DEM_DET_APIID_GETSIZEOFFREEZEFRAMEBYDTC, DEM_E_WRONG_CONFIGURATION);
   	return DEM_GET_SIZEOFFF_WRONG_DTCKIND;
   }

   if(!Dem_EvMemIsDtcOriginValid (&DTCOrigin))
   {
   	DEM_DET(DEM_DET_APIID_GETSIZEOFFREEZEFRAMEBYDTC, DEM_E_WRONG_CONFIGURATION);
   	return DEM_GET_SIZEOFFF_WRONG_DTCOR;
   }

   if(DTC != DemDtcCodeCopy)
   {
        DemDtcIdCopy = Dem_DtcIdFromDtcCode (DTC);
        DemDtcCodeCopy = DTC;
   }
    DtcId = DemDtcIdCopy;

   if(!Dem_DtcIsSupported (DtcId))
   {
   	DEM_DET(DEM_DET_APIID_GETSIZEOFFREEZEFRAMEBYDTC, DEM_E_WRONG_CONFIGURATION);
   	return DEM_GET_SIZEOFFF_WRONG_DTC;
   }

   EventId = Dem_DtcIdGetFirstEventId (DtcId);

   if((!Dem_EnvIsFFRecNumValid(EventId,RecordNumber)) && (RecordNumber != 0xFF))
   {
   	DEM_DET(DEM_DET_APIID_GETSIZEOFFREEZEFRAMEBYDTC, DEM_E_WRONG_CONFIGURATION);
   	return DEM_GET_SIZEOFFF_WRONG_RNUM;
   }

   ReturnSts = Dem_EnvGetSizeOfFF (EventId, SizeOfFreezeFrame);
   if(RecordNumber == 0xFF)
   {
   	NoOfFreezeFrames = Dem_EvtParam_GetMaxNumberFreezeFrameRecords(EventId);
   	*SizeOfFreezeFrame = (*SizeOfFreezeFrame) * NoOfFreezeFrames;
   }

   return ReturnSts;
}
#endif
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#if DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x03

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"
static uint16_least Dem_EvMemFilteredRecordLocId;
static uint16_least Dem_EvMemFilteredRecordFreezeFrameId;

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
static Dem_DTCFormatType Dem_EvMemFilteredRecordDTCFormat;
#endif

#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

Dem_ReturnSetFilterType Dem_SetFreezeFrameRecordFilter(Dem_DTCFormatType DTCFormat, uint16* NumberOfFilteredRecords)
{
   uint16_least LocId;

#if(DEM_CFG_OBD == DEM_CFG_OBD_OFF)

   if(DTCFormat == DEM_DTC_FORMAT_OBD)
   {
      return DEM_WRONG_FILTER;
   }

#endif

   *NumberOfFilteredRecords = 0;

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
   Dem_EvMemFilteredRecordDTCFormat = DTCFormat;
#endif

   for(Dem_EvMemEventMemoryLocIteratorNew     (&Dem_EvMemFilteredRecordLocId, DEM_CFG_EVMEM_MEMID_PRIMARY);
   	 Dem_EvMemEventMemoryLocIteratorIsValid (&Dem_EvMemFilteredRecordLocId, DEM_CFG_EVMEM_MEMID_PRIMARY);
   	 Dem_EvMemEventMemoryLocIteratorNext    (&Dem_EvMemFilteredRecordLocId, DEM_CFG_EVMEM_MEMID_PRIMARY))
   {
   	if( Dem_EvMemIsVisible(Dem_EvMemGetEventMemStatus(Dem_EvMemFilteredRecordLocId), Dem_EvMemGetShadowVisibility()))
   	{
   		LocId = Dem_EvMemFilteredRecordLocId;
   		if(Dem_LibGetParamUI8(DEM_CFG_EVCOMB) == Dem_LibGetParamUI8(DEM_CFG_EVCOMB_ONRETRIEVAL))
   		{
   			LocId = Dem_EvMemGetEventMemoryLocIdOfDtcWithVisibility (Dem_DtcIdFromEventId (Dem_EvMemGetEventMemEventId (Dem_EvMemFilteredRecordLocId)), DEM_CFG_EVMEM_MEMID_PRIMARY, Dem_EvMemGetShadowVisibility());
   		}

   		if(LocId == Dem_EvMemFilteredRecordLocId)
   		{
   			*NumberOfFilteredRecords = *NumberOfFilteredRecords + (uint16) Dem_EvMemGetEventMemFreezeFrameCounter (Dem_EvMemFilteredRecordLocId);
   		}
   	}
   }

   Dem_EvMemEventMemoryLocIteratorNew (&Dem_EvMemFilteredRecordLocId, DEM_CFG_EVMEM_MEMID_PRIMARY);
   Dem_EvMemFilteredRecordFreezeFrameId = 0;

   return DEM_FILTER_ACCEPTED;
}

Dem_ReturnGetNextFilteredDTCType Dem_GetNextFilteredRecord(uint32* DTC, uint8* RecordNumber)
{
   uint16_least LocId;
   uint16_least Status;
   Dem_EventIdType EventId;
   uint16_least FreezeFrameCounter;

   while(Dem_EvMemEventMemoryLocIteratorIsValid (&Dem_EvMemFilteredRecordLocId, DEM_CFG_EVMEM_MEMID_PRIMARY))
   {

   	Status = Dem_EvMemGetEventMemStatus (Dem_EvMemFilteredRecordLocId);
   	EventId = Dem_EvMemGetEventMemEventId (Dem_EvMemFilteredRecordLocId);
   	FreezeFrameCounter = Dem_EvMemGetEventMemFreezeFrameCounter (Dem_EvMemFilteredRecordLocId);

   	if( Dem_EvMemIsVisible(Status, Dem_EvMemGetShadowVisibility()))
        {
            if(Dem_LibGetParamUI8(DEM_CFG_EVCOMB) == Dem_LibGetParamUI8(DEM_CFG_EVCOMB_ONRETRIEVAL))
            {
                if(Dem_EvMemFilteredRecordFreezeFrameId == 0u)
                {
                    LocId = Dem_EvMemGetEventMemoryLocIdOfDtcWithVisibility(Dem_DtcIdFromEventId(EventId)
   ,     DEM_CFG_EVMEM_MEMID_PRIMARY, Dem_EvMemGetShadowVisibility());
                    if(LocId != Dem_EvMemFilteredRecordLocId)
                    {

                    	Dem_EvMemFilteredRecordFreezeFrameId = 0xFFu;
                    }
                }
            }
            if(Dem_LibGetParamUI8(DEM_CFG_FFRECNUM) == Dem_LibGetParamUI8(DEM_CFG_FFRECNUM_CALCULATED))
            {

                if(Dem_EvMemFilteredRecordFreezeFrameId < FreezeFrameCounter)
                {
                    *RecordNumber = Dem_EnvGetFFRecNumFromIndex(EventId, (uint8) Dem_EvMemFilteredRecordFreezeFrameId);

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
                    if(Dem_EvMemFilteredRecordDTCFormat == DEM_DTC_FORMAT_UDS)
                    {
                        *DTC = Dem_GetDtcCode(Dem_DtcIdFromEventId (EventId));
                    }
                    else
                    {
                        *DTC = rba_DemObdBasic_Dtc_GetCode(Dem_DtcIdFromEventId (EventId));
                    }
#else

                    *DTC = Dem_GetDtcCode(Dem_DtcIdFromEventId(EventId));

#endif

                    Dem_EvMemFilteredRecordFreezeFrameId++;
                    return DEM_FILTERED_OK;
                }
                else{
                    Dem_EvMemFilteredRecordFreezeFrameId = 0;
                }
            }
            else{

                if(Dem_EvMemFilteredRecordFreezeFrameId != 0xFFu)
                {

                    while(Dem_EvMemFilteredRecordFreezeFrameId < Dem_EvtParam_GetMaxNumberFreezeFrameRecords(EventId))
                    {

                        *RecordNumber = Dem_EnvGetFFRecNumFromIndex(EventId, (uint8) Dem_EvMemFilteredRecordFreezeFrameId);

                        if(Dem_EnvIsTriggerSet(Dem_EnvGetFFRecordTrigger(*RecordNumber) , Dem_EvMemGetEventMemTrigger(Dem_EvMemFilteredRecordLocId)))
                        {

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
                            if(Dem_EvMemFilteredRecordDTCFormat == DEM_DTC_FORMAT_UDS)
                            {
                                *DTC = Dem_GetDtcCode(Dem_DtcIdFromEventId (EventId));
                            }
                            else
                            {
                                *DTC = rba_DemObdBasic_Dtc_GetCode(Dem_DtcIdFromEventId (EventId));
                            }
#else
                            *DTC = Dem_GetDtcCode(Dem_DtcIdFromEventId(EventId));
#endif

                            Dem_EvMemFilteredRecordFreezeFrameId++;

                            return DEM_FILTERED_OK;
                        }
                        Dem_EvMemFilteredRecordFreezeFrameId++;
                    }
                }

                Dem_EvMemFilteredRecordFreezeFrameId = 0;
            }
        }
   	Dem_EvMemEventMemoryLocIteratorNext (&Dem_EvMemFilteredRecordLocId, DEM_CFG_EVMEM_MEMID_PRIMARY);
   }
   return DEM_FILTERED_NO_MATCHING_DTC;
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
Dem_ReadEventType Dem_ReadEventsFromMemory (Dem_ReadEventsFromMemoryType* ReadEventsFromMemoryState, Dem_DTCOriginType origin)
{
   ReadEventsFromMemoryState->evMemId = Dem_EvMemGetEvMemIdFromOrigin(origin);
   if(Dem_EvMemIsOriginSupported(origin))
   {
   	Dem_EvMemEventMemoryLocIteratorNew (&ReadEventsFromMemoryState->locIterator, ReadEventsFromMemoryState->evMemId);
   	return DEM_READEVENT_OK;
   }
   else
   {
   	Dem_EvMemEventMemoryLocIteratorInvalidate(&ReadEventsFromMemoryState->locIterator, ReadEventsFromMemoryState->evMemId);
   	return DEM_READEVENT_WRONG_ORIGIN;
   }
}

Dem_ReadEventType Dem_GetNextEventFromMemory (Dem_ReadEventsFromMemoryType* ReadEventsFromMemoryState, Dem_EventIdType* EventId, uint16* LocId)
{
   while(Dem_EvMemEventMemoryLocIteratorIsValid (&ReadEventsFromMemoryState->locIterator, ReadEventsFromMemoryState->evMemId))
   {
   	*EventId = Dem_EvMemGetEventMemEventId (ReadEventsFromMemoryState->locIterator);

   	*LocId = (uint16)ReadEventsFromMemoryState->locIterator;
   	Dem_EvMemEventMemoryLocIteratorNext (&ReadEventsFromMemoryState->locIterator,ReadEventsFromMemoryState->evMemId);

   	if(Dem_EvMemIsStored(Dem_EvMemGetEventMemStatus((uint16_least)*LocId)))
   	{
   		return DEM_READEVENT_OK;
   	}
   }
   return DEM_READEVENT_NO_MATCHING_ELEMENT;
}

DEM_INLINE uint8 Dem_EvMemGetNoOfEntries(uint16_least MemId)
{
   uint16_least LocId;
   uint8 counter = 0;

   if(Dem_EvMemIsMemIdValid(MemId))
   {
        for(Dem_EvMemEventMemoryLocIteratorNew(&LocId, MemId); Dem_EvMemEventMemoryLocIteratorIsValid(&LocId, MemId);
                Dem_EvMemEventMemoryLocIteratorNext(&LocId, MemId))
        {
            if(Dem_EvMemIsStored(Dem_EvMemGetEventMemStatus(LocId)))
            {
                counter++;
            }
        }
   }
    return counter;
}

Std_ReturnType Dem_GetNumberOfEventMemoryEntries(Dem_DTCOriginType DTCOrigin, uint8* NumberOfEventMemoryEntries)
{
    Std_ReturnType retVal = E_NOT_OK;

    DEM_ENTRY_CONDITION_CHECK_DEM_INITIALIZED(DEM_DET_APIID_DEM_EVMEMGETNUMBEROFEVENTENTRIES,E_NOT_OK);
    DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(NumberOfEventMemoryEntries,DEM_DET_APIID_DEM_EVMEMGETNUMBEROFEVENTENTRIES,E_NOT_OK);
   if(!Dem_EvMemIsDtcOriginValid(&DTCOrigin))
   {
        DEM_DET(DEM_DET_APIID_DEM_EVMEMGETNUMBEROFEVENTENTRIES, DEM_E_WRONG_CONFIGURATION);
        retVal = E_NOT_OK;
   }

   if(DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY)
   {
        *NumberOfEventMemoryEntries = Dem_EvMemGetNoOfEntries(DEM_CFG_EVMEM_MEMID_PRIMARY);
        retVal = E_OK;
   }

#if DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY > 0
   if(DTCOrigin == DEM_DTC_ORIGIN_SECONDARY_MEMORY)
   {
        *NumberOfEventMemoryEntries = Dem_EvMemGetNoOfEntries(DEM_CFG_EVMEM_MEMID_SECONDARY);
        retVal = E_OK;
   }
#endif

#if(DEM_CFG_MAX_NUMBER_EVENT_ENTRY_MIRROR > 0)
   if(DTCOrigin == DEM_DTC_ORIGIN_MIRROR_MEMORY)
   {
        *NumberOfEventMemoryEntries = Dem_EvMemGetNoOfEntries(DEM_CFG_EVMEM_MEMID_MIRROR);
        retVal = E_OK;
   }
#elif DEM_CFG_EVMEM_SHADOW_MEMORY_SUPPORTED
   if(DTCOrigin == DEM_DTC_ORIGIN_MIRROR_MEMORY)
   {
        *NumberOfEventMemoryEntries = Dem_EvMemGetNoOfEntries(DEM_CFG_EVMEM_MEMID_SHADOW);
        retVal = E_OK;
   }
#endif
    return retVal;
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#endif

