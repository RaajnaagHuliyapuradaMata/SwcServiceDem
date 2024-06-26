#include "Std_Types.hpp"

#include "Dem_Dcm.hpp"
#include "Dem_DTCFilter.hpp"
#include "Dem_Cfg_DTC_DataStructures.hpp"
#include "Dem_Cfg_DTCs.hpp"
#include "Dem_BitArray.hpp"
#include "Dem_Cfg.hpp"
#include "Dem_ChronoSort.hpp"

typedef struct{
   volatile boolean start;
   volatile boolean exec;
   volatile uint8   DTCStatus;
   volatile Dem_DTCOriginType DTCOrigin;
   volatile Dem_DtcIdType DtcId;
}Dem_DTCFilterSyncState;

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"
   DEM_BITARRAY_DEFINE(Dem_DTCFilterMatching,DEM_DTCID_ARRAYLENGTH);
   Dem_DTCFilterState Dem_DTCFilter;
   #if DEM_CFG_EVMEM_MIRROR_MEMORY_DTC_STATUS_STORED
   static Dem_DTCFilterSyncState Dem_DTCFilterSync;
   #endif
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

DEM_INLINE void Dem_DtcFilterSyncInit(void){
#if DEM_CFG_EVMEM_MIRROR_MEMORY_DTC_STATUS_STORED

   Dem_DTCFilterSync.start  = TRUE;
#endif
}

DEM_INLINE boolean Dem_DtcFilterSyncGetDtcStatusByte (Dem_DtcIdType dtcId, Dem_DTCOriginType DTCOrigin, uint8* DTCStatus)
{
   DEM_UNUSED_PARAM(DTCOrigin);

#if DEM_CFG_EVMEM_MIRROR_MEMORY_DTC_STATUS_STORED

   if(DTCOrigin == DEM_DTC_ORIGIN_MIRROR_MEMORY)
   {

   	if(Dem_DTCFilterSync.exec)
   	{
   		return FALSE;
   	}

   	if(Dem_DTCFilterSync.start)
   	{
   		Dem_DTCFilterSync.DtcId = dtcId;
   		Dem_DTCFilterSync.DTCOrigin = DTCOrigin;
   		Dem_DTCFilterSync.start = FALSE;
   		Dem_DTCFilterSync.exec = TRUE;
   		return FALSE;
   	}

   	*DTCStatus = Dem_DTCFilterSync.DTCStatus;
   	Dem_DTCFilterSync.start = TRUE;
   	return TRUE;
   }
#endif

   *DTCStatus = Dem_DtcStatusByteRetrieve(dtcId);
   return TRUE;
}

DEM_INLINE void Dem_DtcFilterSyncCyclic(void){
#if DEM_CFG_EVMEM_MIRROR_MEMORY_DTC_STATUS_STORED
   if(Dem_DTCFilterSync.exec)
   {
   	boolean DtcStatusIsValid;

   	Dem_DTCFilterSync.DTCStatus = Dem_DtcStatusByteRetrieveWithOrigin(Dem_DTCFilterSync.DtcId, Dem_DTCFilterSync.DTCOrigin, &DtcStatusIsValid);
   	Dem_DTCFilterSync.exec = FALSE;
   }
#endif
}

void Dem_DtcFilterInit(void){
#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
    rba_DemObdBasic_Dtc_DtcFilterInit(&Dem_DTCFilter);
#endif

#if(DEM_CFG_REPORT_CHRONOLOGICAL_ORDER_HOOKS_ENABLED)
    Dem_ChronoSortDTCFilterInit();
#endif
    Dem_DtcIdIteratorInvalidate(&Dem_DTCFilter.searchIt);
    Dem_DtcIdIteratorInvalidate(&Dem_DTCFilter.retrieveIt);
    Dem_DTCFilter.isNewFilterCriteria = TRUE;
}

void Dem_SetDTCFilterstartIterator(void){
    Dem_DtcIdIteratorNew(&Dem_DTCFilter.searchIt);
    Dem_DtcIdIteratorNew(&Dem_DTCFilter.retrieveIt);

    Dem_BitArrayClearAll(Dem_DTCFilterMatching, DEM_DTCID_ARRAYLENGTH);
}

