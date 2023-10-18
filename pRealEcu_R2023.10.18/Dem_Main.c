#include "Std_Types.hpp"

#include "Dem.hpp"
#include "SchM_Dem.hpp"
#include "Rte_Dem.hpp"
#include "Dem_Main.hpp"
#include "Dem_Lok_J1939Dcm.hpp"
#include "Dem_ClientRequestDispatcher.hpp"
#include "Dem_Cfg_AssertionChk.hpp"
#include "Dem_IndicatorAttributes.hpp"
#include "Dem_OperationCycle.hpp"
#include "Dem_Clear.hpp"
#include "Dem_Events.hpp"
#include "Dem_Deb.hpp"
#include "Dem_EventFHandling.hpp"
#include "Dem_EventStatus.hpp"
#include "Dem_EventRecheck.hpp"
#include "Dem_EvBuff.hpp"
#include "Dem_EvBuffDistributor.hpp"
#include "Dem_DTCStatusByte.hpp"
#include "Dem_DTCFilter.hpp"
#include "Dem_EventStatus.hpp"
#include "Dem_EvMem.hpp"
#include "Dem_Nvm.hpp"

#if(DEM_CFG_FIM_USED == DEM_CFG_FIM_ON)
#include "FiM.hpp"
#endif

#include "Dem_EvBuffDistributor.hpp"
#include "Dem_DisturbanceMemory.hpp"
#include "Dem_Cfg.hpp"
#include "Dem_Cfg.hpp"

#if(DEM_CFG_SUPPORT_PROJECTSPECIFIC_CONSISTENCYCHECK == DEM_CFG_CONSISTENCY_CHECK_ON)
#include "Dem_PrjSpecificConsistencyCheck.hpp"
#endif
#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
struct Dem_ConfigType
{
   boolean debouncerAlternativeParameters;
   boolean dtcAlternativeParameters;

#if(DEM_BFM_ENABLED == DEM_BFM_ON)
    rba_DemBfm_ConfigDataType const * demBfmConfigPointer;
#endif
};

#if(DEM_BFM_ENABLED == DEM_BFM_OFF)

const Dem_ConfigType Dem_ConfigAlternativeParameters = { TRUE, TRUE };

#else
const Dem_ConfigType Dem_ConfigAlternativeParameters = { TRUE, TRUE, &rba_DemBfm_ConfigParam_cs };
#endif

#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

#if(DEM_CFG_VERSION_INFO_API == DEM_CFG_VERSION_INFO_API_ON)
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
void Dem_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
   versioninfo->vendorID = DEM_VENDOR_ID;
   versioninfo->moduleID = DEM_MODULE_ID;
   versioninfo->sw_major_version = DEM_SW_MAJOR_VERSION;
   versioninfo->sw_minor_version = DEM_SW_MINOR_VERSION;
   versioninfo->sw_patch_version = DEM_SW_PATCH_VERSION;
}
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
#endif

#define DEM_START_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.hpp"

Dem_OpMoStateType Dem_OpMoState = DEM_OPMO_STATE_NOTINITIALIZED;
Dem_FimStateType Dem_FimState = DEM_FIM_STATE_NOTINITIALIZED;
Dem_boolean_least Dem_TestFailedStatusInitialized = FALSE;

static boolean Dem_OpMoWasInitialized = FALSE;

#define DEM_STOP_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

void Dem_PreInit(const Dem_ConfigType* ConfigPtr)
{
    DEM_ASSERT(Dem_OpMoState==DEM_OPMO_STATE_NOTINITIALIZED, DEM_DET_APIID_PREINIT, 0);

    Dem_EvtPreInitEvents();

    Dem_PreInitErrorQueue();

    Dem_ReportErrorStatusEnableQueue();

   if(ConfigPtr != NULL_PTR)
   {
        if(ConfigPtr->debouncerAlternativeParameters) {
            Dem_DebSwitchToAlternativeParameters();
        }
#if(DEM_CFG_ALTERNATIVEDTC == DEM_CFG_ALTERNATIVEDTC_ON)
        if(ConfigPtr->dtcAlternativeParameters) {
            Dem_SwitchToAlternativeDtc();
        }
#endif
   }

   #if(DEM_BFM_ENABLED == DEM_BFM_ON)
   if( ConfigPtr != NULL_PTR )
   {
   	rba_DemBfm_PreInit( ConfigPtr->demBfmConfigPointer );
   }
   else
   {
   	rba_DemBfm_PreInit( NULL_PTR );
   }
   #endif

   Dem_OpMoState = DEM_OPMO_STATE_PREINITIALIZED;
}

