#include "Std_Types.hpp"

#include "Dem_KL15Persistence.hpp"

#include "Dem.hpp"

static boolean Dem_Lok_KL15PersistenceIsStorageScheduled;

void Dem_KL15PersistenceMain(void){
   if(Dem_Lok_KL15PersistenceIsStorageScheduled)
   {
        Dem_Lok_KL15PersistenceIsStorageScheduled = FALSE;

   }
}

void Dem_KL15PersistenceScheduleStorage(void){
    Dem_Lok_KL15PersistenceIsStorageScheduled = TRUE;
}

Std_ReturnType Dem_KL15PersistenceImmediateStorage(void){
    Dem_Lok_KL15PersistenceIsStorageScheduled = FALSE;

    return 0;
}
