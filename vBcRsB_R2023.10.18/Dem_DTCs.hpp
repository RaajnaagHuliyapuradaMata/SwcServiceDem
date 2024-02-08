

#ifndef DEM_DTCS_H
#define DEM_DTCS_H

#include "Dem_Types.hpp"
#include "Dem_Array.hpp"
#include "Dem_BitArray.hpp"
#include "rba_DiagLib_Bits8.hpp"
#include "Dem_Cfg_DtcId.hpp"
#include "Dem_Cfg_DTC_DataStructures.hpp"
#include "Dem_Cfg_Main.hpp"
#include "Dem_Mapping.hpp"
#include "Dem_ISO14229Byte.hpp"
#include "Dem_Events.hpp"
#include "Dem_DTCStatusByte.hpp"
#include "Dem_Cfg_Events_DataStructures.hpp"

#include "Dem_Helpers.hpp"
#include "Dem_EvMem.hpp"

#define DEM_DTC_SETTING_ENABLED     FALSE
#define DEM_DTC_SETTING_DISABLED    TRUE

typedef struct{
   Dem_DtcStateType state;
}Dem_DtcState;

#define DEM_DTCS_NVSTORAGE_BP    2u
#define DEM_DTCS_ALTERNATIVEDTC_FLAG_BP    3u

#define DEM_DTCS_SEVERITYMASK    0xE0u
#define DEM_DTCS_KINDMASK        0x03u
#define DEM_DTCS_NVSTORAGEMASK   ((uint8)(1u<<DEM_DTCS_NVSTORAGE_BP))
#define DEM_DTCS_ALTERNATIVEDTC_FLAG   ((uint8)(1u<<DEM_DTCS_ALTERNATIVEDTC_FLAG_BP))

#define DEM_DTCS_INIT8(KIND, SEVERITY, NVSTORAGE, FUNC_UNIT, INDEXOF_ALTERNATIVE_DTCID) \
{   ((KIND) & (DEM_DTCS_KINDMASK))|((SEVERITY) & (DEM_DTCS_SEVERITYMASK)) | ((uint8)(((NVSTORAGE) & (0x01u)) << DEM_DTCS_NVSTORAGE_BP)) | ((uint8)((DEM_BOOL2BIT(INDEXOF_ALTERNATIVE_DTCID) & (0x01u)) << DEM_DTCS_ALTERNATIVEDTC_FLAG_BP)) \
   ,(FUNC_UNIT) \
}

#if(DEM_CFG_OBD == DEM_CFG_OBD_ON) && (DEM_CFG_OBD_DTC_CONFIG != DEM_CFG_OBD_DTC_CONFIG_OFF)
#define DEM_DTCS_INIT16(OBDCODE) \
{   (OBDCODE) \
}
#endif

#define DEM_DTCS_INIT32(CODE) \
{   (CODE) \
}

typedef struct{
   uint8 kind_severity_storage;
   uint8 Functional_Unit;
}Dem_DtcParam8;

#if(DEM_CFG_OBD == DEM_CFG_OBD_ON) && (DEM_CFG_OBD_DTC_CONFIG != DEM_CFG_OBD_DTC_CONFIG_OFF)
typedef struct{
   uint16 ObdCode;
}Dem_DtcParam16;
#endif

typedef struct{
   Dem_DtcCodeType code;
}Dem_DtcParam32;

typedef struct{
    Dem_DtcCodeType AltDtccode;
    Dem_DtcCodeType Dtccode;
}Dem_DtcAltParam;

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

    DEM_ARRAY_DECLARE(Dem_DtcState, Dem_AllDTCsState, DEM_DTCID_ARRAYLENGTH);

#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.hpp"

#if(DEM_CFG_ALTERNATIVEDTC == DEM_CFG_ALTERNATIVEDTC_ON)
    extern boolean Dem_AlternativeDTCEnabled;
#endif

#define DEM_STOP_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

#if(DEM_CFG_ALTERNATIVEDTC == DEM_CFG_ALTERNATIVEDTC_ON)
    DEM_ARRAY_DECLARE_CONST(Dem_DtcAltParam, Dem_AllAlternativeDTCsParam, DEM_ALTERNATIVE_DTCCODE_ARRAYLENGTH);
#endif

#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

