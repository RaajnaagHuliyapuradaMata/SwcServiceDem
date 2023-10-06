

#ifndef DEM_CLIENTCLEARMACHINE_H
#define DEM_CLIENTCLEARMACHINE_H

#include "Dem_ClientHandlingTypes.hpp"
#include "Dem_ClientBaseHandling.hpp"
#include "Dem_Client.hpp"
#include "Dem_Types.hpp"
#include "Dem_Mapping.hpp"
#include "Dem_Nvm.hpp"
#include "Dem_Cfg_Clear.hpp"

#define DEM_CLEAR_DTC_MACHINE_STATE_IDLE            0x00u
#define DEM_CLEAR_DTC_MACHINE_STATE_EXEC            0x01u
#define DEM_CLEAR_DTC_MACHINE_STATE_WAITINGFORNVM   0x02u

typedef struct{
  uint8                           activeClient;
  uint8                           machine_state;

  boolean                         IsNewClearRequest;

  boolean                         IsClearInterrupted;

  uint16                          NumberOfEventsProcessed;

  Dem_DtcIdListIterator           DtcIt;
  Dem_EventIdIterator             EvtIt;
  Dem_EventIdListIterator         EvtListIt;
#if(DEM_CFG_J1939DCM_CLEAR_SUPPORT != DEM_CFG_J1939DCM_OFF)
  Dem_DtcIdListIterator2          DtcIt2;
#endif
}Dem_ClientClearMachineType;

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

extern Dem_ClientClearMachineType Dem_ClientClearMachine;

#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

DEM_INLINE void Dem_ClientClearMachine_SetMachineActiveClient(Dem_ClientIdType ClientId)
{
    Dem_ClientClearMachine.activeClient = ClientId;
}

DEM_INLINE boolean Dem_ClientClearMachine_isProcessingClient(Dem_ClientIdType ClientId)
{
    return (Dem_ClientClearMachine.activeClient == ClientId);
}

DEM_INLINE uint8 Dem_ClientClearMachine_GetMachineActiveClient(void){
    return Dem_ClientClearMachine.activeClient;
}

DEM_INLINE void Dem_ClientClearMachine_SetMachineState(uint8 state)
{
    Dem_ClientClearMachine.machine_state = state;
}

DEM_INLINE uint8 Dem_ClientClearMachine_GetMachineState(void){
    return Dem_ClientClearMachine.machine_state;
}

DEM_INLINE boolean Dem_ClientClearMachine_isClearDtcGroupAllDtcsSelected(Dem_ClientIdType ClientId)
{
boolean status = TRUE;
#if(DEM_CFG_J1939DCM != DEM_CFG_J1939DCM_OFF)
if(ClientId != DEM_CLIENTID_J1939)
#endif
{
   if((Dem_LibGetParamUI8(DEM_CFG_CLEAR_DTC_LIMITATION)
            == Dem_LibGetParamUI8(DEM_CFG_CLEAR_DTC_LIMITATION_ONLY_CLEAR_ALL_DTCS))
            && (Dem_ClientSelectionType_getTypeOfSelection(Dem_Clients[ClientId].selection)
                    != DEM_CLIENT_SELECTION_TYPE_ALL_DTCS))
   {
        Dem_ClientResultType_setResult(&Dem_Clients[ClientId].result, Dem_Clients[ClientId].request, DEM_WRONG_DTC);
        status = FALSE;
   }
}
return status;
}

DEM_INLINE void Dem_ClientClearMachine_SetClientRequest(Dem_ClientIdType ClientId, uint8 state)
{
if(Dem_ClientClearMachine_isClearDtcGroupAllDtcsSelected(ClientId))
{
   if(state == DEM_CLEAR_DTC_MACHINE_STATE_IDLE)
   {
        Dem_ClientSelectionType_invalidateSelectionResult(&Dem_Client_getClient(ClientId)->selection);
        Dem_ClientClearMachine_SetMachineActiveClient(DEM_CLIENTID_INVALID);
        Dem_ClientClearMachine_SetMachineState(state);
   }
   else if(state == DEM_CLEAR_DTC_MACHINE_STATE_EXEC)
   {
        Dem_ClientClearMachine.IsNewClearRequest = TRUE;
        Dem_ClientClearMachine_SetMachineActiveClient(ClientId);
        Dem_NvMStartClear();
        Dem_ClientClearMachine_SetMachineState(state);
   }
   else if(state == DEM_CLEAR_DTC_MACHINE_STATE_WAITINGFORNVM)
   {
        Dem_ClientClearMachine_SetMachineState(state);
   }
   else{

   }
}
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#endif
