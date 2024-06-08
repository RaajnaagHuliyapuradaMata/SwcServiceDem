#ifndef DEM_DLT_H
#define DEM_DLT_H

#include "Dem_Types.hpp"

Std_ReturnType Dem_DltGetAllExtendedDataRecords(Dem_EventIdType EventId, uint8* DestBuffer, uint16* BufSize);
Std_ReturnType Dem_DltGetMostRecentFreezeFrameRecordData(Dem_EventIdType EventId, uint8* DestBuffer, uint16* BufSize);

#endif
