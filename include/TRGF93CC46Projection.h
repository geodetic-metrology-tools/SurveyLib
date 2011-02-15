#ifndef SURVEYLIB_TRGF93REFERENCEFRAME
#define SURVEYLIB_TRGF93REFERENCEFRAME

#include <TA2DPlus1MapProjection.h>
#include <string>

class TRGF93ZoneReferenceFrame : public TA2DPlus1MapProjection
{
public:
    TRGF93ZoneReferenceFrame(const std::string & name) : TA2DPlus1MapProjection(name) {}
};

#endif
