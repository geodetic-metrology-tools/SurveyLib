/*
© Copyright CERN 2000-2019. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SURVEYLIB_TRGF93ZONE_TRANSFORMATION
#define SURVEYLIB_TRGF93ZONE_TRANSFORMATION

#include  <TARefFrameTransformation.h>
#include  <TSpatialPosition.h>

class TRGF93ZoneTransformation : public TARefFrameTransformation
{
public:
    explicit TRGF93ZoneTransformation(bool fromETRF93);

    TRGF93ZoneTransformation * clone() const;
	TRGF93ZoneTransformation * inverse() const;

    TAReferenceFrame * getSourceFrame() const;
	TAReferenceFrame * getDestinationFrame() const;

    bool transform( TPositionVector & pv) const;
   
private:
	TRGF93ZoneTransformation& operator=(const TRGF93ZoneTransformation&);
    enum { kMaxIter = 1000 };
    bool transformFromETRF93(TPositionVector & pv) const;
    bool transformToETRF93(TPositionVector & pv) const;

    const bool fFromETRF93;    
};

#endif
