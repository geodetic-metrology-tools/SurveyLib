/*
© Copyright CERN 2000-2022. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SURVEYLIB_TTM_PROJECTION
#define SURVEYLIB_TTM_PROJECTION

#include <string>

#include <TA2DPlus1MapProjection.h>

class TTransverseMercatorProjection : public TA2DPlus1MapProjection
{
public:
	TTransverseMercatorProjection(const std::string &name) : TA2DPlus1MapProjection(name) {}
};

#endif
