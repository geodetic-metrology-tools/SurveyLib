/*
© Copyright CERN 2000-2017. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SURVEYLIB_LAMBERT93_B5BA8FC9_95B2_4a26_A763_D842DABC71E2
#define SURVEYLIB_LAMBERT93_B5BA8FC9_95B2_4a26_A763_D842DABC71E2

#include  <TARefFrameTransformation.h>
#include  <TSpatialPosition.h>

class TLambert93Transformation : public TARefFrameTransformation
{
public:
    explicit TLambert93Transformation(bool fromETRF93);

    TLambert93Transformation * clone() const;
	TLambert93Transformation * inverse() const;

    TAReferenceFrame * getSourceFrame() const;
	TAReferenceFrame * getDestinationFrame() const;

    bool transform( TPositionVector & pv) const;
   
private:
    TLambert93Transformation& operator=(const TLambert93Transformation&) = delete;
    enum { kMaxIter = 1000 };
    bool transformFromETRF93(TPositionVector & pv) const;
    bool transformToETRF93(TPositionVector & pv) const;
	
    const bool fFromETRF93;    
};

#endif
