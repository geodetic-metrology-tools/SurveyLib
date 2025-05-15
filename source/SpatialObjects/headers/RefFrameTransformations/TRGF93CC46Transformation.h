

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
