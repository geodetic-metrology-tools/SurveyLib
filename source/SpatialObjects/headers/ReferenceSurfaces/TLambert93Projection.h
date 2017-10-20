/*
© Copyright CERN 2000-2017. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SURVEYLIB_TLANBERT93_PROJECTION_612FCB01_8A89_4cff_A962_A709D25C2195
#define SURVEYLIB_TLANBERT93_PROJECTION_612FCB01_8A89_4cff_A962_A709D25C2195

#include <TA2DPlus1MapProjection.h>
#include <string>

class TLambert93Projection : public TA2DPlus1MapProjection
{
public:
    TLambert93Projection(const std::string & name) : TA2DPlus1MapProjection(name) {}
};

#endif