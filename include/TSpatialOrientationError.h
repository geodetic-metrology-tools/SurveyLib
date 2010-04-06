// TSpatialOrientationError.h: 
//
/*  
   Patterns:
  
   
   Copyright 1999,2000 CERN EST/SU. All rights reserved.
*/
////////////////////////////////////////////////////////




#ifndef SU_SPATIAL_ORIENTATION_ERROR
#define SU_SPATIAL_ORIENTATION_ERROR

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////
// Forward declarations
////////////////////////////////////////////////////////

//class  TAngle;
//class  TReferenceEllipsoid;
class  TVReferenceFrame;
#include "T3DMatrix.h"

#include  "TANumericValue.h"
#include  "TLength.h"
#include  "TAngle.h"
#include "counted_ptr.h"
#include "TGraph.h"
#include  "TSpatialStatus.h"

using namespace std;

// typedefs
typedef  real  Component;
typedef  bool  CompKnown;
//
//
/////////////////////////////



//! The Spatial Orientation Error of a point in a given reference frame.
class TSpatialOrientationError  //: public TObject  
{

public:
	friend  class  TAReferenceFrame;

	//typedef  TANumericValue::EStatus  ESigmaStatus;

	/*!@name Constructors and Destructors */
	//@{
//		explicit  TSpatialOrientationError( TReferenceFrameServer::ERefFrame );
	explicit  TSpatialOrientationError( TCoordSysFactory::ECoordSys );
//		TSpatialOrientationError( TSpatialVector*, counted_ptr< TSpatialStatus> );
//	TSpatialVectorError();	
	TSpatialOrientationError( const TSpatialOrientationError& );
	virtual ~TSpatialOrientationError();
	//@}

	//! Copy Assignment Operator 
	TSpatialOrientationError& operator=(const TSpatialOrientationError&);

	/*!@return the variances as a TFreeVector*/
	TFreeVector				getVariances() const;

	/*!@return the variance/covariance as a T3DMatrix*/
	T3DMatrix				getCovariances() const;

	//! set the variances from a 3D-matrix and 
	bool setVariances(const TFreeVector& fv) ;
	//! set the covariances form a 3D-matrix
	bool setCovariances(const T3DMatrix& mx) ;

protected:

private:
	// member attributes
	T3DMatrix  fSigmaMtrx;

//	counted_ptr< TSpatialStatus >  fSigmaStatus;

//	TVReferenceFrame*  fRefFrame;

//	TSpatialVector*  fAssociatedVector;
	
};


/////////////////////
// Inline Definitions
/////////////////////


#endif // SU_SPATIAL_ORIENTATION_ERROR
