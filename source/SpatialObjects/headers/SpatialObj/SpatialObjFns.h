/*
© Copyright CERN 2000-2024. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SPATIALOBJFNS_H
#define SPATIALOBSFNS_H
#include <string>

//#include "TGlobalDefs.h"

class  SpatialObjFns  
{
public:
	SpatialObjFns();
	/// return the N value in meters for the position in CCS corresponding 
	/// to the double values
	static int  getCG2000N0(double x, double y, double* N);
	static int  getCG2000NMachine(double x, double y, double* N);
	
	static int getCG1985N0(double x, double y, double* N);
	static int getCG1985NMachine(double x, double y, double* N);
	static int getCG1985NMachineGrid(double x, double y, double* N);

	static int getCGSphereN(double x, double y, double* N);

	/// return the deflection of the vertical values (in gon) depending on the geoid
	// Returns the deflection of the vertical in the prime vertical at the given Point's position (North-South)
	static int getXiGon(double x, double y, double *xsi_gon, const char* geoid);
	// Returns the deflection of the vertical in the meridian at the given Point's position (East-West)
	static int getEtaGon(double x, double y, double *eta_gon, const char* geoid);
	// Returns the Laplace correction at the given Point's position
	static int getDAlphaGon(double x, double y, double *alpha_gon, const char* geoid);

	/// return the (XYZ) position in MLA of a point from the origin of the MLA 
	/// and the point to be transformed both in CCS (with slope and bearing equal to 0
	/// and false origin (0,0,0) )
	static int transformToMLA(double x0, double y0, double z0,
							   double* x, double* y, double* z, char* geoid);


	/// return the (XYZ) position in CCS of a point from the origin of the MLA system
	/// in CCS and the point to be transformed in MLA (with slope and bearing equal to 0
	/// and false origin (0,0,0) )
	static int transformFromMLA(double x0, double y0, double z0,
								 double* x, double* y, double* z, char* geoid);


	/// return coordinates as X,Y,h of a point at H metres on the vertical of another point
	static int descenteVert(double x, double y, double h, double deltaH,
							double* xt, double* yt, double* ht);

};
#endif
