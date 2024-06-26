#include "Std_Types.hpp"

#include "Dem.hpp"
#include "Dem_Dlt.hpp"
#include "Ara_Dem.hpp"
#include "Dem_EvtRelatedData.hpp"
#include "Dem_EnvMain.hpp"
#include "Dem_EvMemBase.hpp"
#include "Dem_EvMem.hpp"
#include "Dem_Cfg.hpp"
#include "Dem_Cfg_Events_DataStructures.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

Std_ReturnType Dem_DltGetAllExtendedDataRecords(Dem_EventIdType EventId, uint8* DestBuffer, uint16* BufSize)
{

   Std_ReturnType returnValue = E_NOT_OK;
   Dem_EvMemEventMemoryType ReaderCopy;

   if(!Dem_isEventIdValid(EventId))
   {
   	return E_NOT_OK;
   }

   if(Dem_EvtIsSuppressed(EventId))
   {
        return E_NOT_OK;
   }

   if((DestBuffer==NULL_PTR) || (BufSize==NULL_PTR))
   {
        return E_NOT_OK;
   }

   if(Dem_EvMemGetReaderCopyOfEventFromEventMemory(&ReaderCopy, EventId) == E_OK)
   {
        returnValue = Dem_EnvRetrieveRawED(EventId, DestBuffer, BufSize, Dem_EvMemGetEventMemDataByPtr(&ReaderCopy), &ReaderCopy);
   }
   else
   {
   	return E_NOT_OK;
   }

   return returnValue;
}

Std_ReturnType Dem_DltGetMostRecentFreezeFrameRecordData(Dem_EventIdType EventId, uint8* DestBuffer, uint16* BufSize)
{

   uint16_least ffIndex;
   Std_ReturnType returnValue = E_NOT_OK;
   Dem_EvMemEventMemoryType ReaderCopy;

   if(!Dem_isEventIdValid(EventId))
   {
   	return E_NOT_OK;
   }

   if(Dem_EvtIsSuppressed(EventId))
   {
       return E_NOT_OK;
   }

   if((DestBuffer==NULL_PTR) || (BufSize==NULL_PTR))
   {
        return E_NOT_OK;
   }

   if(Dem_EvMemGetReaderCopyOfEventFromEventMemory(&ReaderCopy, EventId) == E_OK)
   {

        ffIndex = Dem_EvMemGetEventMemFreezeFrameCounterByPtr(&ReaderCopy);

        if(ffIndex < 1u)
        {
            return E_NOT_OK;
        }
        returnValue = Dem_EnvRetrieveRawFF(EventId, DestBuffer, BufSize, (uint8)(ffIndex - 1u), Dem_EvMemGetEventMemDataByPtr(&ReaderCopy), &ReaderCopy);
   }
   else
   {
   	returnValue = E_NOT_OK;
   }
   return returnValue;
}

Std_ReturnType Dem_GetEventExtendedDataRecord(
   	Dem_EventIdType EventId
   ,  uint8 RecordNumber
   ,  uint8* DestBuffer
   ,  uint16* BufSize
)
{
#if( DEM_CFG_EVMEM_EXTENDED_DATA_SUPPORTED != FALSE )
   Std_ReturnType returnValue = E_NOT_OK;
   Dem_TriggerType Trigger;

   Dem_EvMemEventMemoryType ReaderCopy;

   DEM_ENTRY_CONDITION_CHECK_DEMINIT_OR_OPMO_ALLFAILUREINFOLOCKED_EVTIDVALID_EVTAVAILABLE(EventId, DEM_DET_APIID_GETEVENTEXTENDEDDATARECORD , E_NOT_OK);
   DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(DestBuffer,DEM_DET_APIID_GETEVENTEXTENDEDDATARECORD,E_NOT_OK);
   DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(BufSize,DEM_DET_APIID_GETEVENTEXTENDEDDATARECORD,E_NOT_OK);

   if(!Dem_EnvIsEDRNumberValid (EventId, RecordNumber, &Trigger))
   {
   	return E_NOT_OK;
   }

   if(Dem_EvMemGetReaderCopyOfEventFromEventMemory(&ReaderCopy, EventId) == E_OK)
   {

        if(!Dem_EnvIsTriggerSet(Dem_EvMemGetEventMemTriggerByPtr(&ReaderCopy), Trigger))
        {
   		return E_NOT_OK;
   	}

        if( Dem_EnvRetrieveRawEDR(EventId, RecordNumber, DestBuffer, BufSize, Dem_EvMemGetEventMemDataByPtr(&ReaderCopy), &ReaderCopy) == FALSE )
   	{
   		returnValue = E_NOT_OK;
   	}
   	else
   	{
   	    returnValue = E_OK;
   	}

   }
   else
   {

   }

   return returnValue;

#else
   DEM_UNUSED_PARAM(EventId);
   DEM_UNUSED_PARAM(RecordNumber);
   DEM_UNUSED_PARAM(DestBuffer);
   DEM_UNUSED_PARAM(BufSize);
   return E_NOT_OK;
#endif
}

