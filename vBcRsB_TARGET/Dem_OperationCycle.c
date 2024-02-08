#include "Std_Types.hpp"

#include "Dem.hpp"
#include "Rte_Dem.hpp"

#include "Dem_OperationCycle.hpp"
#include "Dem_Events.hpp"
#include "Dem_Main.hpp"
#include "Dem_Lock.hpp"
#include "Dem_Mapping.hpp"
#include "Dem_EventStatus.hpp"
#include "Dem_ISO14229Byte.hpp"
#include "Dem_EvMem.hpp"
#include "Dem_EventRecheck.hpp"
#include "Dem_Cfg.hpp"
#include "Dem_GenericNvData.hpp"
#include "Dem_Cfg.hpp"

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"
Dem_OperationCycleList Dem_OperationCycleStates;
static Dem_OperationCycleList Dem_OperationCycleQualified;
static Dem_OperationCycleList Dem_QualifyCycleCollectedTriggers;
static Dem_OperationCycleList Dem_StartOperationCycleCollectedTriggers;
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
static boolean Dem_IsOperationCycleIdValid(Dem_OperationCycleIdType OperationCycleId)
{
    return (OperationCycleId < DEM_OPERATIONCYCLE_COUNT);
}

Std_ReturnType Dem_GetCycleQualified(Dem_OperationCycleIdType OperationCycleId, boolean* isQualified)
{
    Std_ReturnType retVal = E_NOT_OK;

   if(!Dem_IsOperationCycleIdValid(OperationCycleId))
   {
        DEM_DET(DEM_DET_APIID_GETCYCLEQUALIFIED, DEM_E_WRONG_CONFIGURATION);
   }
   else{
        *isQualified = DEM_OPERATIONCYCLE_ISBITSET(Dem_OperationCycleQualified, OperationCycleId);
        retVal = E_OK;
   }

    return retVal;
}

Std_ReturnType Dem_SetCycleQualified(Dem_OperationCycleIdType OperationCycleId)
{
    Std_ReturnType retVal = E_NOT_OK;

   if(!Dem_IsOperationCycleIdValid(OperationCycleId))
   {
        DEM_DET(DEM_DET_APIID_SETCYCLEQUALIFIED, DEM_E_WRONG_CONFIGURATION);
   }
   else{
        DEM_ENTERLOCK_MON();
        DEM_OPERATIONCYCLE_SETBIT(&Dem_OperationCycleQualified, OperationCycleId);
        DEM_OPERATIONCYCLE_SETBIT(&Dem_QualifyCycleCollectedTriggers, OperationCycleId);

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
        rba_DemObdBasic_SetCycleQualified(OperationCycleId);
#endif
        DEM_EXITLOCK_MON();

        retVal = E_OK;
   }

    return retVal;
}

Std_ReturnType Dem_SetOperationCycleState(Dem_OperationCycleIdType OperationCycleId
   ,     Dem_OperationCycleStateType CycleState)
{
    Std_ReturnType retVal = E_OK;

   if(!Dem_IsOperationCycleIdValid(OperationCycleId))
   {
        DEM_DET(DEM_DET_APIID_DEM_SETOPERATIONCYCLESTATE, DEM_E_WRONG_CONFIGURATION);
        DEM_ASSERT_ISNOTLOCKED();
        return E_NOT_OK;
   }

   if(!Dem_Cfg_OperationCycle_GetIsAllowedToBeStartedDirectly(OperationCycleId))
   {
        //DEM_DET(DEM_DET_APIID_DEM_SETOPERATIONCYCLESTATE, DEM_E_WRONG_CONFIGURATION);
        DEM_ASSERT_ISNOTLOCKED();
        return E_NOT_OK;
   }

    DEM_ENTERLOCK_MON();

   if(CycleState == DEM_CYCLE_STATE_START)
   {
        Dem_OperationCycleList bitMaskOld = 0;
        Dem_OperationCycleList bitMask = 0;
        Dem_OperationCycleList bitMaskDependent = 0;
        Dem_OperationCycleIdType cycleId;

        DEM_OPERATIONCYCLE_SETBIT(&bitMask, OperationCycleId);

        do
        {

            bitMaskOld = bitMask;

            for(cycleId = 0; cycleId < DEM_OPERATIONCYCLE_COUNT; cycleId++)
            {

                if(DEM_OPERATIONCYCLE_ISBITSET(bitMask, cycleId))
                {
                    bitMaskDependent = Dem_Cfg_OperationCycle_GetDependentCycleMask(cycleId);

                    DEM_OPERATIONCYCLE_MERGEBITMASK(&bitMaskDependent, Dem_OperationCycleQualified);

                    DEM_OPERATIONCYCLE_SETBITMASK(&bitMask, bitMaskDependent);
                }
            }

        }while(bitMaskOld != bitMask);

        DEM_OPERATIONCYCLE_SETBITMASK(&Dem_OperationCycleStates, bitMask);
        DEM_OPERATIONCYCLE_SETBITMASK(&Dem_StartOperationCycleCollectedTriggers, bitMask);

        DEM_OPERATIONCYCLE_CLEARBITMASK(&Dem_OperationCycleQualified, bitMask);
        DEM_OPERATIONCYCLE_CLEARBITMASK(&Dem_QualifyCycleCollectedTriggers, bitMask);

   }
   else if(CycleState == DEM_CYCLE_STATE_END)
   {
        DEM_OPERATIONCYCLE_CLEARBIT(&Dem_OperationCycleStates, OperationCycleId);
   }
   else{
        DEM_DET(DEM_DET_APIID_DEM_SETOPERATIONCYCLESTATE, DEM_E_WRONG_CONFIGURATION);
        retVal = E_NOT_OK;
   }

    DEM_EXITLOCK_MON();
    return retVal;
}

