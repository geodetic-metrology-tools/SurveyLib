

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
