#include  "SpatialObjCFns.h"
#include  "SpatialObjFns.h"
#include  "TSpatialPosition.h"
#include  "TGraph.h"
#include  "TRefSystemFactory.h"
#include  "TLength.h"
#include  "TVGeoidModel.h"
#include  "TVReferenceFrame.h"
#include  "TModifiedLocalAstronomicalRF.h"


typedef double double_t;

// N value for CG2000 at 0-level
int DLLAPI  getCG2000N0( double_t  x, double_t  y, double_t* N)
{
	return SpatialObjFns::getCG2000N0(x,y,N);	
}

// N value for CG2000 at LEP-level
int DLLAPI  getCG2000NMachine( double_t  x, double_t  y, double_t* N)
{
	return SpatialObjFns::getCG2000NMachine(x,y,N);
}

// N value for CG1985 at 0-level
int DLLAPI getCG1985N0( double_t  x, double_t  y, double_t* N)
{
	return SpatialObjFns::getCG1985N0(x,y,N);
}

// N value for Sphere
int DLLAPI getCGSphereN(double_t  x, double_t  y, double_t* N)
{
	return SpatialObjFns::getCGSphereN(x, y, N);
}

// N value for CG1985 at LEP-level
int DLLAPI getCG1985NMachine( double_t  x, double_t  y, double_t* N)
{
	return SpatialObjFns::getCG1985NMachine(x,y,N);
}

// N value for CG1985 at LEP-level (using grid)
int DLLAPI getCG1985NMachineGrid(double_t x, double_t y, double_t *N)
{
	return SpatialObjFns::getCG1985NMachineGrid(x, y, N);
}

int DLLAPI transformToMLA(double_t x0, double_t y0, double_t z0,
					double_t* x, double_t* y, double_t* z, char* geoid)
{
	return SpatialObjFns::transformToMLA(x0,y0,z0,x,y,z,geoid);
}

// coordinates transformation from MLA system to CCS
int DLLAPI transformFromMLA(double_t x0, double_t y0, double_t z0,
					  double_t* x, double_t* y, double_t* z, char* geoid)
{
	return SpatialObjFns::transformFromMLA(x0,y0,z0,x,y,z,geoid);
}

// coordinates of a point on the vertical of another
int DLLAPI descenteVert(double_t x, double_t y, double_t h, double_t deltaH, double_t* xt, double_t* yt, double_t* ht)
{
	return SpatialObjFns::descenteVert(x,y,h,deltaH,xt,yt,ht);
}

// Xi (North-South DoV) value (in gons) at Machine level, geoid may be "CG2000_Machine", "CG1985_Machine" and "Sphere"
int DLLAPI getXiGon(double_t x, double_t y, double_t *xi_gon, const char* geoid)
{
	return SpatialObjFns::getXiGon(x, y, xi_gon, geoid);
}

// Eta (East-West DoV) value (in gons) at Machine level, geoid may be "CG2000_Machine", "CG1985_Machine" and "Sphere"
int DLLAPI getEtaGon(double_t x, double_t y, double_t *eta_gon, const char* geoid)
{
	return SpatialObjFns::getEtaGon(x, y, eta_gon, geoid);
}

// DAlpha (Laplace correction) value (in gons) at Machine level, geoid may be "CG2000_Machine", "CG1985_Machine" and "Sphere"
int DLLAPI getDAlpha(double_t x, double_t y, double_t *dAlpha_gon, const char* geoid)
{
	return SpatialObjFns::getDAlphaGon(x, y, dAlpha_gon, geoid);
}
