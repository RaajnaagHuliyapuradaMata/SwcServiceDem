

#ifndef DEM_EVMEMTYPES_H
#define DEM_EVMEMTYPES_H

#include "Dem_Types.hpp"
#include "Dem_Cfg_EvMem.hpp"
#include "Dem_Cfg_EnvMain.hpp"
#include "Dem_Cfg_EnvDataElement.hpp"

#include "Dem_Cfg_DTCs.hpp"

#include "Dem_Cfg_DTC_DataStructures.hpp"

#if(DEM_CFG_EVMEM_PROJECT_EXTENSION)
#include "Dem_PrjEvmemProjectExtension.hpp"
#endif

#define DEM_EVMEM_MAX_TIMEID                                    0xFFFFFFFFuL

#define DEM_EVMEM_INVALID_LOCID                                 0xFFFFu

#define DEM_EVMEM_INVALID_MEMID                                 0xFFFFu

#define DEM_EVMEM_STSMASK_TESTFAILED                            0x0001u
#define DEM_EVMEM_STSMASK_TESTFAILED_TFC                        0x0002u
#define DEM_EVMEM_STSMASK_PENDING                               0x0004u
#define DEM_EVMEM_STSMASK_CONFIRMED                             0x0008u
#define DEM_EVMEM_STSMASK_PENDING_NFC                           0x0010u
#define DEM_EVMEM_STSMASK_TESTCOMPLETE_TFC                      0x0020u
#define DEM_EVMEM_STSMASK_TESTFAILED_SLC                        0x0040u
#define DEM_EVMEM_STSMASK_DELETED                               0x0080u

#define DEM_EVMEM_STSMASK_TESTFAILED_TAC                        0x0100u
#define DEM_EVMEM_STSMASK_TESTCOMPLETE_TAC                      0x0200u
#define DEM_EVMEM_STSMASK_AGED                                  0x0400u
#define DEM_EVMEM_STSMASK_PENDING_CONFIRMED                     0x0800u
#define DEM_EVMEM_STSMASK_STORED                                0x1000u
#if(DEM_CFG_EVMEM_READ_FROM_DIFFERENT_TASK)
#define DEM_EVMEM_STSMASK_READER_COPY_CURRENT               0x2000u
#else

#define DEM_EVMEM_STSMASK_READER_COPY_CURRENT                   0u
#endif
#define DEM_EVMEM_STSMASK_CONFIRMATION_NOT_YET_VISIBLE_IN_OBD   0x4000u
#define DEM_EVMEM_STSMASK_MIL_NOT_YET_VISIBLE_IN_OBD            0x8000u

#define DEM_EVMEM_STORAGE_PRIO_UNDEF                0u
#define DEM_EVMEM_STORAGE_PRIO_DELETED              1u
#define DEM_EVMEM_STORAGE_PRIO_EMPTY                2u
#define DEM_EVMEM_STORAGE_PRIO_STORED               3u

#define DEM_EVMEM_PRIO_OFFSET                       255u

#define DEM_EVMEM_WRITEMASK_NO                      0x0000u
#define DEM_EVMEM_WRITEMASK_DATA                    0x0001u
#define DEM_EVMEM_WRITEMASK_EVENTDATA               0x0002u
#define DEM_EVMEM_WRITEMASK_CLEAR                   0x0004u
#define DEM_EVMEM_WRITEMASK_OCCCOUNTER              0x0008u

#define DEM_EVMEM_UPDATE_EXTDATA_AND_FFDATA         0u
#define DEM_EVMEM_UPDATE_EXTDATA                    1u
#define DEM_EVMEM_UPDATE_FFDATA                     2u

#if DEM_CFG_EVMEM_OCCURRENCE_COUNTER_MAX <= 0xFF
   typedef uint8    Dem_EvMemOccurrenceCounterType;
#elif DEM_CFG_EVMEM_OCCURRENCE_COUNTER_MAX <= 0xFFFF
   typedef uint16   Dem_EvMemOccurrenceCounterType;
#else
#error Occurrence Counter Type must be 8 or 16-Bit
#endif

#if DEM_CFG_EVMEM_AGING_COUNTER_MAX <= 0xFF
   typedef uint8    Dem_EvMemAgingCounterType;
#elif DEM_CFG_EVMEM_AGING_COUNTER_MAX <= 0xFFFF
   typedef uint16   Dem_EvMemAgingCounterType;
