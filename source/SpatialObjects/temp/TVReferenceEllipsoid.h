//  TVReferenceEllipsoid.h
//
/** A Purely abstract base class for a geodetic reference ellipsoid. 
  
    Patterns:
  
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_V_REFERENCE_ELLIPSOID
#define SU_V_REFERENCE_ELLIPSOID


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include  <string>
using namespace std;
//
class  TAngle;
//#include  "##classname##.h"
// typedefs
typedef double EllipseParameter;
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TVReferenceEllipsoid //: public TObject  
{
public:
	/**@name Member Functions */
	//@{
		/// return ellipsoid name
		virtual string  getName()  const = 0;

		/// return major semi-axis value
		virtual EllipseParameter  getA()  const = 0;

		/// return eccentricity value
		virtual EllipseParameter  getE()  const = 0;

		/// return the square of eccentricity value
		virtual EllipseParameter  getESquared()  const = 0;

		/// return the flattening value
		virtual EllipseParameter  getF()   const = 0;

		/// return minor semi-axis value
		virtual EllipseParameter  getB()  const = 0;

		/// return second eccentricity value
		virtual EllipseParameter  getEPrime()  const = 0;

		/// return the square of second eccentricity value
		virtual EllipseParameter  getEPrimeSquared()  const = 0;

		/** Get the Radius of Curvature of the Ellipsoid in the Prime Vertical
		    at a given latitude.

			@param  phi the latitude
		 */
		virtual EllipseParameter  getNu( const TAngle& phi )  const = 0;
		
		/** Get the Radius of Curvature of the Ellipsoid in the Prime Vertical
		    at a given latitude.

			@param  phi the latitude in radians
		 */
		virtual EllipseParameter  getNu( const double phi )  const = 0;

		/** Get the Radius of Curvature of the Ellipsoid in the Meridian
		    at a given latitude.

			@param  phi the latitude
		 */
		virtual EllipseParameter  getRho( const TAngle& phi )  const = 0;

		/** Get the Radius of Curvature of the Ellipsoid in the Meridian
		    at a given latitude.

			@param  phi the latitude in radians
		 */
		virtual EllipseParameter  getRho( const double phi )  const = 0;

		/** Get the Euler's Radius of Curvature of the Ellipsoid
		    at a given latitude, and azimuth.

			@param  phi the latitude
			@param  alpha the azimuth
		 */
		virtual EllipseParameter  getEuler( const TAngle& phi, const TAngle& alpha )  const = 0;

		/** Get the Euler's Radius of Curvature of the Ellipsoid
		    at a given latitude, and azimuth.

			@param  phi the latitude in radians
			@param  alpha the azimuth in radians
		 */
		virtual EllipseParameter  getEuler( const double phi, const double alpha )  const = 0;
	//@}


protected:


private:

	//ClassDef(TVReferenceEllipsoid, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////




#endif // SU_V_REFERENCE_ELLIPSOID
