/*
© Copyright CERN 2000-2017. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SURVEYLIB_TRGF93_PROJECTION
#define SURVEYLIB_TRGF93_PROJECTION

#include <TA2DPlus1MapProjection.h>
#include <string>

class TRGF93CC46Projection : public TA2DPlus1MapProjection
{
public:
    TRGF93CC46Projection(const std::string & name) : TA2DPlus1MapProjection(name) {}
};

#endif
