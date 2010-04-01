//  TLocalGeodeticRefFrame.h
//
/** A Geodetic Ellisoidal Reference Frame. 
    Deals with requests for Spatial Position coordinates
    appropriate to a Geodetic reference frame.

  
    Patterns:
    A concrete STATE of a Spatial Position
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_LOC_GEODETIC_REFERENCE_FRAME
#define SU_LOC_GEODETIC_REFERENCE_FRAME


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include  <string>
using namespace std;
//
class  TSpatialPosition;
//class  TGraph;
class  TReferenceEllipsoid;
class TGeodeticRefFrame;
#include  "TA3DEuclideanRefFrame.h"

// typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TLocalGeodeticRefFrame : public TA3DEuclideanRefFrame //: public TObject  
{
public:
	
	/**@name Constructors and Destructors */
	//@{
		/// Constructor taking the name of the reference frame
		TLocalGeodeticRefFrame( const string& name, TReferenceEllipsoid* ellipsoid,
			const TSpatialPosition spos, const TFreeVector falseOrigin,
			const TRotationMatrix orientation, TGeodeticRefFrame* GRF);

		/// Constructor taking the name of the reference frame, the geoid id.,
		/// the origin and the false origin in CCS and the beam gis. and slope
		TLocalGeodeticRefFrame( const string& name, TSpatialPosition origin,
			TFreeVector falseOrigin, const TAngle gis, const TAngle slope);

		/// Destructor
		virtual  ~TLocalGeodeticRefFrame();
	//@}


	/**@name Member Functions */
	//@{
		/// Return a pointer to a clone of this reference frame
		//virtual TVReferenceFrame*  clone() const;

		
		//!sets the sigmaXX of the given Spatial Position Error
		virtual bool setSigmaXX( TSpatialPositionError*, const TLength &);
		//!sets the sigmaYY of the given Spatial Position Error
		virtual bool setSigmaYY( TSpatialPositionError*, const TLength &);
		//!sets the sigmaZZ of the given Spatial Position Error
		virtual bool setSigmaZZ( TSpatialPositionError*, const TLength &);
		//!sets the sigmaXY of the given Spatial Position Error
		virtual bool setSigmaXY( TSpatialPositionError*, const TLength &);
		//!sets the sigmaXZ of the given Spatial Position Error
		virtual bool setSigmaXZ( TSpatialPositionError*, const TLength &);
		//!sets the sigmaYZ of the given Spatial Position Error
		virtual bool setSigmaYZ( TSpatialPositionError*, const TLength &);
	
		

		
		
		/// sets the X Cartesian coordinate status of the given Spatial Position
		virtual bool  setXCoordStatus( TPositionStatus*, TANumericValue::EStatus);
		/// sets the Y Cartesian coordinate status of the given Spatial Position
		virtual bool  setYCoordStatus( TPositionStatus*, TANumericValue::EStatus);
		/// sets the Z Cartesian coordinate status of the given Spatial Position
		virtual bool  setZCoordStatus( TPositionStatus*, TANumericValue::EStatus);
		/// sets the 3D Cartesian coordinates status of the given Spatial Position
		virtual bool  setPositionStatus(  TPositionStatus*, TPositionStatus::EPositionStatus );
		
		
					
		//! returns the sigmaXX of the given Spatial Position Error
		virtual TLength getSigmaXX(const TSpatialPositionError* ) const;
		//! returns the sigmaYY of the given Spatial Position Error
		virtual TLength getSigmaYY(const TSpatialPositionError* ) const;
		//! returns the sigmaZZ of the given Spatial Position Error
		virtual TLength getSigmaZZ(const TSpatialPositionError* ) const;
		//! returns the sigmaXY of the given Spatial Position Error
		virtual TLength getSigmaXY(const TSpatialPositionError* ) const;
		//! returns the sigmaXZ of the given Spatial Position Error
		virtual TLength getSigmaXZ(const TSpatialPositionError* ) const;
		//! returns the sigmaYZ of the given Spatial Position Error
		virtual TLength getSigmaYZ(const TSpatialPositionError* ) const;



		/// returns the X coordinate status
		virtual TANumericValue::EStatus  getXCoordStatus( const TPositionStatus* ) const;
		/// returns the Y coordinate status
		virtual TANumericValue::EStatus  getYCoordStatus( const TPositionStatus* ) const;
		/// returns the Z coordinate status
		virtual TANumericValue::EStatus  getZCoordStatus( const TPositionStatus* ) const;
		//! gets the 3D Cartesian coordinates status of the given Spatial Position
		virtual TPositionStatus::EPositionStatus  getPositionStatus( const TPositionStatus*) const;



		/// Returns a pointer to the references ellipsoid
		TReferenceEllipsoid* getReferenceEllipsoid() const;

		/// Returns the origin of the local RF
		TSpatialPosition getOrigin() const { return fOrigin; }

		/// Returns the geodetic system for the local RF
		TGeodeticRefFrame* getGeodeticRF() const { return fGeodeticSys; }

			/// Returns the false origin of the modified local RF
		TFreeVector getFalseOrigin() const { return fFalseOrigin; }

		/// Returns the orientation matrix 
		TRotationMatrix getOrientation() const { return fOrientationMatrix; }

		/// Returns the local geodetic system for the modified local RF
		TLocalGeodeticRefFrame* getLocGeodeticRefFrame() const { return fLocGeodeticSys; }





		/// returns a boolean indicating the if X coordinate,, is known
		virtual bool  isXCoordKnown( const TSpatialPosition* ) const;
		/// returns a boolean indicating the if Y coordinate,, is known
		virtual bool  isYCoordKnown( const TSpatialPosition* ) const;
		/// returns a boolean indicating the if Z coordinate,, is known
		virtual bool  isZCoordKnown( const TSpatialPosition* ) const;


		//! transforms a spatial position with an affine transformation, if possible
		virtual bool transform( TSpatialPosition* sp, TVAffineTransformation* trans);

		//! transform a position from a reference frame to CGRF
		bool transformToCGRF( TSpatialPosition* sp );

		//! transform a position from CGRF to another reference frame
		bool transformFromCGRF( TSpatialPosition* sp );



		//! transforms a spatial vector with an affine transformation, if possible
		virtual bool transform( TSpatialVector* sv, TVAffineTransformation* trans);



	//@}


protected:


private:
	// We don't want these accessible
	// Copy Constructor 
	TLocalGeodeticRefFrame( const TLocalGeodeticRefFrame& );

	// Copy Assignment Operator 
	TLocalGeodeticRefFrame& operator=( const TLocalGeodeticRefFrame& );
	
	// constants
	static const double precisionH;
	static const double precisionPhi;

	//typedef
	typedef struct {double phi; double lambda; double h;} TGeodeticCoords;

	

private:
	
	TSpatialPosition			fOrigin;
	TReferenceEllipsoid*		fEllipsoid;
	TGeodeticRefFrame*			fGeodeticSys;

	TFreeVector					fFalseOrigin;
	TRotationMatrix				fOrientationMatrix;
	TLocalGeodeticRefFrame*		fLocGeodeticSys;


};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_GEODETIC_REFERENCE_FRAME
