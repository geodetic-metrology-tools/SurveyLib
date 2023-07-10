/*
© Copyright CERN 2000-2012. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch

/** Conversion between projected and ellipsoidal coordinates using transverse mercator projection
* The tranverse mercator is defined as follow:
* scale factor on central meridian : 1.00006
* Central meridian (center of the FCC) : 6.14°
* False easting and false northing: 0
* Ellipsoid: GRS 80

It is valid for the CGRF

*/

#ifndef SURVEYLIB_GEODETIC_2_MERCATORPROJECTION
#define SURVEYLIB_GEODETIC_2_MERCATORPROJECTION


#include <TARefFrameTransformation.h>
#include <TSpatialPosition.h>

class TGeodetic2Mercator : public TARefFrameTransformation
{
public:
	explicit TGeodetic2Mercator(bool fromGeodetic);

	TGeodetic2Mercator *clone() const;
	TGeodetic2Mercator *inverse() const;

	TAReferenceFrame *getSourceFrame() const;
	TAReferenceFrame *getDestinationFrame() const;

	bool transform(TPositionVector &pv) const;

private:
	TGeodetic2Mercator &operator=(const TGeodetic2Mercator &);
	enum
	{
		kMaxIter = 1000
	};
	bool transformFromGeodetic(TPositionVector &pv) const;
	bool transformToGeodetic(TPositionVector &pv) const;

	/// Convert latitude to isometric latitude
	double latTolatIso(double first_e, double phi_rad) const;

	/// Convert isometric latitude to latitude
	double latIsoTolat(double first_e, double latIso_rad) const;

	/// compute development of the meridional arc
	double devMeridianArc(double first_e, double phi_rad) const;

	/// compute nb factorial (nb!)
	double factorial(int nb) const;

	const bool fFromGeodetic;
};

#endif