DEM_INLINE Dem_boolean_least Dem_DtcIsSuppressed (Dem_DtcIdType dtcId)
{
#if(DEM_CFG_SUPPRESSION != DEM_NO_SUPPRESSION)
    return DEM_DTCSTATE_ISBITSET (Dem_AllDTCsState[dtcId].state, DEM_DTC_BP_STATE_SUPPRESSED);
#else
    DEM_UNUSED_PARAM(dtcId);
    return FALSE;
#endif
}

DEM_INLINE Dem_boolean_least Dem_DtcIsSuppressedDirectly (Dem_DtcIdType dtcId)
{
#if((DEM_CFG_SUPPRESSION == DEM_DTC_SUPPRESSION) || (DEM_CFG_SUPPRESSION == DEM_EVENT_AND_DTC_SUPPRESSION))
    return DEM_DTCSTATE_ISBITSET (Dem_AllDTCsState[dtcId].state, DEM_DTC_BP_STATE_SUPPRESSED_DIRECTLY);
#else
    DEM_UNUSED_PARAM(dtcId);
    return FALSE;
#endif
}

DEM_INLINE Dem_boolean_least Dem_DtcIsSupported (Dem_DtcIdType dtcID)
{
    return (Dem_isDtcIdValid(dtcID)
            && (!Dem_DtcIsSuppressed(dtcID))
    );
}

#if((DEM_CFG_SUPPRESSION == DEM_EVENT_SUPPRESSION) || (DEM_CFG_SUPPRESSION == DEM_EVENT_AND_DTC_SUPPRESSION))
DEM_INLINE void Dem_DtcHandleEventSuppression (Dem_DtcIdType dtcId, Dem_boolean_least eventUnsuppressed)
{
    DEM_ASSERT_ISLOCKED();

   if(!Dem_DtcIsSuppressedDirectly(dtcId))
   {
        Dem_EventIdListIterator it;

        if(!eventUnsuppressed)
        {
            for(Dem_EventIdListIteratorNewFromDtcId(&it, dtcId);
                    Dem_EventIdListIteratorIsValid(&it);
                    Dem_EventIdListIteratorNext(&it))
            {
                if( !Dem_EvtIsSuppressed(Dem_EventIdListIteratorCurrent(&it)) )
                {
                    eventUnsuppressed = TRUE;
                    break;
                }
            }
        }

        DEM_DTCSTATE_OVERWRITEBIT (&Dem_AllDTCsState[dtcId].state, DEM_DTC_BP_STATE_SUPPRESSED, !eventUnsuppressed);
   }
}
#endif

#if((DEM_CFG_SUPPRESSION == DEM_DTC_SUPPRESSION) || (DEM_CFG_SUPPRESSION == DEM_EVENT_AND_DTC_SUPPRESSION))
DEM_INLINE void Dem_DtcSuppressionApply (Dem_DtcIdType dtcId, Dem_boolean_least setBit)
{
   DEM_ENTERLOCK_MON();

   DEM_DTCSTATE_OVERWRITEBIT (&Dem_AllDTCsState[dtcId].state, DEM_DTC_BP_STATE_SUPPRESSED_DIRECTLY, setBit);

   if(setBit)
   {
       DEM_DTCSTATE_SETBIT (&Dem_AllDTCsState[dtcId].state, DEM_DTC_BP_STATE_SUPPRESSED);
   }
   else
   {
# if(DEM_CFG_SUPPRESSION == DEM_EVENT_AND_DTC_SUPPRESSION)
       Dem_DtcHandleEventSuppression (dtcId, FALSE);
# else
       DEM_DTCSTATE_CLEARBIT (&Dem_AllDTCsState[dtcId].state, DEM_DTC_BP_STATE_SUPPRESSED);
# endif
   }

   DEM_EXITLOCK_MON();
}
#endif

#if((DEM_CFG_SUPPRESSION == DEM_DTC_SUPPRESSION) || (DEM_CFG_SUPPRESSION == DEM_EVENT_AND_DTC_SUPPRESSION))
DEM_INLINE Dem_boolean_least Dem_IsEventMemoryEntryExistForDTC (Dem_DtcIdType dtcId)
{
   uint8 DtcStatusByte = Dem_DtcStatusByteRetrieve(dtcId);

   if(Dem_ISO14229ByteIsTestFailed(DtcStatusByte) || Dem_ISO14229ByteIsTestFailedSLC(DtcStatusByte))
   {
   	return TRUE;
   }
   else
   {
   	return FALSE;
   }
}
#endif

