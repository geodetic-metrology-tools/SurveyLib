/*
© Copyright CERN 2000-2017. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef _SL_CONSTANTS_H_
#define _SL_CONSTANTS_H_

#include "Quad.h"

/*!
   Global definitions and includes shared among the classes.
*/

namespace  {

	static const TReal RAD2RAD = 1.0;
	static const TReal DEG2RAD = M_PI / 180.0;
	static const TReal RAD2DEG = 180.0 / M_PI;
	static const TReal GON2RAD = M_PI / 200.0;
	static const TReal RAD2GON = 200.0 / M_PI;
	static const TReal CC2RAD = GON2RAD*1e-4;
	static const TReal RAD2CC = RAD2GON*1e+4;
	static const TReal GON2CC = 1e+4;
	static const TReal CC2GON = 1e-4;
	
	static const TReal PI = M_PI;
	static const TReal TWOPI = 2*M_PI;
	static const TReal PI_2 = M_PI*0.5;
	static const TReal PI_4 = M_PI*0.25;

	static const TReal MM2M = 0.001;
	static const TReal M2MM = 1000;


	static const TReal NO_VALf = std::numeric_limits<TReal>::quiet_NaN(); //!< marks uninitialized or unused float/real values
	static const int NO_VALi = std::numeric_limits<int>::quiet_NaN(); //!< marks uninitialized or unused integer values
}

#endif