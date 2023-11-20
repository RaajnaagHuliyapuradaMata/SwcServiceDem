

#ifndef DEM_CLIENTSELECTIONRESULT_H
#define DEM_CLIENTSELECTIONRESULT_H

#include "Dem_Client.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

DEM_INLINE void Dem_ClientSelectionResult_SetClientRequest(Dem_ClientIdType clientId)
{
    Dem_ClientResultType_setResult(&Dem_Clients[clientId].result, Dem_Clients[clientId].request, E_OK);
}

DEM_INLINE void Dem_ClientSelectionResult_SetClientRequest4Clear(Dem_ClientIdType clientId)
{
      if((Dem_LibGetParamUI8(DEM_CFG_CLEAR_DTC_LIMITATION) == Dem_LibGetParamUI8(DEM_CFG_CLEAR_DTC_LIMITATION_ONLY_CLEAR_ALL_DTCS))
          && (Dem_ClientSelectionType_getTypeOfSelection(Dem_Clients[clientId].selection) != DEM_CLIENT_SELECTION_TYPE_ALL_DTCS))
      {
          Dem_ClientResultType_setResult(&Dem_Clients[clientId].result, Dem_Clients[clientId].request, DEM_WRONG_DTC);
      }else{
          Dem_ClientResultType_setResult(&Dem_Clients[clientId].result, Dem_Clients[clientId].request, E_OK);
      }
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#endif
