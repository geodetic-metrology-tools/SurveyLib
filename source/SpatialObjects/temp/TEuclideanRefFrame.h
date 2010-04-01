//  TEuclideanRefFrame.h
//
/*
  
    Patterns:
    A concrete STATE of a Spatial Position
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
////////////////////////////////////////////////////////////////////



#ifndef SU_EUCLIDEAN_REFERENCE_FRAME
#define SU_EUCLIDEAN_REFERENCE_FRAME


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


//////////////////////////////////////////////////////////////
// Forward declarations
//
#include  <string>
using namespace std;
//
class  TSpatialPosition;
#include  "TAReferenceFrame.h"
// typedefs
//
//
//////////////////////////////////////////////////////////////



//! A Euclidean Reference Frame. 
 /* Deals with requests for Spatial Position coordinates
    appropriate to a Euclidean reference frame.*/
class  TEuclideanRefFrame : public TAReferenceFrame //: public TObject  
{
public:
	
	/*!@name Constructors and Destructors */
	//@{
		//! Constructor taking the name of the reference frame
		explicit TEuclideanRefFrame( const string& name );

		//! Destructor
		virtual  ~TEuclideanRefFrame();
	//@}


		//! Return a pointer to a clone of this reference frame
		//virtual TVReferenceFrame*  clone() const;

		//! Set the value for the false origin of the reference frame {default (0, 0, 0)}
		void  setFalseOrigin( const TSpatialPosition& origin );

		/*!@name Set methods*/
		//@{
		//! sets the X Cartesian coordinate of the given Spatial Position
		virtual bool  setXCoord( TSpatialPosition*, const TLength & );  
		//! sets the Y Cartesian coordinate of the given Spatial Position
		virtual bool  setYCoord( TSpatialPosition*, const TLength & );  
		//! sets the Y Cartesian coordinate of the given Spatial Position
		virtual bool  setZCoord( TSpatialPosition*, const TLength & );  

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
		
		//! sets the X Cartesian coordinate status of the given Spatial Position
		virtual bool  setXCoordStatus( TPositionStatus*, TANumericValue::EStatus);
		//! sets the Y Cartesian coordinate status of the given Spatial Position
		virtual bool  setYCoordStatus( TPositionStatus*, TANumericValue::EStatus);
		//! sets the Z Cartesian coordinate status of the given Spatial Position
		virtual bool  setZCoordStatus( TPositionStatus*, TANumericValue::EStatus);
		//! sets the 3D Cartesian coordinates status of the given Spatial Position
		virtual bool  setPositionStatus(  TPositionStatus*, TPositionStatus::EPositionStatus );
		//@}
		

		/*!@name Access methods*/
		//@{
		//! returns the X coordinate
		virtual TLength  getXCoord( const TSpatialPosition* ) const;
		//! returns the Y coordinate
		virtual TLength  getYCoord( const TSpatialPosition* ) const;
		//! returns the Z coordinate
		virtual TLength  getZCoord( const TSpatialPosition* ) const;

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

		
		//! returns the X coordinate status
		virtual TANumericValue::EStatus  getXCoordStatus( const TPositionStatus* ) const;
		//! returns the Y coordinate status
		virtual TANumericValue::EStatus  getYCoordStatus( const TPositionStatus* ) const;
		//! returns the Z coordinate status
		virtual TANumericValue::EStatus  getZCoordStatus( const TPositionStatus* ) const;
		//! gets the 3D Cartesian coordinates status of the given Spatial Position
		virtual TPositionStatus::EPositionStatus  getPositionStatus( const TPositionStatus*) const;
		//@}


		//! returns a boolean indicating the if X coordinate,, is known
		virtual bool  isXCoordKnown( const TSpatialPosition* ) const;
		//! returns a boolean indicating the if Y coordinate,, is known
		virtual bool  isYCoordKnown( const TSpatialPosition* ) const;
		//! returns a boolean indicating the if Z coordinate,, is known
		virtual bool  isZCoordKnown( const TSpatialPosition* ) const;
		



protected:


private:
	// We don't want these accessible
	// Copy Constructor 
	TEuclideanRefFrame( const TEuclideanRefFrame& );

	// Copy Assignment Operator 
	TEuclideanRefFrame& operator=( const TEuclideanRefFrame& );
	
private:
	
	//TSpatialPosition  fFalseOrigin;

	//ClassDef(TEuclideanRefFrame, 1)
};


////////////////////////////////////////////////////////////////////
// Inline Definitions
////////////////////////////////////////////////////////////////////






#endif // SU_EUCLIDEAN_REFERENCE_FRAME
