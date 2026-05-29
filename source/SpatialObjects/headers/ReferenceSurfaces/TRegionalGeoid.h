/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

//  TRegionalGeoid.h

/** Grid defined to model a regional geoid (or quasi-geoid).
	A regional geoid is a geoid model defined for a specific region, and is based on a grid of values (geoidal height or height anomaly).
	Values are given with respect to a reference ellipsoid
	Values are interpolated to obtain the geoid parameters at any given point within the region.

	Concrete Class derived from TAGeoidModel.


	Patterns:

*/
//////////////////////////////////////////////////////////////////////

#ifndef REGIONAL_GEOID
#define REGIONAL_GEOID

#include <gdal_raster_cpp.h>

#include "TAGeoidModel.h"

/*! \ingroup spatialobjects
	@{*/

//! Concrete Class derived from TAGeidModel
class TRegionalGeoid : public TAGeoidModel
{
public:
	/**@name Constructors and Destructors */
	//@{
	/// default constructor
	TRegionalGeoid();

	/// cconstructor taking the name, the definition reference frame and ellipsoid, the calculation reference frame and the path to the geoid grid file
	TRegionalGeoid(const std::string &name,
		const TRefSystemFactory::EGeoid &geoidId,
		TAReferenceFrame *def,
		TReferenceEllipsoid *ell,
		TAReferenceFrame *calc,
		const std::string &pathToFile,
		const int &epsgCode = 4345, //ETRS89
		const GDALRIOResampleAlg &interpolationMethod = GRIORA_Bilinear);

	/// Destructor
	virtual ~TRegionalGeoid();
	//@}

	/**@name Member Functions */
	//@{
	/// Returns the geoidal undulation (geoidal height) at the given Point's position
	virtual TLength getN(const TSpatialPosition &) const;

	/// Returns the deflection of the vertical in the prime vertical at the given Point's position (Pizzeti correction, i.e. at the geoid level)
	virtual TAngle getEta(const TSpatialPosition &) const;

	/// Returns the deflection of the vertical in the meridian at the given Point's position (Pizzeti correction, i.e. at the geoid level)
	virtual TAngle getXi(const TSpatialPosition &) const;

	/// Returns the Laplace correction at the given Point's position (phi is given)
	// virtual TAngle getDAlpha(const TSpatialPosition &, const TAngle &) const;

	/// Return true if the point is in the grid
	bool isInGrid(const TSpatialPosition &point) const;
	//@}

private:
	/**@name Private Functions */
	//@{

	GDALDataset *openGDALDataset() const;

	bool getXAndYFromSpatialPosition(const TSpatialPosition &sp, TReal &x, TReal &y, const OGRSpatialReference &geoidSRS) const;

	bool prepareXiAndEtaComputation(const TSpatialPosition &sp, TReal &deltaN, TAngle &lambdaOrPhi, TAngle &gridSpacing, const std::string &xiOrEta) const;

	bool getNatCornerAroundPoint(const TReal &xPoint,
		const TReal &yPoint,
		const GDALDataset *dataset,
		const TReal &gridSpacingX,
		const TReal &gridSpacingY,
		TReal &n_XBefore_Y,
		TReal &n_XAfter_Y,
		TReal &n_X_YBefore,
		TReal &n_X_YAfter) const;

	// Compute the normal curvature of the plumb line
	TAngle normalPlumbLineCurvature(const TAngle &phi, const TLength h_km) const;

	/*!Generate message for the NotInGeoidGridException*/
	std::stringstream generateNotInGeoidGridMessage(const std::string &functionCalled, const TSpatialPosition &position) const;

	//@}

	/**@name Member Attributes */
	//@{
	std::string fPathToFile; /*! path to the geoid grid file */

	int fEPSGCode = 4345; /*! EPSG code of the geoid grid. 4345 (ETRS89 3D geographic) is default value  */
	GDALRIOResampleAlg fInterpolationMethod = GRIORA_Bilinear; /*! Prefered interpolation method*/
	//@}
};

#endif // CERN_FCC_GEOID
