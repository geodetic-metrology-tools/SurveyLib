/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef SPATIALOBJCFNS_H
#define SPATIALOBSCFNS_H
#include <string>
//#include <windows.h>

#include "TGlobalDefs.h"


#ifdef __cplusplus
extern "C" {  // only need to export C interface if
              // used by C++ source code
#endif

	/// return the N value in meters for the position in CCS corresponding 
	/// to the double values
	SU_DECLSPEC int DLLAPI getCG2000N0(double x, double y, double* N);
	SU_DECLSPEC int DLLAPI getCG2000NMachine(double x, double y, double* N);
	SU_DECLSPEC int DLLAPI getCG2000NTopo(double x, double y, double* N);
	
	SU_DECLSPEC int DLLAPI getCG1985N0(double x, double y, double* N);
	SU_DECLSPEC int DLLAPI getCG1985NMachine(double x, double y, double* N);

	SU_DECLSPEC int DLLAPI getCGSphereN(double x, double y, double* N);

	/// return the deflection of the vertical values (in radians) depending on the geoid
	// Returns the deflection of the vertical in the prime vertical at the given Point's position (North-South)
	SU_DECLSPEC int DLLAPI getXiRadian(double x, double y, double *xi_rad, const char* geoid);
	// Returns the deflection of the vertical in the meridian at the given Point's position (East-West)
	SU_DECLSPEC int DLLAPI getEtaRadian(double x, double y, double *eta_rad, const char* geoid);
	// Returns the Laplace correction at the given Point's position
	SU_DECLSPEC int DLLAPI getDAlphaRadian(double x, double y, double *dAlpha_rad, const char* geoid);

	/// return the (XYZ) position in MLA of a point from the origin of the MLA 
	/// and the point to be transformed both in CCS
	SU_DECLSPEC int DLLAPI transformToMLA(double x0, double y0, double z0,
									double* x, double* y, double* z, char* geoid);

	
	/// return the (XYZ) position in CCS of a point from the origin of the MLA system
	/// in CCS and the point to be transformed in MLA 
	SU_DECLSPEC int DLLAPI transformFromMLA(double x0, double y0, double z0,
									  double* x, double* y, double* z, char* geoid);

	/// return coordinates as X,Y,h of a point at H metres on the vertical of another point
	SU_DECLSPEC int DLLAPI descenteVert(double x, double y, double h, double deltaH,
							double* xt, double* yt, double* ht);
	

#ifdef __cplusplus
}
#endif
#endif