Std_ReturnType Dem_GetOperationCycleState(Dem_OperationCycleIdType OperationCycleId
   ,     Dem_OperationCycleStateType* CycleState)
{

    DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(CycleState, DEM_DET_APIID_DEM_GETOPERATIONCYCLESTATE, E_NOT_OK);
   if(!Dem_IsOperationCycleIdValid(OperationCycleId))
   {
        DEM_DET(DEM_DET_APIID_DEM_GETOPERATIONCYCLESTATE, DEM_E_WRONG_CONFIGURATION);
        return E_NOT_OK;
   }

   if(DEM_OPERATIONCYCLE_ISBITSET(Dem_OperationCycleStates, OperationCycleId))
   {
        *CycleState = DEM_CYCLE_STATE_START;
   }
   else{
        *CycleState = DEM_CYCLE_STATE_END;
   }

    return E_OK;
}

boolean Dem_OperationCyclesMainFunction(void){
   boolean retVal = FALSE;

    Dem_OperationCycleList opCycleStartTriggers;
    Dem_OperationCycleList opCycleQualifiedTriggers;

   if((Dem_StartOperationCycleCollectedTriggers != 0) || (Dem_QualifyCycleCollectedTriggers != 0))
   {
        DEM_ENTERLOCK_MON();
        opCycleStartTriggers = Dem_StartOperationCycleCollectedTriggers;
        opCycleQualifiedTriggers = Dem_QualifyCycleCollectedTriggers;
        Dem_StartOperationCycleCollectedTriggers = 0;
        Dem_QualifyCycleCollectedTriggers = 0;
        DEM_EXITLOCK_MON();

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)

        rba_DemObdBasic_StartOperationCycle(opCycleStartTriggers, opCycleQualifiedTriggers);
#endif

#if( DEM_BFM_ENABLED == DEM_BFM_ON )
        rba_DemBfm_CounterAdvanceOperationCycle( opCycleStartTriggers );
#endif

        Dem_EvMemStartOperationCycleAllMem(opCycleStartTriggers);
        Dem_EvtAdvanceOperationCycle(opCycleStartTriggers);
        Dem_RecheckNodeNotRecoverableRequest();

        if(Dem_LibGetParamBool(DEM_CFG_OPERATIONCYCLESTATUSSTORAGE))
        {
            Dem_GenericNvData.OperationCycleStates = Dem_OperationCycleStates;
            Dem_GenericNvData.OperationCycleQualified = Dem_OperationCycleQualified;

            Dem_NvMWriteBlockOnShutdown(DEM_NVM_ID_DEM_GENERIC_NV_DATA);
        }

        retVal = TRUE;
   }

    return retVal;
}

void Dem_OperationCycleInit(void){

    (void) Dem_OperationCyclesMainFunction();
}

void Dem_OperationCycleInitCheckNvm(void){
   if(Dem_LibGetParamBool(DEM_CFG_OPERATIONCYCLESTATUSSTORAGE))
   {
        DEM_ENTERLOCK_MON();
        Dem_OperationCycleStates |= Dem_GenericNvData.OperationCycleStates;
        Dem_OperationCycleQualified |= Dem_GenericNvData.OperationCycleQualified;
        DEM_EXITLOCK_MON();
   }
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
