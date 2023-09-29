#ifdef __cplusplus
extern "C"
{
#endif

#include "SwcServiceDem.hpp"
#include "fbl_inc.hpp"

void Dem_ReportErrorStatus(Dem_EventIdType  EventId, Dem_EventStatusType  EventStatus){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )
   (void) EventId;
   (void) EventStatus;
#endif
}

#ifdef __cplusplus
}
#endif
