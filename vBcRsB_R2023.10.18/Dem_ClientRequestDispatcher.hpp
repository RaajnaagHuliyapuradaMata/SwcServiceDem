

#ifndef DEM_CLIENTREQUESTDISPATCHER_H
#define DEM_CLIENTREQUESTDISPATCHER_H

#include "Dem_ClientHandlingTypes.hpp"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

void Dem_ClientRequestDispatcher_main (void);

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#endif
