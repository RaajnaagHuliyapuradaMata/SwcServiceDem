#include "Std_Types.hpp"

#include "Dem.hpp"
#include "Rte_Dem.hpp"
#include "Dem_EvMemGen.hpp"
#include "Dem_Main.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
#if( DEM_CFG_EVMEMGENERIC_SUPPORTED != FALSE )
Dem_ReturnGetDTCByOccurrenceTimeType Dem_GetDTCByOccurrenceTime(Dem_DTCRequestType DTCRequest, Dem_DTCKindType DTCKind, uint32* DTC)
{
      Dem_DtcIdType DtcId;

      if(!Dem_OpMoIsInitialized())
      {
         DEM_DET(DEM_DET_APIID_GETDTCBYOCCURRENCETIME, DEM_E_UNINIT);
         return DEM_OCCURR_FAILED;
      }

      if((DTCRequest != DEM_FIRST_FAILED_DTC) &&
            (DTCRequest != DEM_MOST_RECENT_FAILED_DTC) &&
            (DTCRequest != DEM_FIRST_DET_CONFIRMED_DTC) &&
            (DTCRequest != DEM_MOST_REC_DET_CONFIRMED_DTC))
      {
         DEM_DET(DEM_DET_APIID_GETDTCBYOCCURRENCETIME, DEM_E_WRONG_CONFIGURATION);
         return DEM_OCCURR_FAILED;
      }
      if(DTC==NULL_PTR)
      {
          return DEM_OCCURR_FAILED;
      }

      if(DTCKind != DEM_DTC_KIND_ALL_DTCS)
      {
         DEM_DET(DEM_DET_APIID_GETDTCBYOCCURRENCETIME, DEM_E_WRONG_CONFIGURATION);
         return DEM_OCCURR_WRONG_DTCKIND;
      }

      DtcId = Dem_EvMemGenGetDtcIdByOccIndex(DTCRequest);

      if(!Dem_isDtcIdValid(DtcId))
      {
         return DEM_OCCURR_FAILED;
      }

      *DTC = (uint32)Dem_GetDtcCode(DtcId);
      return DEM_OCCURR_OK;
   }
#endif

Std_ReturnType Dem_GetEventMemoryOverflow(Dem_DTCOriginType DTCOrigin, boolean* OverflowIndication)
{

   if(Dem_LibGetParamBool(DEM_CFG_EVMEMGENERIC_SUPPORTED))
   {

       DEM_ENTRY_CONDITION_CHECK_DEM_INITIALIZED(DEM_DET_APIID_GETEVENTMEMORYOVERFLOW,E_NOT_OK);
       DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(OverflowIndication,DEM_DET_APIID_GETEVENTMEMORYOVERFLOW,E_NOT_OK);

      if(!Dem_EvMemIsDtcOriginValid (&DTCOrigin))
      {
         DEM_DET(DEM_DET_APIID_GETEVENTMEMORYOVERFLOW, DEM_E_WRONG_CONFIGURATION);
         return E_NOT_OK;
      }

      *OverflowIndication = Dem_EvMemGenIsOverflow(DTCOrigin);
      return E_OK;
   }
   else{
      DEM_DET(DEM_DET_APIID_GETEVENTMEMORYOVERFLOW, DEM_E_WRONG_CONDITION);
      return E_NOT_OK;
   }
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