Dem_ReturnSetFilterType Dem_SetDTCFilter(uint8 DTCStatusMask
   ,     Dem_DTCKindType DTCKind
   ,     Dem_DTCFormatType DTCFormat
   ,     Dem_DTCOriginType DTCOrigin
   ,     Dem_FilterWithSeverityType FilterWithSeverity
   ,     Dem_DTCSeverityType DTCSeverityMask
   ,     Dem_FilterForFDCType FilterForFaultDetectionCounter)
{
    Dem_ReturnSetFilterType returnVal = DEM_FILTER_ACCEPTED;

    DEM_ENTERLOCK_DCM();

    Dem_DtcFilterInit();

   if(!(Dem_EvMemIsDtcOriginValid(&DTCOrigin)
#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
    || (DTCOrigin == DEM_DTC_ORIGIN_PERMANENT_MEMORY)
#endif
    ))
   {
        DEM_DET(DEM_DET_APIID_DcmSetDTCFilter, DEM_E_WRONG_CONFIGURATION);
        returnVal = DEM_WRONG_FILTER;
   }

   if((DTCFormat == DEM_DTC_FORMAT_OBD) && (DEM_CFG_OBD == DEM_CFG_OBD_OFF))
   {
        returnVal = DEM_WRONG_FILTER;
   }

   if(returnVal != DEM_WRONG_FILTER)
   {
        Dem_DTCFilter.DTCStatusMask = (uint8) (DTCStatusMask & DEM_CFG_DTCSTATUS_AVAILABILITYMASK);
        Dem_DTCFilter.DTCKind = DTCKind;
        Dem_DTCFilter.DTCFormat = DTCFormat;
        Dem_DTCFilter.DTCOrigin = DTCOrigin;
        Dem_DTCFilter.FilterWithSeverity = FilterWithSeverity;
        Dem_DTCFilter.DTCSeverityMask = DTCSeverityMask;
        Dem_DTCFilter.FilterForFaultDetectionCounter = FilterForFaultDetectionCounter;

        Dem_DTCFilter.numberOfMatchingDTCs = 0;

        Dem_DtcFilterSyncInit();

        if(DTCFormat == DEM_DTC_FORMAT_OBD)
        {
#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
            rba_DemObdBasic_Dtc_SetDTCFilter(&Dem_DTCFilter, DTCOrigin);
#endif
        }
        else{
#if(DEM_CFG_REPORT_CHRONOLOGICAL_ORDER_HOOKS_ENABLED)
            if(!Dem_ChronoSortSetDTCFilter(&Dem_DTCFilter))
#endif
            {
                Dem_SetDTCFilterstartIterator();
            }
        }
   }

    DEM_EXITLOCK_DCM();

    return returnVal;
}

DEM_INLINE Dem_boolean_least Dem_DTCFilterMatchesStatus(uint8 DtcStatus, sint8 FaultDetectionCounter)
{
    Dem_boolean_least matches = TRUE;

   if(Dem_DTCFilter.DTCStatusMask != 0)
   {
        matches = matches && ((Dem_DTCFilter.DTCStatusMask & (DtcStatus & DEM_CFG_DTCSTATUS_AVAILABILITYMASK)) != 0u);
   }

   if(Dem_DTCFilter.FilterForFaultDetectionCounter == DEM_FILTER_FOR_FDC_YES)
   {
        matches = matches && ((FaultDetectionCounter > 0) && (FaultDetectionCounter < 127));
   }

    return matches;
}

Dem_boolean_least Dem_DTCFilterMatches(Dem_DtcIdType dtcId)
{
   uint8 DtcStatus = 0;
    Dem_boolean_least matches = TRUE;
   sint8 FaultDetectionCounter = 0;

   boolean DtcStatusIsValid;

   if(Dem_DTCFilter.DTCStatusMask != 0)
   {
        DtcStatus = Dem_DtcStatusByteRetrieveWithOrigin(dtcId, Dem_DTCFilter.DTCOrigin, &DtcStatusIsValid);
   }

   if(Dem_DTCFilter.DTCKind != DEM_DTC_KIND_ALL_DTCS)
   {
        matches = matches && (Dem_Cfg_Dtc_GetKind(dtcId) == Dem_DTCFilter.DTCKind);
   }

   if(!Dem_DtcUsesOrigin(dtcId, Dem_DTCFilter.DTCOrigin))
   {
        matches = FALSE;
   }

   if(Dem_DTCFilter.FilterWithSeverity == DEM_FILTER_WITH_SEVERITY_YES)
   {
        matches = matches && ((Dem_Cfg_Dtc_GetSeverity(dtcId) & Dem_DTCFilter.DTCSeverityMask) != 0);
   }

   if(Dem_DTCFilter.FilterForFaultDetectionCounter == DEM_FILTER_FOR_FDC_YES)
   {
        FaultDetectionCounter = Dem_DtcFaultDetectionRetrieve(dtcId);
   }

    matches = matches && Dem_DTCFilterMatchesStatus(DtcStatus, FaultDetectionCounter);

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
   matches = matches && rba_DemObdBasic_Dtc_DTCFilterMatches(dtcId, Dem_DTCFilter);
#endif

    return matches;
}