Std_ReturnType Dem_GetEventExtendedDataRecordForRTE(
        Dem_EventIdType EventId
   ,     uint8 RecordNumber
   ,     uint8* DestBuffer
)
{
   uint16 bufSize = DEM_SIZEOF_TYPE(Dem_MaxDataValueType);
    return Dem_GetEventExtendedDataRecord(EventId, RecordNumber, DestBuffer, &bufSize);
}

Std_ReturnType Dem_GetEventExtendedDataRecord_GeneralEvtInfo(
        Dem_EventIdType EventId
   ,     uint8 RecordNumber
   ,     uint8* DestBuffer
)
{
    return Dem_GetEventExtendedDataRecordForRTE(EventId, RecordNumber, DestBuffer);
}

Std_ReturnType Dem_GetEventExtendedDataRecordEx(Dem_EventIdType EventId, uint8 RecordNumber, uint8* DestBuffer, uint16* BufSize)
{
    return Dem_GetEventExtendedDataRecord(EventId, RecordNumber, DestBuffer, BufSize);
}

Std_ReturnType Dem_GetEventExtendedDataRecordEx_GeneralEvtInfo(Dem_EventIdType EventId, uint8 RecordNumber, uint8* DestBuffer, uint16* BufSize)
{
    return Dem_GetEventExtendedDataRecord(EventId, RecordNumber, DestBuffer, BufSize);
}

