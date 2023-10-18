#include "Std_Types.hpp"

#include "Dem_Dcm.hpp"
#include "Dem_DTCGroup.hpp"
#include "Dem_DTCs.hpp"

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
DEM_ARRAY_DEFINE_CONST(Dem_DtcGroupParam, Dem_AllDTCGroupsParam, DEM_DTCGROUPID_ARRAYLENGTH, DEM_CFG_DTCGROUPPARAMS);
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"
DemControlDtcGroupType Dem_DtcGroupDisabledFlag = FALSE;
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

DEM_INLINE void Dem_DtcGroupApplyDTCSetting(Dem_DTCGroupType DTCGroup, uint8 groupId, boolean newDtcSettingState)
{
    Dem_DtcIdListIterator dtcIt;
    Dem_boolean_least AnyDTCSettingDisabled = FALSE;
    Dem_DtcIdType LockCounter = 0;

   if(DTCGroup != DEM_DTC_GROUP_EMISSION_REL_DTCS)
   {
        DEM_ENTERLOCK_MON();

        for(Dem_DtcIdListIteratorNewFromDtcGroup(&dtcIt, groupId); Dem_DtcIdListIteratorIsValid(&dtcIt);
                Dem_DtcIdListIteratorNext(&dtcIt))
        {
            Dem_DtcSetDTCSetting(Dem_DtcIdListIteratorCurrent(&dtcIt), newDtcSettingState);

            LockCounter++;
            if(LockCounter >= DEM_NUMBER_OF_DTCS_TO_PROCESS_PER_LOCK)
            {
                DEM_EXITLOCK_MON();

                LockCounter = 0;
                DEM_ENTERLOCK_MON();
            }
        }
        DEM_EXITLOCK_MON();
        Dem_SetDtcGroupSettingFlag(newDtcSettingState);
   }
   else{
        Dem_DtcIdIterator dtcId = DEM_DTCIDITERATOR_NEW();

        DEM_ENTERLOCK_MON();

        for(Dem_DtcIdIteratorNew(&dtcId); Dem_DtcIdIteratorIsValid(&dtcId); Dem_DtcIdIteratorNext(&dtcId))
        {
            if(Dem_Cfg_Dtc_GetKind(Dem_DtcIdIteratorCurrent(&dtcId)) == DEM_DTC_KIND_EMISSION_REL_DTCS)
            {
                Dem_DtcSetDTCSetting(Dem_DtcIdIteratorCurrent(&dtcId), newDtcSettingState);

                LockCounter++;
                if(LockCounter >= DEM_NUMBER_OF_DTCS_TO_PROCESS_PER_LOCK)
                {
                    DEM_EXITLOCK_MON();

                    LockCounter = 0;
                    DEM_ENTERLOCK_MON();
                }
            }

            if((!AnyDTCSettingDisabled) && (!Dem_DtcIsDTCSettingEnabled(Dem_DtcIdIteratorCurrent(&dtcId))))
            {
                AnyDTCSettingDisabled = TRUE;
            }
        }
        DEM_EXITLOCK_MON();
        Dem_SetDtcGroupSettingFlag(AnyDTCSettingDisabled);
   }
}

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
Dem_DTCGroupIdType Dem_DtcGroupIdFromDtcGroupCode (Dem_DTCGroupType dtcGrpCode)
{
   Dem_DtcGroupIdIterator dtcGroupId;

   for(Dem_DtcGroupIdIteratorNew(&dtcGroupId);
        Dem_DtcGroupIdIteratorIsValid(&dtcGroupId);
        Dem_DtcGroupIdIteratorNext(&dtcGroupId))
   {
      if(Dem_DtcGroupGetCode(Dem_DtcGroupIdIteratorCurrent(&dtcGroupId)) == dtcGrpCode)
      {
         return Dem_DtcGroupIdIteratorCurrent(&dtcGroupId);
      }
   }
   return DEM_DTCGROUPID_INVALID;
}

Dem_ReturnControlDTCSettingType Dem_EnableDTCSetting (Dem_DTCGroupType DTCGroup, Dem_DTCKindType DTCKind)
{

   Dem_DTCGroupIdType DtcGroupId = Dem_DtcGroupIdFromDtcGroupCode(DTCGroup);
   DEM_UNUSED_PARAM(DTCKind);

   if(DTCGroup != DEM_DTC_GROUP_EMISSION_REL_DTCS)
   {
   	if(!Dem_DtcGroupIdIsValid(DtcGroupId))
   	{
   		return DEM_CONTROL_DTC_WRONG_DTCGROUP;
   	}
   }

#if(DEM_CFG_OBD == DEM_CFG_OBD_OFF)

   {
   	if(DTCGroup == DEM_DTC_GROUP_EMISSION_REL_DTCS)
   	{
   		return DEM_CONTROL_DTC_WRONG_DTCGROUP;
   	}
   }

#endif

   Dem_DtcGroupApplyDTCSetting(DTCGroup, DtcGroupId, DEM_DTC_SETTING_ENABLED);

   return DEM_CONTROL_DTC_SETTING_OK;
}

Dem_ReturnControlDTCSettingType Dem_DisableDTCSetting (Dem_DTCGroupType DTCGroup, Dem_DTCKindType DTCKind)
{

   Dem_DTCGroupIdType DtcGroupId = Dem_DtcGroupIdFromDtcGroupCode(DTCGroup);
   DEM_UNUSED_PARAM(DTCKind);

   if(DTCGroup != DEM_DTC_GROUP_EMISSION_REL_DTCS)
   {
   	if(!Dem_DtcGroupIdIsValid(DtcGroupId))
   	{
   		return DEM_CONTROL_DTC_WRONG_DTCGROUP;
   	}
   }

#if(DEM_CFG_OBD == DEM_CFG_OBD_OFF)

   {
   	if(DTCGroup == DEM_DTC_GROUP_EMISSION_REL_DTCS)
   	{
   		return DEM_CONTROL_DTC_WRONG_DTCGROUP;
   	}
   }

#endif

   Dem_DtcGroupApplyDTCSetting(DTCGroup, DtcGroupId, DEM_DTC_SETTING_DISABLED);

   return DEM_CONTROL_DTC_SETTING_OK;
}

void Dem_DtcsClearDtcInGroup(uint8 GroupId, Dem_DTCOriginType DTCOrigin, Dem_ClientClearMachineType *Dem_ClientClearMachinePtr)
{
    Dem_DtcIdType dtcId;

   if(Dem_ClientClearMachinePtr->IsNewClearRequest)
   {
        Dem_DtcIdListIteratorNewFromDtcGroup(&(Dem_ClientClearMachinePtr->DtcIt), GroupId);
   }

   while(Dem_DtcIdListIteratorIsValid(&(Dem_ClientClearMachinePtr->DtcIt)))
   {
        dtcId = Dem_DtcIdListIteratorCurrent(&(Dem_ClientClearMachinePtr->DtcIt));
        Dem_ClearSingleDTC(dtcId, DTCOrigin, Dem_ClientClearMachinePtr);

        if(Dem_ClientClearMachinePtr->IsClearInterrupted)
        {
            return;
        }
        Dem_DtcIdListIteratorNext(&(Dem_ClientClearMachinePtr->DtcIt));
   }
}
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
