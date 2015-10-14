#ifndef _CONSTANTS_H_
#define __CONSTANTS_H__H_

/*!
   \file
   Global definitions and includes shared among the classes.
*/

#include <string>
#include <cassert>
#include <stdexcept>
#include "Quad.h"


#define assert3D(x) assert((x) >= 0 && (x) < 3)
#define assert4D(x) assert((x) >= 0 && (x) < 4)

#ifndef M_PI
#define M_PI 3.141592653589793238462
#endif

static const TReal RAD2RAD = 1.0;
static const TReal DEG2RAD = M_PI / 180.0;
static const TReal RAD2DEG = 180.0 / M_PI;
static const TReal GON2RAD = M_PI / 200.0;
static const TReal RAD2GON = 200.0 / M_PI;
static const TReal CC2RAD = GON2RAD*1e-4;
static const TReal RAD2CC = RAD2GON*1e+4;

static const TReal PI = M_PI;
static const TReal TWOPI = 2*M_PI;
static const TReal PI_2 = M_PI*0.5;
static const TReal PI_4 = M_PI*0.25;

static const TReal MM2M = 0.001;
static const TReal M2MM = 1000;

#endif