Std_ReturnType Dem_GetEventFreezeFrameData(
   	Dem_EventIdType EventId
   ,  uint8 RecordNumber
   ,  boolean ReportTotalRecord
   ,  uint16 DataId
   ,  uint8* DestBuffer
   ,  uint16* BufSize
)
{
#if( DEM_CFG_EVMEM_FREEZE_FRAME_SUPPORTED != FALSE )
   Std_ReturnType returnValue = E_NOT_OK;
   uint16_least ffIndex = 0xFFFF;
   Dem_EvMemEventMemoryType ReaderCopy;

   DEM_ENTRY_CONDITION_CHECK_DEMINIT_OR_OPMO_ALLFAILUREINFOLOCKED_EVTIDVALID_EVTAVAILABLE(EventId, DEM_DET_APIID_GETEVENTFREEZEFRAMEDATA , E_NOT_OK);
   DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(DestBuffer,DEM_DET_APIID_GETEVENTFREEZEFRAMEDATA,E_NOT_OK);
   DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(BufSize,DEM_DET_APIID_GETEVENTFREEZEFRAMEDATA,E_NOT_OK);

   if(  (!Dem_EnvIsFFRecNumValid(EventId,RecordNumber)) && (RecordNumber != 0xFF)

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
         && (RecordNumber != 0x00)
#endif

         )
   {
       DEM_ASSERT_ISNOTLOCKED();
       return E_NOT_OK;
   }

   if(Dem_EvMemGetReaderCopyOfEventFromEventMemory(&ReaderCopy, EventId) == E_OK)
   {
       if(RecordNumber == 0xFFu)
       {
#if(DEM_CFG_FFRECNUM == DEM_CFG_FFRECNUM_CALCULATED)

           ffIndex = Dem_EvMemGetEventMemFreezeFrameCounterByPtr(&ReaderCopy);

   		if(ffIndex > 0u)
   		{
   			ffIndex--;
   		}
   		else
#endif
   		{
   			return E_NOT_OK;
   		}
   	}
      else if(RecordNumber == 0x00u)
      {

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)

         if((DataId & 0xFF00u) == 0xF400u)
         {
            returnValue = rba_DemObdBasic_FF_RetrievePidData((uint8)(DataId & 0xFFu), DestBuffer, BufSize, &ReaderCopy);
         }
         else{

            returnValue = E_NOT_OK;
         }
#else

         return E_NOT_OK;

#endif

      }
   	else
   	{
   		ffIndex = Dem_EnvGetIndexFromFFRecNum(EventId,RecordNumber);
   	}

   	if(ReportTotalRecord)
   	{
   		DEM_DET(DEM_DET_APIID_GETEVENTFREEZEFRAMEDATA, 0);
   		return E_NOT_OK;
   	}
   	else
   	{
#if(DEM_CFG_FFRECNUM == DEM_CFG_FFRECNUM_CALCULATED)
   		if(ffIndex < Dem_EvtParam_GetMaxNumberFreezeFrameRecords(EventId))
#else
   		if(Dem_EnvIsFFRecNumStored(&ReaderCopy, RecordNumber))
#endif
   		{
   		    if( Dem_EnvRetrieveRawDid(EventId, DestBuffer, BufSize, (uint8)(ffIndex), DataId, Dem_EvMemGetEventMemDataByPtr(&ReaderCopy), &ReaderCopy) == FALSE )
   			{
   				returnValue = E_NOT_OK;
   			}
   			else
   			{
   				returnValue = E_OK;
   			}
   		}
   		else
   		{

   		}
   	}
   }
   else
   {

   }

   return returnValue;

#else
   DEM_UNUSED_PARAM(EventId);
   DEM_UNUSED_PARAM(RecordNumber);
   DEM_UNUSED_PARAM(ReportTotalRecord);
   DEM_UNUSED_PARAM(DataId);
   DEM_UNUSED_PARAM(DestBuffer);
   DEM_UNUSED_PARAM(BufSize);
   return E_NOT_OK;
#endif
}

Std_ReturnType Dem_GetEventFreezeFrameDataForRTE(
        Dem_EventIdType EventId
   ,     uint8 RecordNumber
   ,     boolean ReportTotalRecord
   ,     uint16 DataId
   ,     Dem_MaxDataValueType DestBuffer
)
{
   uint16 bufSize = DEM_SIZEOF_TYPE(Dem_MaxDataValueType);
    return Dem_GetEventFreezeFrameData(EventId, RecordNumber, ReportTotalRecord, DataId, DestBuffer, &bufSize);
}

Std_ReturnType Dem_GetEventFreezeFrameDataEx(Dem_EventIdType EventId, uint8 RecordNumber, uint16 DataId, uint8* DestBuffer, uint16* BufSize)
{
   boolean ReportTotalRecord = FALSE;
    return Dem_GetEventFreezeFrameData(EventId, RecordNumber, ReportTotalRecord, DataId, DestBuffer, BufSize);
}

Std_ReturnType Dem_GetEventFreezeFrameDataEx_GeneralEvtInfo(Dem_EventIdType EventId, uint8 RecordNumber, uint16 DataId, uint8* DestBuffer, uint16* BufSize)
{
   boolean ReportTotalRecord = FALSE;
    return Dem_GetEventFreezeFrameData(EventId, RecordNumber, ReportTotalRecord, DataId, DestBuffer, BufSize);
}

Std_ReturnType Dem_GetEventFreezeFrameData_GeneralEvtInfo(
        Dem_EventIdType EventId
   ,     uint8 RecordNumber
   ,     boolean ReportTotalRecord
   ,     uint16 DataId
   ,     Dem_MaxDataValueType DestBuffer
)
{
    return Dem_GetEventFreezeFrameDataForRTE(EventId, RecordNumber, ReportTotalRecord, DataId, DestBuffer);
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
