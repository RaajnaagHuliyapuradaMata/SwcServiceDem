

#ifndef DEM_CLIENT_H
#define DEM_CLIENT_H

#include "Dem_ClientHandlingTypes.hpp"
#include "Dem_Array.hpp"
#include "Dem_Dcm.hpp"

#define DEM_CLIENTID_INVALID  0x00
#define DEM_CLIENTID_DCM      0x01

typedef struct{
  uint32                           DTC;
  Dem_DTCFormatType                DTCFormat;
  Dem_DTCOriginType                DTCOrigin;
#if(DEM_CFG_J1939DCM_CLEAR_SUPPORT != DEM_CFG_J1939DCM_OFF)
  Dem_J1939DcmSetClearFilterType   J1939DTCTypeFilter;
  uint8                            J1939node;
#endif
  volatile uint8                   client_state;
  volatile Dem_ClientRequestType   request;
  volatile Dem_ClientResultType    result;
  Dem_ClientSelectionType          selection;
}Dem_ClientType;

typedef struct{
  uint8 ClientId;
  Dem_ClientPriorityType          client_priority;
}Dem_ClientConfigDataType;

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

DEM_ARRAY_DECLARE(Dem_ClientType, Dem_Clients, DEM_CLIENTID_ARRAYLENGTH);

#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

DEM_ARRAY_DECLARE_CONST(Dem_ClientConfigDataType, Dem_Client_ConfigData, DEM_CLIENTS_COUNT);

#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

DEM_INLINE Dem_boolean_least Dem_isClientIdValid(Dem_ClientIdType clientId)
{
   return ((clientId != DEM_CLIENTID_INVALID) && (clientId < DEM_CLIENTID_ARRAYLENGTH));
}

Dem_ClientType* Dem_Client_getClient (Dem_ClientIdType ClientId);
Std_ReturnType Dem_SelectDTC(uint8 ClientId, uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin);
Std_ReturnType Dem_ClearDTC_4_3(uint8 ClientId);
Std_ReturnType Dem_Client_Operation(uint8 ClientId, uint8 requestId, uint8 ApiId);

#if(DEM_CFG_J1939DCM_CLEAR_SUPPORT != DEM_CFG_J1939DCM_OFF)
Std_ReturnType Dem_J1939DcmClearDTC_4_3 (Dem_J1939DcmSetClearFilterType DTCTypeFilter , uint8 node, uint8 ClientId);
#endif

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#endif