Std_ReturnType Dem_LockAllFailureInfo (void){
#if(DEM_CFG_LOCK_ALLFAILUREINFO == DEM_CFG_LOCK_ALLFAILUREINFO_ON)
    Dem_OpMoState = DEM_OPMO_STATE_LOCK_ALL_FAILURE_INFO;
    (void)Dem_LockEventMemory(TRUE);
    return E_OK;
#else
    return E_NOT_OK;
#endif
}

void Dem_Init(void){
#if(DEM_CFG_LOCK_ALLFAILUREINFO == DEM_CFG_LOCK_ALLFAILUREINFO_ON)
   if(!Dem_OpMoIsAllFailureInfoLocked())
#endif
   {
        DEM_ASSERT(Dem_OpMoState==DEM_OPMO_STATE_PREINITIALIZED, DEM_DET_APIID_INIT, 0);

        if(Dem_OpMoState == DEM_OPMO_STATE_PREINITIALIZED)
        {

#if(DEM_CFG_SUPPORT_PROJECTSPECIFIC_CONSISTENCYCHECK == DEM_CFG_CONSISTENCY_CHECK_ON)
            Dem_ProjectSpecificConsistencyCheck();
#endif

            Dem_NvMInit();

            Dem_OperationCycleInitCheckNvm();
            Dem_ClearDtcInit();
            Dem_DtcFilterInit();
#if(DEM_CFG_J1939DCM_READ_DTC_SUPPORT)
            Dem_J1939DcmDtcFilterInit();
#endif
#if(DEM_CFG_J1939DCM_FREEZEFRAME_SUPPORT || DEM_CFG_J1939DCM_EXPANDED_FREEZEFRAME_SUPPORT)
            Dem_J1939DcmFreezeFrameFilterInit();
#endif
            if(!Dem_OpMoWasInitialized)
            {
                 //Set the event status to 0 for the events which are currently not available or suppressed
                Dem_EvtInitEvents();

                Dem_EventStatusInitCheckNvM();

#if(DEM_CFG_ALLOW_HISTORY == DEM_CFG_ALLOW_HISTORY_ON)
                Dem_EvtHistoryStatusInitCheckNvM();
#endif

                Dem_IndicatorAttributeInitCheckNvM();

                Dem_EvMemInit();

                Dem_InitEventStatusTestFailed();

                Dem_DependencyInit();

                Dem_IndicatorAttributeInit();

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
                rba_DemObdBasic_InitCheckNvm();
#endif

#if(DEM_CFG_FFPRESTORAGESUPPORT == DEM_CFG_FFPRESTORAGESUPPORT_ON)
                Dem_PreStoredFFInitCheckNvM();
#endif

#if(DEM_CFG_DISTURBANCE_MEMORY == DEM_CFG_DISTURBANCE_MEMORY_ON)
                Dem_DistMemInitCheckNvM();
#endif

#if( DEM_BFM_ENABLED == DEM_BFM_ON )
                rba_DemBfm_InitCheckNvM();
                rba_DemBfm_InitCausality();
#endif
                Dem_EvMemInitCausality();

#if(DEM_CFG_FIM_USED == DEM_CFG_FIM_ON)
                Dem_FimState = DEM_FIM_STATE_IS_IN_INITIALIZATION;

                FiM_DemInit();

                Dem_FimState = DEM_FIM_STATE_INITIALIZED;
#endif
            }

            Dem_OperationCycleInit();

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
            rba_DemObdBasic_Init();
#endif

#if(DEM_CFG_DISTURBANCE_MEMORY == DEM_CFG_DISTURBANCE_MEMORY_ON)
            Dem_DistMemInit();
#endif

#if( DEM_BFM_ENABLED == DEM_BFM_ON )
            rba_DemBfm_Init();
#endif

            Dem_TestFailedStatusInitialized = TRUE;
            Dem_ReportErrorStatusDisableQueue();
            Dem_OpMoWasInitialized = TRUE;
            Dem_OpMoState = DEM_OPMO_STATE_INITIALIZED;

        }
   }
}

