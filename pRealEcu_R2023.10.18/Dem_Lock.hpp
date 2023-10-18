#ifndef DEM_LOCK_H
#define DEM_LOCK_H

#include "Dem_Cfg_Main.hpp"
#include "Dem_Cfg_Events.hpp"
#include "Dem_Main.hpp"
#include "Dem_Cfg_SchM.hpp"

#define DEM_ENTERLOCK_MON()              SchM_Enter_Dem_Monitoring()
#define DEM_EXITLOCK_MON()               SchM_Exit_Dem_Monitoring()
#define DEM_ENTERLOCK_DCM()              SchM_Enter_Dem_Dcm()
#define DEM_EXITLOCK_DCM()               SchM_Exit_Dem_Dcm()
#define DEM_ASSERT_ISLOCKED()            do {}while(0)
#define DEM_ASSERT_ISNOTLOCKED()         do {}while(0)

#endif
