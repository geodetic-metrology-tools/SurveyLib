
//
// dist3D.h : definitions of distance functions taking TLength
// objects (x, y, z) as argument

#ifndef SU_DIST3D_FCTS
#define SU_DIST3D_FCTS

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TLength.h"

/* definitions of distance functions taking TLength objects (x, y, z) as argument */
double	dist3D(TLength x1, TLength y1, TLength z1, TLength x2, TLength y2, TLength z2);

#endif

