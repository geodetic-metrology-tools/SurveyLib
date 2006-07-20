//  TTopocentricDatumPosition.h
//
/** A simple class representing a set of topocentric
    Dataum Position parameters.
  
    Patterns:
  
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_TOPOCENTRIC_DATUM_POSITION
#define SU_TOPOCENTRIC_DATUM_POSITION


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include  <string>
using namespace std;
//
//class  ##classname##;
#include  "TVTopocentricDatumPosition.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TTopocentricDatumPosition : public TVTopocentricDatumPosition //: public TObject  
{
public:
	/**@name Constructors and Destructors */
	//@{
		/// Constructor taking the name of the datum
		TTopocentricDatumPosition( const string& name ) : fDatumName( name ) {}

		/// Destructor
		virtual  ~TTopocentricDatumPosition();
	//@}


	/**@name Member Functions */
	//@{
		/// Assigns the latitude of the Initial Point
		void  setPhi0( const TAngle& ang )  {fPhi0 = ang; return; }

		/// Assigns the longitude of the Initial Point
		void  setLambda0( const TAngle& ang )  {fLambda0 = ang; return; }

		/// Assigns the ellipsoidal height of the Initial Point
		void  setHe0( const TLength& len )  {fHe0 = len; return; }

		/// Assigns the deflection of the vertical in the prime vertical at the Initial Point	
		void  setEta0( const TAngle& ang )  {fEta0 = ang; return; }
		
		/// Assigns the deflection of the vertical in the meridian at the Initial Point	
		void  setXi0( const TAngle& ang )  {fXi0 = ang; return; }
		
		/// Assigns the azimuth of the local system y-axis at the Initial Point	
		void  setAlpha0( const TAngle& ang )  {fAlpha0 = ang; return; }
		
		/// Assigns the local system x-coordinate of the Initial Point
		void  setX0( const TLength& len )  {fX0 = len; return; }

		/// Assigns the local system y-coordinate of the Initial Point
		void  setY0( const TLength& len )  {fY0 = len; return; }

		/// Assigns the local system z-coordinate of the Initial Point
		void  setZ0( const TLength& len )  {fZ0 = len; return; }

		/// Returns the latitude of the Initial Point
		virtual TAngle  getPhi0()  const  { return fPhi0; }

		/// Returns the longitude of the Initial Point
		virtual TAngle  getLambda0()  const  { return fLambda0; }

		/// Returns the ellipsoidal height of the Initial Point
		virtual TLength  getHe0()  const  { return fHe0; }

		/// Returns the deflection of the vertical in the prime vertical at the Initial Point	
		virtual TAngle  getEta0() const  { return fEta0; }
		
		/// Returns the deflection of the vertical in the meridian at the Initial Point	
		virtual TAngle  getXi0() const  { return fXi0; }
		
		/// Returns the azimuth of the local system y-axis at the Initial Point	
		virtual TAngle  getAlpha0() const  { return fAlpha0; }
		
		/// Returns the local system x-coordinate of the Initial Point
		virtual TLength  getX0()  const  { return fX0; }

		/// Returns the local system y-coordinate of the Initial Point
		virtual TLength  getY0()  const  { return fY0; }

		/// Returns the local system z-coordinate of the Initial Point
		virtual TLength  getZ0()  const  { return fZ0; }

	//@}


protected:


private:
	/// Copy Constructor 
	TTopocentricDatumPosition(const  TTopocentricDatumPosition&);

	/// Copy Assignment Operator 
	TTopocentricDatumPosition& operator=( const TTopocentricDatumPosition& );


private:
	string  fDatumName;

	TAngle  fPhi0;
	TAngle  fLambda0;
	TLength  fHe0;
	TAngle  fEta0;
	TAngle  fXi0;
	TAngle  fAlpha0;
	TLength  fX0;
	TLength  fY0;
	TLength  fZ0;


	//ClassDef(TTopocentricDatumPosition, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////




#endif // SU_TOPOCENTRIC_DATUM_POSITION
