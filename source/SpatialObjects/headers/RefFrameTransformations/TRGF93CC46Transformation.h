/*
© Copyright CERN 2000-2019. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch

Modification Feb. 2022:
After the update of the definition of the french coordinate system, RGF93 and ETRF are no more equivalent
*/

#ifndef SURVEYLIB_TRGF93ZONE_TRANSFORMATION
#define SURVEYLIB_TRGF93ZONE_TRANSFORMATION

#include  <TARefFrameTransformation.h>
#include  <TSpatialPosition.h>

class TRGF93ZoneTransformation : public TARefFrameTransformation
{
public:
    explicit TRGF93ZoneTransformation(bool fromRGF93, bool ellipsHeight);

    TRGF93ZoneTransformation * clone() const;
	TRGF93ZoneTransformation * inverse() const;

    TAReferenceFrame * getSourceFrame() const;
	TAReferenceFrame * getDestinationFrame() const;

    bool transform( TPositionVector & pv) const;
   
private:
	TRGF93ZoneTransformation& operator=(const TRGF93ZoneTransformation&);
    enum { kMaxIter = 1000 };
    bool transformFromRGF93(TPositionVector & pv) const;
    bool transformToRGF93(TPositionVector & pv) const;

    const bool fFromRGF93;
	const bool fEllipsHeight;
};

#endif
