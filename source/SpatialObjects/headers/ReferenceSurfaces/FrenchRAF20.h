#ifndef __FRENCH_RAF20__
#define __FRENCH_RAF20__

#include <Quad.h>



	/**
	 *
	 * Management of French RAF 20 altimetric conversion grid
	 *
	 *
	 */

namespace FrenchRAF20
{
/// extract the conversion value
double interpolRAF20(const double &latitude_rgf93_deg, const double &longitude_rgf93_deg);

/// Bilinear interpolation
double bilinearInterpolation(double q11, double q12, double q21, double q22, double x1, double x2, double y1, double y2, double x, double y);

/// Convert NGF-IGN69 altitude into GRS80 ellipsoidal height using RAF20 altimetric conversion grid
void circeTransfoRafToH(const double &latitude_rgf93_rad, const double &longitude_rgf93_rad, double &h);

/// Convert GRS80 ellipsoidal height into NGF-IGN69 altitude using RAF20 altimetric conversion grid
void circeTransfoHToRaf(const double &latitude_rgf93_rad, const double &longitude_rgf93_rad, double &h);

//std::ifstream& GotoLine(std::ifstream &file, unsigned int num);
}


#endif
