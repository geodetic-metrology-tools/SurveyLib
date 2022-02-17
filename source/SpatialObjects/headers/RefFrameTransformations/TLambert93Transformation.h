/*
© Copyright CERN 2000-2019. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch

Modification Feb. 2022:
After the update of the definition of the french coordinate system, RGF93 and ETRF are no more equivalent
*/

#ifndef SURVEYLIB_LAMBERT93_B5BA8FC9_95B2_4a26_A763_D842DABC71E2
#define SURVEYLIB_LAMBERT93_B5BA8FC9_95B2_4a26_A763_D842DABC71E2

#include  <TARefFrameTransformation.h>
#include  <TSpatialPosition.h>

class TLambert93Transformation : public TARefFrameTransformation
{
public:
    explicit TLambert93Transformation(bool fromRGF93, bool ellipsHeight);

    TLambert93Transformation * clone() const;
	TLambert93Transformation * inverse() const;

    TAReferenceFrame * getSourceFrame() const;
	TAReferenceFrame * getDestinationFrame() const;

    bool transform( TPositionVector & pv) const;
   
private:
    TLambert93Transformation& operator=(const TLambert93Transformation&) = delete;
    enum { kMaxIter = 1000 };
    bool transformFromRGF93(TPositionVector & pv) const;
    bool transformToRGF93(TPositionVector & pv) const;

    const bool fFromRGF93;
	const bool fEllipsHeight;
};

#endif
