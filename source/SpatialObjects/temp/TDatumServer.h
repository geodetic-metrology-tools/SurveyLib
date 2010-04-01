//  TDatumServer.h
//
/** A class that instantiates the complete set of available horizontal 
    and vertical datums (coordinate surfaces), and provides access to 
	them.

  
    Patterns:
	A singleton to ensure only one such server exists.
  
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_DATUM_SERVER
#define SU_DATUM_SERVER


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
//#include  <##classname##>
//using namespace std;
//
class  TVReferenceEllipsoid;
class  TReferenceEllipsoid;
class  TVGeoid;
class  TCernParabolicGeoid;
class  TVTopocentricDatumPosition;
class  TTopocentricDatumPosition;
//#include  "##classname##.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TDatumServer //: public TObject  
{
public:
	/**@name Constants */
	//@{
		enum  EEllipsoid { kGRS80, kWGS84Ell, kInternational, kCERNSPS };
		enum  EGeoid { kCERNLEP, kCERNSurf };
		enum  EDatum { kCERNGRF };
	//@}


	/**@name Member Functions */
	//@{
		/// Instance method to obtain a pointer to the TDatumServer instance
		static	TDatumServer*  instance();

		/// Get a pointer to the specified reference ellipsoid
		TVReferenceEllipsoid*  getRefEllipsoid( EEllipsoid );
		
		/// Get a pointer to the specified geoid model
		TVGeoid*  getGeoid( EGeoid );
		
		/// Get a pointer to the specified topocentric Datum Position
		TVTopocentricDatumPosition*  getTopoDatumPosition( EDatum );

	//@}


protected:
	/**@name Protected Constructors and Destructors */
	//@{
		/// Default Constructor 
		TDatumServer();

		/// Destructor
		virtual  ~TDatumServer();
	//@}




private:
	// Private Member Functions
	// Copy Constructor 
	TDatumServer(const  TDatumServer&);

	// Copy Assignment Operator 
	TDatumServer& operator=( const TDatumServer& );
	

	// Reference Ellipsoid constructors

	// return a pointer to a reference ellipsoid with the GRS80 ellipsoid parameters
	TVReferenceEllipsoid*  getGRS80();

	// return a pointer to a reference ellipsoid with the WGS84 ellipsoid parameters
	TVReferenceEllipsoid*  getWGS84Ell();

	// return a pointer to a reference ellipsoid with the International ellipsoid parameters
	TVReferenceEllipsoid*  getInternational();

	// return a pointer to a reference ellipsoid with the CERN SPS sphere parameters
	TVReferenceEllipsoid*  getCERNSPS();
	

	// Geoid Model constructors

	// return a pointer to a CERN parabolic geoid model with the surface model parameters
	TVGeoid*  getCERNSurf();

	// return a pointer to a CERN parabolic geoid model with the Lep model parameters
	TVGeoid*  getCERNLEP();


	// Datum Position constructors

	// return a pointer to a topocentric datum position with the CERN GRF parameters
	TVTopocentricDatumPosition*  getCGRFPosition();


private:
	static	TDatumServer*  fInstance;

	static  TReferenceEllipsoid*  fGRS80;
	static  TReferenceEllipsoid*  fWGS84Ell;
	static  TReferenceEllipsoid*  fInternational;
	static  TReferenceEllipsoid*  fCERNSPS;

	static  TCernParabolicGeoid*  fCERNSurf;
	static  TCernParabolicGeoid*  fCERNLEP;

	static  TTopocentricDatumPosition*  fCGRFPosition;

	//ClassDef(TDatumServer, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////



#endif // SU_DATUM_SERVER
