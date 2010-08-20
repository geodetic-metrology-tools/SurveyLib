#ifndef SURVEYLIB_TLV95TRANSFORMATION_4599afe1-7725-409d-8ea5-b2b9f5f3a95a
#define SURVEYLIB_TLV95TRANSFORMATION_4599afe1-7725-409d-8ea5-b2b9f5f3a95a

#include  <TARefFrameTransformation.h>
#include  <TSpatialPosition.h>

class TLV95Transformation : public TARefFrameTransformation
{
public:
    explicit TLV95Transformation(bool fromCH1903plus);

	TLV95Transformation * clone() const;
	TLV95Transformation * inverse() const;

    TAReferenceFrame * getSourceFrame() const;
	TAReferenceFrame * getDestinationFrame() const;

    bool transform( TPositionVector & pv) const;

private:
    const std::size_t kMaxIter = 100;
    bool transformFromCH1903plus(TPositionVector & pv) const;
    bool transformToCH1903plus(TPositionVector & pv) const;

    const bool fFromCH1903plus;
};

#endif
