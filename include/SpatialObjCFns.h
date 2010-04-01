/* C Functions file
 */

#ifndef SPATIALOBJCFNS_H
#define SPATIALOBSCFNS_H
#include <string>
//#include <windows.h>

using namespace std;
#include "TGlobalDefs.h"


#ifdef __cplusplus
extern "C" {  // only need to export C interface if
              // used by C++ source code
#endif

	/// return the N value in meters for the position in CCS corresponding 
	/// to the quad values
	SU_DECLSPEC int DLLAPI getCG2000N0(quad x, quad y, quad* N);
	SU_DECLSPEC int DLLAPI getCG2000NMachine(quad x, quad y, quad* N);
	
	SU_DECLSPEC int DLLAPI getCG1985N0(quad x, quad y, quad* N);
	SU_DECLSPEC int DLLAPI getCG1985NMachine(quad x, quad y, quad* N);


	/// return the (XYZ) position in MLA of a point from the origin of the MLA 
	/// and the point to be transformed both in CCS
	SU_DECLSPEC int DLLAPI transformToMLA(quad x0, quad y0, quad z0,
									quad* x, quad* y, quad* z, char* geoid);

	
	/// return the (XYZ) position in CCS of a point from the origin of the MLA system
	/// in CCS and the point to be transformed in MLA 
	SU_DECLSPEC int DLLAPI transformFromMLA(quad x0, quad y0, quad z0,
									  quad* x, quad* y, quad* z, char* geoid);


	/// return the (XYZ) position in MLA of a point from the origin of the MLA 
	/// and the point to be transformed both in CCS (with slope and bearing equal to 0
	/// and false origin (0,0,0) )
	SU_DECLSPEC int DLLAPI transformToMLA2(quad x0, quad y0, quad z0,
									quad* x, quad* y, quad* z, char* geoid);


	/// return the (XYZ) position in CCS of a point from the origin of the MLA system
	/// in CCS and the point to be transformed in MLA (with slope and bearing equal to 0
	/// and false origin (0,0,0) )
	SU_DECLSPEC int DLLAPI transformFromMLA2(quad x0, quad y0, quad z0,
									  quad* x, quad* y, quad* z, char* geoid);


	/// return coordinates as X,Y,h of a point at H metres on the vertical of another point
	SU_DECLSPEC int DLLAPI descenteVert(quad x, quad y, quad h, quad deltaH,
							quad* xt, quad* yt, quad* ht);
	

#ifdef __cplusplus
}
#endif
#endif;
