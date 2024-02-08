#ifndef DEM_PRV_J1939DCM_H
#define DEM_PRV_J1939DCM_H

#define DEM_CFG_AMBER_WARNING_LAMP  0u

#include "Dem_BitArray.hpp"
#include "Dem_Types.hpp"
#include "Dem_Array.hpp"
#include "Dem_Mapping.hpp"

#if(DEM_CFG_J1939DCM != DEM_CFG_J1939DCM_OFF)

#include "Dem_Mapping.hpp"

#define DEM_J1939DCM_AMBER_CONTINOUS     0x040Cu
#define DEM_J1939DCM_AMBER_SLOW_FLASH    0x0400u
#define DEM_J1939DCM_AMBER_FAST_FLASH    0x0404u
#define DEM_J1939DCM_AMBER_OFF           0x0000u

#if(DEM_CFG_J1939DCM_READ_DTC_SUPPORT)

typedef struct{
   boolean isNewFilterCriteria;
    Dem_J1939DcmDTCStatusFilterType DTCStatusFilter;
    Dem_DTCKindType DTCKind;
   uint8 node;
    Dem_J1939DcmLampStatusType* LampStatus;
   uint16 numberOfMatchingDTCs;
    Dem_DtcIdListIterator2 searchIt, retrieveIt;
}Dem_J1939DcmDTCFilterState;

#endif

#if(DEM_CFG_J1939DCM_DM31_SUPPORT)

typedef struct{
   uint8 node;
    Dem_DtcIdListIterator2 retrieveIt;
}Dem_J1939DcmDTCRetrieveState;

#endif

#if(DEM_CFG_J1939DCM_FREEZEFRAME_SUPPORT || DEM_CFG_J1939DCM_EXPANDED_FREEZEFRAME_SUPPORT)

typedef struct{
    Dem_J1939DcmSetFreezeFrameFilterType FreezeFrameKind;
   uint8 node;
}Dem_J1939FreezeFrameFilterState;

#endif

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"
#if(DEM_CFG_J1939DCM_READ_DTC_SUPPORT)
    extern Dem_J1939DcmDTCFilterState Dem_J1939DcmDTCFilter;
    DEM_BITARRAY_DECLARE(Dem_J1939DcmDTCFilterMatching, DEM_DTCID_ARRAYLENGTH);
#endif

#if(DEM_CFG_J1939DCM_DM31_SUPPORT)
    extern Dem_J1939DcmDTCRetrieveState Dem_J1939DcmDTCRetrieve;
#endif

#if(DEM_CFG_J1939DCM_FREEZEFRAME_SUPPORT || DEM_CFG_J1939DCM_EXPANDED_FREEZEFRAME_SUPPORT)
   extern Dem_J1939FreezeFrameFilterState Dem_J1939FreezeFrameFilter;
#endif
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

typedef struct{
    Dem_DtcCodeType code;
}Dem_J1939DtcParam32;

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

DEM_ARRAY_DECLARE_CONST(Dem_J1939DtcParam32, Dem_AllJ1939DTCsParam32, DEM_DTCID_ARRAYLENGTH);

#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

uint8 Dem_J1939GetOccurrenceCounterByDtcId(Dem_DtcIdType dtcId);
#if(DEM_CFG_EVT_INDICATOR != DEM_CFG_EVT_INDICATOR_OFF)
Dem_J1939DcmLampStatusType Dem_J1939DcmGetLampStatus(void);
#endif

#if(DEM_CFG_J1939DCM_READ_DTC_SUPPORT)
void Dem_J1939DcmDtcFilterInit(void);
#endif

DEM_INLINE Dem_DtcCodeType Dem_J1939DtcGetCode (Dem_DtcIdType dtcId)
{
    return Dem_AllJ1939DTCsParam32[dtcId].code;
}

#if(DEM_CFG_J1939DCM_CLEAR_SUPPORT != DEM_CFG_J1939DCM_OFF)
Dem_ReturnClearDTCType Dem_J1939DcmClearDTCBody(Dem_J1939DcmSetClearFilterType DTCTypeFilter , uint8 node);
void Dem_J1939DcmClearDTCMainFunction(void);
#endif

#if(DEM_CFG_J1939DCM_FREEZEFRAME_SUPPORT || DEM_CFG_J1939DCM_EXPANDED_FREEZEFRAME_SUPPORT)
void Dem_J1939DcmFreezeFrameFilterInit(void);
#endif

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#if(DEM_CFG_J1939DCM_FREEZEFRAME_SUPPORT || DEM_CFG_J1939DCM_EXPANDED_FREEZEFRAME_SUPPORT)

DEM_INLINE Dem_boolean_least Dem_J1939IsFreezeFrameKindValid (Dem_J1939DcmSetFreezeFrameFilterType FreezeFrameKind)
{
    Dem_boolean_least DemJ1939FFKindValid = FALSE;

#if(DEM_CFG_J1939DCM_FREEZEFRAME_SUPPORT)
   if(FreezeFrameKind == DEM_J1939DCM_FREEZEFRAME)
   {
        DemJ1939FFKindValid = TRUE;
   }
   else
#endif
#if(DEM_CFG_J1939DCM_EXPANDED_FREEZEFRAME_SUPPORT)
        if(FreezeFrameKind == DEM_J1939DCM_EXPANDED_FREEZEFRAME)
        {
            DemJ1939FFKindValid = TRUE;
        }
        else
#endif
        {

        }

    return DemJ1939FFKindValid;
}

#endif

#endif

#endif

