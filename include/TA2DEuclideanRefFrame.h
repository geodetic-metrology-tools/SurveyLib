// TA2DXYRefFrame.h
//
/*  
   Patterns:
   An Abstract STATE of a Spatial Position
   
   Copyright 2000 CERN EST/SU. All rights reserved.
*/
////////////////////////////////////////////////////////////////////



#ifndef SU_A_2D_XY_RF
#define SU_A_2D_XY_RF


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


//////////////////////////////////////////////////////////////
// Forward declarations
//
#include  <string>
#include  <set>
#include  "TSpatialPosition.h"
#include  "TSpatialVector.h"

#include  "TAReferenceFrame.h"
//using namespace std;
//
//class  TVTransformation;
// typedefs
//
//
//////////////////////////////////////////////////////////////!/



//! An abstract base class for a reference frame.
class  TA2DEuclideanRefFrame : public  TAReferenceFrame //: public TObject  
{
public:
	 
	/*!@name Constructors and Destructors */
	//@{
		//! Constructor taking the name of the reference frame
		TA2DEuclideanRefFrame( const string& name );

		//! Destructor
		virtual  ~TA2DEuclideanRefFrame();
	//@}

	/*!@name default definition of TVReferenceFrame's Data extraction methods*/
	//@{
	//! return the position vector of a spatial position 
//	virtual TPositionVector* getCoordinates(const TSpatialPosition* sp, TCoordSysFactory::ECoordSys) const;
	//! return the spatial position error of a spatial position 
//	virtual TSpatialPositionError getCoordCovariances(const TSpatialPosition* sp, TCoordSysFactory::ECoordSys) const;
	//! return the free vector of a spatial vector
//  virtual TFreeVector getElements(const TSpatialVector* sv, TCoordSysFactory::ECoordSys) const;
	//! return the spatial vector error of a spatial vector
//	virtual TSpatialVectorError getElementCovars(const TSpatialVector* sv, TCoordSysFactory::ECoordSys) const;
	//! return the rotation matrix of a spatial orientation
//	virtual TRotationMatrix getElements(const TSpatialOrientation* so, TCoordSysFactory::ECoordSys ) const;
	//! return the spatial orientation error of a spatial orientation
//	virtual TSpatialOrientationError getElementCovars(const TSpatialOrientation* so, TCoordSysFactory::ECoordSys ) const;

		//@}

	/*!@name default definition of TVReferenceFrame's Settings methods*/
	//@{
	//! set the position vector of a spatial position 
//	virtual bool setCoordinates(TSpatialPosition* sp, const TPositionVector& pv);
	//! set the spatial position error of a spatial position 
//	virtual bool setCoordCovariances(TSpatialPosition* sp, const TSpatialPositionError& spe);
	//! set the free vector of a spatial vector
//	virtual bool setElements(TSpatialVector* sv, const TFreeVector& fv);
	//! set the spatial vector error of a spatial vector
//	virtual bool getElementCovars(const TSpatialVector* sv, TSpatialVectorError& sve) const;
	//! set the rotation matrix of a spatial orientation
//	virtual bool setElements(const TSpatialOrientation* so, const TRotationMatrix& rm) const;
	//! set the spatial orientation error of a spatial orientation
//	virtual bool setElementCovars(const TSpatialOrientation* so, const TSpatialOrientationError& soe) const;
		//@}

	/*!@name Access methods*/
	//@{

		//! Get the name of the reference frame
		//virtual string  getName() const;

		/*! Add a transformation for transforming objects from this 
		    reference frame to another 
		 */
		//void  insert( TVTransformation*  transformer );

		//! Return an Iterator to the beginning of the set of Transformations
		//TVReferenceFrame::iterator  begin() const;

		//! Return an Iterator to the end of the set of Transformations
		//TVReferenceFrame::iterator  end() const;


		//! returns the X coordinate if defined for the reference frame
/*		virtual TLength  getXCoord( const TSpatialPosition* ) const;
		//! returns the Y coordinate if defined for the reference frame
		virtual TLength  getYCoord( const TSpatialPosition* ) const;

		//! returns the X component
		virtual TLength  getXComp( const TSpatialVector* ) const;
		//! returns the Y component
		virtual TLength  getYComp( const TSpatialVector* ) const;
*/		/*!@name Set methods*/
		//@{
		//! sets the X Cartesian coordinate of the given Spatial Position if defined for the Reference Frame
/*		virtual bool  setXCoord( TSpatialPosition*, const TLength & );  
		//! sets the Y Cartesian coordinate of the given Spatial Position if defined for the Reference Frame
		virtual bool  setYCoord( TSpatialPosition*, const TLength & );  

		//! sets the X Component of the given Spatial Vector
		virtual bool  setXComp( TSpatialVector*, const TLength & );  
		//! sets the Y Component of the given Spatial Vector
		virtual bool  setYComp( TSpatialVector*, const TLength & ); 
*/
		
/*		//! transforms a spatial position with an affine transformation, if possible
		bool transform( TSpatialPosition* sp, TAAffineTransformation* trans);

		//! transforms a spatial vector with an affine transformation, if possible
		bool transform( TSpatialVector* sv, TAAffineTransformation* trans);

		//! transforms a spatial orientation with an affine transformation, if possible
		bool transform( TSpatialOrientation* so, TAAffineTransformation* trans);
*/
		//@}
		


protected:
	
	

private:

	// Constructors and Destructors
	// Copy Constructor 
	TA2DEuclideanRefFrame( const  TA2DEuclideanRefFrame& );


	// Private Member Functions
	// Copy Assignment Operator
	TA2DEuclideanRefFrame&  TA2DEuclideanRefFrame::operator=( const TA2DEuclideanRefFrame& );


private:

//	string  fName;
//	TransformationSet  fTransformations;

	//ClassDef(TAReferenceFrame, 1)
};


////////////////////////////////////////////////////////////////////
// Inline Definitions
////////////////////////////////////////////////////////////////////






#endif // SU_A_REFERENCE_FRAME