void Dem_DTCFilterStandardMainFunction(void){
   const sint32 epc = (sint32)DEM_DTC_FILTER_NUMBER_OF_EVENTS_PER_CYCLE; //to avoid MISRA warnings
   sint32 i = epc;
    Dem_DtcIdIterator searchItCopy;
    Dem_DtcIdType dtcId;
    Dem_boolean_least matches;
   sint32 numberOfEvents;

    DEM_ENTERLOCK_DCM();
    Dem_DTCFilter.isNewFilterCriteria = FALSE;
   searchItCopy = Dem_DTCFilter.searchIt;
    DEM_EXITLOCK_DCM();

    Dem_DtcFilterSyncCyclic();

   if(Dem_DtcIdIteratorIsValid(&searchItCopy))
   {
        while(i>0)
        {

            dtcId = Dem_DtcIdIteratorCurrent(&searchItCopy);

            if(!Dem_isDtcIdValid(dtcId))
            {
                return;
            }

            if(!Dem_DtcIsSuppressed(dtcId))
            {
                numberOfEvents = (sint32)Dem_DtcIdGetNumberOfEvents(dtcId);

                if((numberOfEvents > i) && (i != epc))
                {
                    break;
                }
                i = i - numberOfEvents;
                matches = Dem_DTCFilterMatches(dtcId);
            }
            else{
                i = i - 1;
                matches = FALSE;
            }

            DEM_ENTERLOCK_DCM();
            if(!Dem_DTCFilter.isNewFilterCriteria)
            {
                if(matches)
                {
                    Dem_BitArraySetBit(Dem_DTCFilterMatching, dtcId);
                    Dem_DTCFilter.numberOfMatchingDTCs++;
                }

                Dem_DtcIdIteratorNext(&Dem_DTCFilter.searchIt);
                searchItCopy = Dem_DTCFilter.searchIt;
            }
            else{
                i = 0;
            }
            DEM_EXITLOCK_DCM();
        }
   }
}

boolean Dem_IsStandardFilterFinished(const Dem_DtcIdIterator *it)
{
    return (!Dem_DtcIdIteratorIsValid(it));
}

void Dem_DTCFilterMainFunction(void){
#if DEM_CFG_REPORT_CHRONOLOGICAL_ORDER_HOOKS_ENABLED
   if(Dem_IsChronoSortEnabled())
   {
        Dem_ChronoSortMainFunction(&Dem_DTCFilter);
   }
   else
#endif
   {
        Dem_DTCFilterStandardMainFunction();
   }

#if(DEM_CFG_J1939DCM_READ_DTC_SUPPORT)
    Dem_J1939DcmDTCFilterMainFunction();
#endif
}

Dem_ReturnGetNextFilteredDTCType Dem_GetNextFilteredStandardDTCID(Dem_DtcIdType* dtcId, uint32* DTC, uint8* DTCStatus, sint8* DTCFaultDetectionCounter)
{
   uint16_least i = DEM_DTC_FILTER_RETRIEVE_NUMBER_OF_DTCS;
   uint8 localDTCStatus;
   sint8 FaultDetectionCounter = 0;

   while(i > 0u)
   {
        if(!Dem_DtcIdIteratorIsValid(&Dem_DTCFilter.retrieveIt))
        {
            return DEM_FILTERED_NO_MATCHING_DTC;
        }

        if(Dem_DTCFilter.retrieveIt == Dem_DTCFilter.searchIt)
        {
            return DEM_FILTERED_PENDING;
        }

        *dtcId = Dem_DtcIdIteratorCurrent(&Dem_DTCFilter.retrieveIt);

        if(Dem_BitArrayIsBitSet(Dem_DTCFilterMatching, *dtcId))
        {
            if(!Dem_DtcFilterSyncGetDtcStatusByte(*dtcId, Dem_DTCFilter.DTCOrigin, &localDTCStatus))
            {
                return DEM_FILTERED_PENDING;
            }

            if(Dem_DTCFilter.FilterForFaultDetectionCounter == DEM_FILTER_FOR_FDC_YES)
            {
                FaultDetectionCounter = Dem_DtcFaultDetectionRetrieve(*dtcId);
            }

            if(Dem_DTCFilterMatchesStatus(localDTCStatus, FaultDetectionCounter))
            {
                if(DTCStatus != NULL_PTR)
                {
                    *DTCStatus = (uint8) (localDTCStatus & DEM_CFG_DTCSTATUS_AVAILABILITYMASK);
                }

                if(DTCFaultDetectionCounter != NULL_PTR)
                {
                    *DTCFaultDetectionCounter = FaultDetectionCounter;
                }

                *DTC = Dem_GetDtcCode(*dtcId);

                Dem_DtcIdIteratorNext(&Dem_DTCFilter.retrieveIt);
                return DEM_FILTERED_OK;
            }
        }
        i--;
        Dem_DtcIdIteratorNext(&Dem_DTCFilter.retrieveIt);
   }
    return DEM_FILTERED_PENDING;
}

