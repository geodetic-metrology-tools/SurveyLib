#ifndef SURVEYLIB_TLV95REFERENCEFRAME_fbf774f0_9fc2_4c4c_ae17_4c2a804516b8
#define SURVEYLIB_TLV95REFERENCEFRAME_fbf774f0_9fc2_4c4c_ae17_4c2a804516b8

#include <TA2DPlus1MapProjection.h>
#include <string>

class TLV95ReferenceFrame : public TA2DPlus1MapProjection
{
public:
    TLV95ReferenceFrame(const std::string & name) : TA2DPlus1MapProjection(name) {}
};

#endif