#else
#error Aging Counter Type must be 8 or 16-Bit
#endif

#if(DEM_CFG_EVMEM_DEBUG_BITFIELDS)

typedef struct{
   unsigned int TestFailed                      :1;
   unsigned int TestFailedTFC                   :1;
   unsigned int Pending                         :1;
   unsigned int Confirmed                       :1;
   unsigned int PendingNFC                      :1;
   unsigned int TestCompleteTFC                 :1;
   unsigned int TestFailedSLC                   :1;
   unsigned int Deleted                         :1;
   unsigned int TestFailedTAC                   :1;
   unsigned int TestCompleteTAC                 :1;
   unsigned int Aged                            :1;
   unsigned int PendingConfirmed                :1;
   unsigned int Stored                          :1;
   unsigned int ReaderCopyCurrent               :1;
   unsigned int ConfirmationNotYetVisibleInOBD  :1;
   unsigned int MilNotYetVisibleInOBD           :1;
}Dem_EvMemStatusBitFieldType;

#endif

typedef union
{
  struct
  {
      uint16       Status;
      uint16       EventId;
  }Data;
#if(DEM_CFG_EVMEM_DEBUG_BITFIELDS)
  Dem_EvMemStatusBitFieldType  StatusBits;
#endif
}Dem_EvMemHdrType;

typedef struct{
   Dem_EvMemHdrType                          Hdr;

#if(DEM_CFG_EVMEM_MIRROR_MEMORY_DTC_STATUS_STORED)
   uint8                                     DTCStatus;
#endif
#if(DEM_CFG_READDEM_CYCLES_SINCE_FIRST_FAILED_SUPPORTED)
   uint8                            CyclesSinceFirstFailed;
#endif

#if(DEM_CFG_READDEM_CYCLES_SINCE_LAST_FAILED_SUPPORTED)
   uint8                            CyclesSinceLastFailed;
#endif

#if(DEM_CFG_READDEM_CYCLES_SINCE_LAST_FAILED_EXCLUDING_TNC_SUPPORTED)
   uint8                            CyclesSinceLastFailedExcludingTNC;
#endif

#if(DEM_CFG_READDEM_FAILED_CYCLES_SUPPORTED)
   uint8                           FailedCycles;
#endif

   uint8                                     Data[DEM_CFG_ENVMINSIZE_OF_MULTIPLE_RAWENVDATA];
   uint8                                     FailureCounter;

#if(DEM_CFG_EVMEM_FREEZE_FRAME_SUPPORTED)
   uint8                                     FreezeFrameCounter;
#endif
#if(DEM_CFG_READDEM_MAX_FDC_DURING_CURRENT_CYCLE_SUPPORTED)
   sint8                                   MaxFdcDuringCurrentCycle;
#endif
#if(DEM_CFG_READDEM_MAX_FDC_SINCE_LAST_CLEAR_SUPPORTED)
   sint8                                   MaxFdcSinceLastClear;
#endif

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
   uint8                                     ObdMilCounter;
   boolean                                   ObdMilResetThisCycle;
#endif

#if(DEM_CFG_EVMEM_AGING_COUNTER_SUPPORTED)
   Dem_EvMemAgingCounterType                 AgingCounter;
#endif
#if(DEM_CFG_TFSLC_RESET_AFTER_AGING_AND_DISPLACEMENT)
   Dem_EvMemAgingCounterType                 AgingCounterForTFSLC;
#endif
#if(DEM_CFG_EVMEM_OCCURRENCE_COUNTER_SUPPORTED)
   Dem_EvMemOccurrenceCounterType            OccurrenceCounter;
#endif
#if(DEM_CFG_EVMEM_EXTENDED_DATA_SUPPORTED || DEM_CFG_EVMEM_FREEZE_FRAME_SUPPORTED)
   Dem_TriggerType                           Trigger;
#endif

   uint32                                    TimeId;

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
   uint32                                    ObdFFTimeId;
#endif

#if(DEM_CFG_EVMEM_PROJECT_EXTENSION)
   Dem_EvMemProjectExtensionType             ProjectExtension;
#endif

#if(DEM_CFG_REPORT_CHRONOLOGICAL_ORDER_HOOKS_ENABLED)
   uint32 Dem_ChronoSortID;
#endif
}Dem_EvMemEventMemoryType;

#endif

