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
double bilinearInterpolation(float q11, float q12, float q21, float q22, float x1, float x2, float y1, float y2, float x, float y);

/// Convert RGF-IGN69 altitude into GRS80 ellipsoidal height using RAF20 altimetric conversion grid
void circeTransfoRafToH(const double &latitude_rgf93_rad, const double &longitude_rgf93_rad, double &h);

/// Convert GRS80 ellipsoidal height into RGF-IGN69 altitude using RAF20 altimetric conversion grid
void circeTransfoHToRaf(const double &latitude_rgf93_rad, const double &longitude_rgf93_rad, double &h);


std::ifstream& GotoLine(std::ifstream &file, unsigned int num);


}


#endif