DEM_INLINE Dem_DtcCodeType Dem_GetDtcCode (Dem_DtcIdType dtcId)
{
#if(DEM_CFG_ALTERNATIVEDTC == DEM_CFG_ALTERNATIVEDTC_ON)
   if(Dem_Cfg_Dtc_GetDtcCode_Is_Index(dtcId))
   {
        if(Dem_AlternativeDTCEnabled)
        {
            return Dem_AllAlternativeDTCsParam[Dem_Cfg_Dtc_GetDtcCode(dtcId)].AltDtccode;
        }
        else{
            return Dem_AllAlternativeDTCsParam[Dem_Cfg_Dtc_GetDtcCode(dtcId)].Dtccode;
        }
   }
   else
#endif
   {
        return Dem_Cfg_Dtc_GetDtcCode(dtcId);
   }
}

#if(DEM_CFG_OBD == DEM_CFG_OBD_ON) && (DEM_CFG_OBD_DTC_CONFIG != DEM_CFG_OBD_DTC_CONFIG_OFF)

#endif

Dem_DtcIdType Dem_DtcIdFromDtcCode (Dem_DtcCodeType dtcCode);

#if(DEM_CFG_CHECKAPICONSISTENCY == TRUE)

Std_ReturnType Dem_GetDTCOfEvent_GeneralEvtInfo(Dem_EventIdType EventId, Dem_DTCFormatType DTCFormat, uint32* DTCOfEvent);
#endif

DEM_INLINE Dem_boolean_least Dem_EventUsesOrigin (Dem_EventIdType eventId, Dem_DTCOriginType origin)
{
   if(   ((origin == DEM_DTC_ORIGIN_PRIMARY_MEMORY) && Dem_EvtParam_GetEventIsStoredInPrimary(eventId))
   		|| ((origin == DEM_DTC_ORIGIN_SECONDARY_MEMORY) && Dem_EvtParam_GetEventIsStoredInSecondary(eventId))
   		|| ((origin == DEM_DTC_ORIGIN_MIRROR_MEMORY) && Dem_EvtParam_GetEventIsStoredInMirror(eventId))

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
   		|| ((origin == DEM_DTC_ORIGIN_PERMANENT_MEMORY) && (Dem_Cfg_Dtc_GetKind(Dem_DtcIdFromEventId(eventId)) == DEM_DTC_KIND_EMISSION_REL_DTCS))
#endif

   )
   {
   	return TRUE;
   }
   return FALSE;
}

DEM_INLINE Dem_boolean_least Dem_DtcUsesOrigin (Dem_DtcIdType dtcId, Dem_DTCOriginType origin)
{
    Dem_EventIdType eventId = Dem_DtcIdGetFirstEventId(dtcId);
    return Dem_EventUsesOrigin(eventId, origin);
}

void Dem_DtcSetDTCSetting (Dem_DtcIdType dtcId, Dem_boolean_least setBit);

DEM_INLINE Dem_boolean_least Dem_DtcIsDTCSettingEnabled(Dem_DtcIdType dtcId)
{
   return (!(DEM_DTCSTATE_ISBITSET (Dem_AllDTCsState[dtcId].state, DEM_DTC_BP_GROUP_DTCSETTING_DISABLED)));
}

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

Dem_boolean_least Dem_IsEventEnabledByDtcSetting(Dem_EventIdType EventId);

DEM_INLINE Dem_boolean_least Dem_IsEventReportingEnabledByDtcSetting(Dem_EventIdType EventId)
{
#if(DEM_CFG_DTCSETTINGBLOCKSREPORTING)
    return Dem_IsEventEnabledByDtcSetting(EventId);
#else
    DEM_UNUSED_PARAM(EventId);
    return TRUE;
#endif
}

DEM_INLINE Dem_boolean_least Dem_IsEventStorageEnabledByDtcSetting(Dem_EventIdType EventId)
{
#if(DEM_CFG_DTCSETTINGBLOCKSREPORTING)
    DEM_UNUSED_PARAM(EventId);
    return TRUE;
#else
    return Dem_IsEventEnabledByDtcSetting(EventId);
#endif
}

sint8 Dem_DtcFaultDetectionRetrieve (Dem_DtcIdType dtcId);

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#endif
