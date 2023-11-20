
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef DEM_CUSTOMSTATUSBYTE_H
#define DEM_CUSTOMSTATUSBYTE_H

#include "Dem_Events.hpp"
#include "Dem_Dtcs.hpp"
#include "Dem_ISO14229Byte.hpp"

#if(DEM_CFG_CUSTOMIZABLEDTCSTATUSBYTE)

#define DEM_CUSTBYTE_EVENT_UNAVAILABLE                   (0x00u)
#define DEM_CUSTBYTE_NEW_OPERATIONCYCLE_SETMASK          (DEM_ISO14229_BM_TESTNOTCOMPLETE_TOC)
#define DEM_CUSTBYTE_NEW_OPERATIONCYCLE_CLEARMASK        (DEM_ISO14229_BM_TESTFAILED_TOC)

DEM_INLINE void Dem_EvtSt_CustomInitialization (Dem_EventIdType EventId, Dem_UdsStatusByteType *statusByte)
{
    DEM_UNUSED_PARAM(EventId);
    *statusByte = (Dem_UdsStatusByteType)DEM_ISO14229BYTE_INITVALUE;
}

DEM_INLINE void Dem_EvtSt_CustomFailed(Dem_EventIdType EventId, Dem_UdsStatusByteType *statusByte)
{
   if(Dem_IsEventEnabledByDtcSetting(EventId))
   {
        Dem_ISO14229ByteSetTestFailed (statusByte, TRUE);
        Dem_ISO14229ByteSetTestFailedTOC (statusByte, TRUE);
        Dem_ISO14229ByteSetTestFailedSLC (statusByte, TRUE);
        Dem_ISO14229ByteSetTestCompleteTOC (statusByte, TRUE);
        Dem_ISO14229ByteSetTestCompleteSLC (statusByte, TRUE);
        Dem_ISO14229ByteSetPendingDTC (statusByte, TRUE);
   }
}

DEM_INLINE void Dem_EvtSt_CustomPassed(Dem_EventIdType EventId, Dem_UdsStatusByteType *statusByte)
{
   if(Dem_IsEventEnabledByDtcSetting(EventId))
   {
        Dem_ISO14229ByteSetTestFailed (statusByte, FALSE);
        Dem_ISO14229ByteSetTestCompleteTOC (statusByte, TRUE);
        Dem_ISO14229ByteSetTestCompleteSLC (statusByte, TRUE);
   }
}

DEM_INLINE void Dem_EvtSt_CustomResetEventStatus(Dem_EventIdType EventId, Dem_UdsStatusByteType *statusByte)
{
   if(Dem_IsEventEnabledByDtcSetting(EventId))
   {
        Dem_ISO14229ByteSetTestFailed(statusByte, FALSE);
   }
}

DEM_INLINE void Dem_EvtSt_CustomEvtAvailable(Dem_EventIdType EventId, Dem_UdsStatusByteType *statusByte)
{
    DEM_UNUSED_PARAM(EventId);
    *statusByte = (Dem_UdsStatusByteType)DEM_ISO14229BYTE_INITVALUE;
}

DEM_INLINE void Dem_EvtSt_CustomEvtNotAvailable(Dem_EventIdType EventId, Dem_UdsStatusByteType *statusByte)
{
    DEM_UNUSED_PARAM(EventId);
    *statusByte = DEM_CUSTBYTE_EVENT_UNAVAILABLE;
}

DEM_INLINE void Dem_EvtSt_CustomClear(Dem_EventIdType EventId, Dem_UdsStatusByteType *statusByte)
{
    *statusByte = (Dem_UdsStatusByteType)DEM_ISO14229BYTE_INITVALUE;
   if(!Dem_IsEventEnabledByDtcSetting(EventId))
   {
        Dem_ISO14229ByteSetWarningIndicatorRequested(statusByte,Dem_ISO14229ByteIsWarningIndicatorRequested(Dem_EvtGetIsoByte(EventId)));
   }
}

