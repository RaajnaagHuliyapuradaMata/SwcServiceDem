#ifndef DEM_ARRAY_H
#define DEM_ARRAY_H

#include "Dem_Cfg_Main.hpp"
#include "Dem_Types.hpp"

#if(   (DEM_CFG_BUILDTARGET == DEM_CFG_BUILDTARGET_ECU) \
     || (defined DEM_TEST_FORCE_PLAIN_ARRAY))
#define DEM_ARRAY_DECLARE(TYPE,NAME,SIZE)                 extern TYPE NAME[SIZE]
#define DEM_ARRAY_DECLARE_CONST(TYPE,NAME,SIZE)           extern const TYPE NAME[SIZE]
#define DEM_ARRAY_DEFINE(TYPE,NAME,SIZE)                  TYPE NAME[SIZE]
#define DEM_ARRAY_DEFINE_CONST(TYPE,NAME,SIZE,INITVALUE)  const TYPE NAME[SIZE] = INITVALUE
#define DEM_ARRAY_FUNCPARAM(TYPE,NAME)                    TYPE NAME[]
#define DEM_ARRAY_CONSTFUNCPARAM(TYPE,NAME)               const TYPE NAME[]
#define DEM_SIZEOF_VAR(x)                sizeof(x)
#define DEM_SIZEOF_TYPE(x)               sizeof(x)
#endif

#endif

