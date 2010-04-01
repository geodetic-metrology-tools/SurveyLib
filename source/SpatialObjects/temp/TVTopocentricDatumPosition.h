//  TVTopocentricDatumPosition.h
//
/** A Purely abstract base class representing a set of 
	topocentric Datum Position parameters. 
	

    Patterns:
  
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_V_TOPOCENTRIC_DATUM_POSITION
#define SU_V_TOPOCENTRIC_DATUM_POSITION


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
//#include  <##classname##>
//using namespace std;
//
//class  ##classname##;
#include  "TAngle.h"
#include  "TLength.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TVTopocentricDatumPosition//: public TObject  
{
public:
	/**@name Member Functions */
	//@{
		/// Returns the latitude of the Initial Point
		virtual TAngle  getPhi0()  const = 0;

		/// Returns the longitude of the Initial Point
		virtual TAngle  getLambda0()  const = 0;

		/// Returns the ellipsoidal height of the Initial Point
		virtual TLength  getHe0()  const = 0;

		/// Returns the deflection of the vertical in the prime vertical at the Initial Point	
		virtual TAngle  getEta0() const = 0;
		
		/// Returns the deflection of the vertical in the meridian at the Initial Point	
		virtual TAngle  getXi0() const = 0;
		
		/// Returns the azimuth of the local system y-axis at the Initial Point	
		virtual TAngle  getAlpha0() const = 0;
		
		/// Returns the local system x-coordinate of the Initial Point
		virtual TLength  getX0()  const = 0;

		/// Returns the local system y-coordinate of the Initial Point
		virtual TLength  getY0()  const = 0;

		/// Returns the local system z-coordinate of the Initial Point
		virtual TLength  getZ0()  const = 0;

	//@}


protected:


private:


	//ClassDef(TVTopocentricDatumPosition, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////



#endif // SU_V_TOPOCENTRIC_DATUM_POSITION