DEM_INLINE void Dem_EvtSt_CustomClear_OnlyThisCycleAndReadiness(Dem_EventIdType EventId, Dem_UdsStatusByteType *statusByte)
{
}

DEM_INLINE void Dem_EvtSt_CustomNewOperationCycle(Dem_EventIdType EventId, Dem_UdsStatusByteType *statusByte)
{
   if(Dem_IsEventEnabledByDtcSetting(EventId))
   {
        if(Dem_ISO14229ByteIsTestCompleteTOC(*statusByte) && !Dem_ISO14229ByteIsTestFailedTOC(*statusByte))
        {
            Dem_ISO14229ByteSetPendingDTC(statusByte, FALSE);
        }

        Dem_ISO14229ByteSetTestFailedTOC (statusByte, FALSE);
        Dem_ISO14229ByteSetTestCompleteTOC (statusByte, FALSE);
   }
}

DEM_INLINE void Dem_EvtSt_CustomIndicatorOn(Dem_EventIdType EventId, Dem_UdsStatusByteType *statusByte)
{
   if(Dem_IsEventEnabledByDtcSetting(EventId))
   {
        Dem_ISO14229ByteSetWarningIndicatorRequested(statusByte, TRUE);
   }
}

DEM_INLINE void Dem_EvtSt_CustomIndicatorOff(Dem_EventIdType EventId, Dem_UdsStatusByteType *statusByte)
{
   if(Dem_IsEventEnabledByDtcSetting(EventId))
   {
        Dem_ISO14229ByteSetWarningIndicatorRequested(statusByte, FALSE);
   }
}

DEM_INLINE void Dem_EvtSt_CustomDTCSettingOn(Dem_EventIdType EventId, Dem_UdsStatusByteType *statusByte)
{
    Dem_ISO14229ByteSetWarningIndicatorRequested(statusByte,Dem_ISO14229ByteIsWarningIndicatorRequested(Dem_EvtGetIsoByte(EventId)));
}

DEM_INLINE void Dem_EvtSt_CustomConfirmation(Dem_EventIdType EventId, Dem_UdsStatusByteType *statusByte)
{
   if(Dem_IsEventEnabledByDtcSetting(EventId))
   {
        Dem_ISO14229ByteSetConfirmedDTC(statusByte, TRUE);
   }
}

DEM_INLINE void Dem_EvtSt_CustomAging(Dem_EventIdType EventId, Dem_UdsStatusByteType *statusByte)
{
    DEM_UNUSED_PARAM(EventId);
    Dem_ISO14229ByteSetConfirmedDTC(statusByte, FALSE);
    //Dem_ISO14229ByteSetPendingDTC(statusByte, FALSE);
}

DEM_INLINE void Dem_EvtSt_CustomSetImmediateAging(Dem_EventIdType EventId, Dem_UdsStatusByteType *statusByte)
{
    DEM_UNUSED_PARAM(EventId);
    Dem_ISO14229ByteSetConfirmedDTC(statusByte, FALSE);
    //Dem_ISO14229ByteSetPendingDTC(statusByte, FALSE);
}

DEM_INLINE void Dem_EvtSt_CustomDisplacement(Dem_EventIdType EventId, Dem_UdsStatusByteType *statusByte)
{
    DEM_UNUSED_PARAM(EventId);
    DEM_UNUSED_PARAM(statusByte);
}

DEM_INLINE void Dem_EvtSt_CustomEvCombinationReplacement(Dem_EventIdType EventId, Dem_UdsStatusByteType *statusByte)
{
    DEM_UNUSED_PARAM(EventId);
    Dem_ISO14229ByteSetConfirmedDTC(statusByte, FALSE);
}

DEM_INLINE void Dem_EvtSt_CustomSetPending(Dem_EventIdType EventId, Dem_UdsStatusByteType *statusByte, Dem_boolean_least newValue)
{
   if(Dem_IsEventEnabledByDtcSetting(EventId))
   {
        Dem_ISO14229ByteSetPendingDTC(statusByte, newValue);
   }
}

#endif

#endif