DEM_INLINE void Dem_HandleImmediateTrigger(void){
#if(DEM_CFG_TRIGGER_TO_STORE_NVM_SUPPORTED)
   if(Dem_NvMIsImmediateStorageRequested())
   {

#if( DEM_BFM_ENABLED == DEM_BFM_ON )
        (void)rba_DemBfm_TriggerStoreToNvm();
#endif

   }
#endif //(DEM_CFG_TRIGGER_TO_STORE_NVM_SUPPORTED)
}

void infSwcServiceDemSwcServiceSchM_vMainFunction(void){
   if(Dem_OpMoState == DEM_OPMO_STATE_INITIALIZED)
   {
        Dem_HandleImmediateTrigger();

        if(!Dem_OperationCyclesMainFunction())
        {

#if(DEM_CFG_ENABLECONDITION == DEM_CFG_ENABLECONDITION_ON)
            Dem_EnCoCallbacks();
#endif
        }

        Dem_ClientRequestDispatcher_main();

        Dem_ClearMainFunction();

        Dem_DebMainFunction();

        Dem_IndicatorAttributeMainFunction();

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
        rba_DemObdBasic_MainFunction();
#endif

        Dem_EvBuffMainFunction();

#if( DEM_BFM_ENABLED == DEM_BFM_ON )
        rba_DemBfm_MainFunction();
#endif

        Dem_DependencyMainFunction();

        Dem_StoCoMainFunction();

        Dem_EvBuffDistributorMainFunction();

#if(DEM_CFG_DTCFILTER_EXTERNALPROCESSING == DEM_CFG_DTCFILTER_EXTERNALPROCESSING_OFF)
        Dem_DTCFilterMainFunction();
#endif

        Dem_EvMemMainFunction();

#if(DEM_CFG_DISTURBANCE_MEMORY == DEM_CFG_DISTURBANCE_MEMORY_ON)
        Dem_DistMemMainFunction();
#endif
#if(DEM_CFG_CALLBACK_INIT_MON_FOR_EVENT_SUPPORTED == TRUE)
        Dem_InitMonitorForEFnc();
#endif
        Dem_NvMMainFunction();
   }
#if(DEM_CFG_LOCK_ALLFAILUREINFO == DEM_CFG_LOCK_ALLFAILUREINFO_ON)
   if(Dem_OpMoIsAllFailureInfoLocked())
   {
#if(DEM_CFG_DTCFILTER_EXTERNALPROCESSING == DEM_CFG_DTCFILTER_EXTERNALPROCESSING_OFF)
        Dem_DTCFilterMainFunction();
#endif
   }
#endif
}

void Dem_Shutdown(void){
#if(DEM_CFG_LOCK_ALLFAILUREINFO == DEM_CFG_LOCK_ALLFAILUREINFO_ON)
   if(!Dem_OpMoIsAllFailureInfoLocked())
#endif
   {
        DEM_ASSERT(Dem_OpMoState==DEM_OPMO_STATE_INITIALIZED, DEM_DET_APIID_SHUTDOWN, 0);

        if(Dem_OpMoState == DEM_OPMO_STATE_INITIALIZED)
        {

            //DEM102 : Dem_Shutdown shall finalize all pending operations in the Dem module
            //DEM341 : For individual non-volatile blocks the API NvM_WriteBlock shall be called within the API Dem_Shutdown.

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
            rba_DemObdBasic_Shutdown();
#endif

            Dem_ReportErrorStatusEnableQueue();
            Dem_OpMoState = DEM_OPMO_STATE_PREINITIALIZED;
            Dem_TestFailedStatusInitialized = FALSE;

            Dem_EvBuffDistributorMainFunction();

#if( DEM_BFM_ENABLED == DEM_BFM_ON )
            rba_DemBfm_Shutdown();
#endif

            Dem_IndicatorAttributeShutdown();

            Dem_NvMShutdown();
        }
   }
}

#if(DEM_CFG_ERASE_ALL_DATA_SUPPORTED != DEM_CFG_ERASE_ALL_OFF)
Std_ReturnType Dem_GetEraseAllNvMDataResult(Dem_EraseAllStatusType* EraseResult)
{

    *EraseResult = Dem_NvMGetInvalidateAllNvMBlocksStatus();

    return E_OK;
}
#endif

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"
