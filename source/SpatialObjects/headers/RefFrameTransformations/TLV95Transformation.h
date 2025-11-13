/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef SURVEYLIB_TLV95TRANSFORMATION_4599afe1_7725_409d_8ea5_b2b9f5f3a95a
#define SURVEYLIB_TLV95TRANSFORMATION_4599afe1_7725_409d_8ea5_b2b9f5f3a95a

#include  <TARefFrameTransformation.h>
#include  <TSpatialPosition.h>

class TLV95Transformation : public TARefFrameTransformation
{
public:
	explicit TLV95Transformation(bool fromCH1903plus, std::string fVerticalDatum);

	TLV95Transformation * clone() const;
	TLV95Transformation * inverse() const;

    TAReferenceFrame * getSourceFrame() const;
	TAReferenceFrame * getDestinationFrame() const;

    bool transform( TPositionVector & pv) const;

private:
    enum { kMaxIter = 1000 };
    bool transformFromCH1903plus(TPositionVector & pv) const;
    bool transformToCH1903plus(TPositionVector & pv) const;

    const bool fFromCH1903plus;
	const std::string fVerticalDatum;
	
	TLV95Transformation & operator=(const TLV95Transformation&);  // non copyable
};

#endif
