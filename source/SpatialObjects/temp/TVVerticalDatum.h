//  TVVerticalDatum.h
//
/** Purely Abstract Base Class for a Vertical Geodetic Datum.
  
    Patterns:
  
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_V_VERTICAL_DATUM
#define SU_V_VERTICAL_DATUM


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
//#include  <##classname##>
//using namespace std;
//
class  TSpatialPoint;
#include  "TGeoidValues.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TVVerticalDatum //: public TObject  
{
public:

	/**@name Member Functions */
	//@{
		/// Returns the name of the geoid
		virtual  string	 getName()  const = 0;

		/// Returns the geoidal undulation (geoidal height) at the given Point's position	
		virtual  GeoidValue getN( const TSpatialPoint& ) const = 0;
		
		/// Returns the deflection of the vertical in the prime vertical at the given Point's position	
		virtual  GeoidValue getEta( const TSpatialPoint& ) const = 0;
		
		/// Returns the deflection of the vertical in the meridian at the given Point's position	
		virtual  GeoidValue getXi( const TSpatialPoint& ) const = 0;
		
		/// Returns the Laplace correction at the given Point's position	
		virtual  GeoidValue getDAlpha( const TSpatialPoint& ) const = 0;
		
		/// Returns all the geoid values at the given Point's position	
		virtual	 TGeoidValues getGeoidValues( const TSpatialPoint& ) const =0;


		/// Returns the geoidal undulation (geoidal height) at the given position	
		virtual  GeoidValue getN( const TSpatialPosition& ) const = 0;
		
		/// Returns the deflection of the vertical in the prime vertical at the given position	
		virtual  GeoidValue getEta( const TSpatialPosition& ) const = 0;
		
		/// Returns the deflection of the vertical in the meridian at the given position	
		virtual  GeoidValue getXi( const TSpatialPosition& ) const = 0;
		
		/// Returns the Laplace correction at the given position	
		virtual  GeoidValue getDAlpha( const TSpatialPosition& ) const = 0;
		
		/// Returns all the geoid values at the given position	
		virtual	 TGeoidValues getGeoidValues( const TSpatialPosition& ) const =0;

	//@}


protected:


private:

	//ClassDef(TVVerticalDatum, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_V_VERTICAL_DATUM