static Dem_ReturnGetNextFilteredDTCType Dem_GetNextFilteredDTCID(Dem_DtcIdType* dtcId, uint32* DTC, uint8* DTCStatus, sint8* DTCFaultDetectionCounter)
{
#if DEM_CFG_REPORT_CHRONOLOGICAL_ORDER_HOOKS_ENABLED
   if(Dem_IsChronoSortEnabled())
   {
        return Dem_ChronoSortGetNextFilteredDTCID(dtcId, DTC, DTCStatus);
   }
   else
#endif
   {
        return Dem_GetNextFilteredStandardDTCID(dtcId, DTC, DTCStatus, DTCFaultDetectionCounter);
   }
}

Dem_ReturnGetNextFilteredDTCType Dem_GetNextFilteredDTC(uint32* DTC, uint8* DTCStatus)
{
    Dem_DtcIdType dtcId;
    Dem_ReturnGetNextFilteredDTCType retVal = DEM_FILTERED_NO_MATCHING_DTC;

#if DEM_CFG_REPORT_CHRONOLOGICAL_ORDER_HOOKS_ENABLED
   if(Dem_IsChronoSortEnabled() || (Dem_DtcIdIteratorIsValid(&Dem_DTCFilter.retrieveIt)))
#else
   if(Dem_DtcIdIteratorIsValid(&Dem_DTCFilter.retrieveIt))
#endif
   {
        retVal = Dem_GetNextFilteredDTCID (&dtcId, DTC, DTCStatus, NULL_PTR);
   }
#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
   else{
        retVal = rba_DemObdBasic_Dtc_GetNextFilteredDTC(&Dem_DTCFilter, DTC, DTCStatus);
   }
#endif

    return retVal;
}

Dem_ReturnGetNextFilteredDTCType Dem_GetNextFilteredDTCAndFDC(uint32* DTC, sint8* DTCFaultDetectionCounter)
{
   Dem_DtcIdType dtcId;
   Dem_ReturnGetNextFilteredDTCType retVal;

   DEM_ASSERT(((DTC != NULL_PTR) && (DTCFaultDetectionCounter != NULL_PTR)),DEM_DET_APIID_GETNEXTFILTEREDDTCANDFDC, DEM_E_PARAM_POINTER);

   retVal = Dem_GetNextFilteredDTCID (&dtcId, DTC, NULL_PTR, DTCFaultDetectionCounter);

   return retVal;
}

Dem_ReturnGetNextFilteredDTCType Dem_GetNextFilteredDTCAndSeverity (uint32* DTC, uint8* DTCStatus, Dem_DTCSeverityType* DTCSeverity, uint8* DTCFunctionalUnit)
{
   Dem_DtcIdType dtcId;
   Dem_ReturnGetNextFilteredDTCType retVal;

   retVal = Dem_GetNextFilteredDTCID (&dtcId, DTC, DTCStatus, NULL_PTR);
   if(retVal == DEM_FILTERED_OK)
   {
   	*DTCSeverity = Dem_Cfg_Dtc_GetSeverity(dtcId);
   	*DTCFunctionalUnit = Dem_Cfg_Dtc_GetFunc_Unit(dtcId);
   }
   return retVal;
}

Dem_ReturnGetNumberOfFilteredDTCType Dem_GetNumberOfStandardFilteredDTC(uint16* NumberOfFilteredDTC)
{
    *NumberOfFilteredDTC = Dem_DTCFilter.numberOfMatchingDTCs;
    return DEM_NUMBER_OK;
}

Dem_ReturnGetNumberOfFilteredDTCType Dem_GetNumberOfFilteredDTC(uint16* NumberOfFilteredDTC)
{
    Dem_ReturnGetNumberOfFilteredDTCType retVal;

   if(Dem_DtcIdIteratorIsValid(&Dem_DTCFilter.searchIt))
   {
        return DEM_NUMBER_PENDING;
   }

#if(DEM_CFG_REPORT_CHRONOLOGICAL_ORDER_HOOKS_ENABLED)
   if(Dem_IsChronoSortEnabled())
   {
        retVal = Dem_ChronoSortGetNumberOfFilteredDTC(NumberOfFilteredDTC);
   }
   else
#endif
   {
        retVal = Dem_GetNumberOfStandardFilteredDTC(NumberOfFilteredDTC);
   }

    return retVal;
}
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
