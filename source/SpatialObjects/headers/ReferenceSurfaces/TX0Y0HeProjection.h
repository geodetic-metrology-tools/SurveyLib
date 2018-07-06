//  TX0Y0HeProjection.h
/*
© Copyright CERN 2000-2017. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
/** A projection on XY plane at 0-level with ellipsoidal height 

  
    Patterns:
    A concrete STATE of a Spatial Position

*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_X0Y0He_PROJECTION
#define SU_X0Y0He_PROJECTION


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include  <string>
//
class  TSpatialPosition;
class  TSpatialVector;
class  TReferenceEllipsoid;
class  TXYHeProjection;
#include  "TA2DPlus1MapProjection.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//!A projection on XY plane at 0-level with ellipsoidal height
class  TX0Y0HeProjection : public TA2DPlus1MapProjection //: public TObject  
{
public:
	
	/**@name Constructors and Destructors */
	//@{
		/// Default constructor
		TX0Y0HeProjection();

		/*! Constructor taking the name, and the ellipsoid projection */
		TX0Y0HeProjection( const std::string& name, TXYHeProjection* xyhe );

		/*! Destructor */
		virtual  ~TX0Y0HeProjection();
	//@}


	/**@name Member Functions */
	//@{
		/*! return the ellipsoid projection reference frame */
		virtual TXYHeProjection* getXYHe() { return fXYHe; }

		/*! return the reference ellipsoid of the projection */
		virtual TReferenceEllipsoid* getEllipsoid() { return fXYHe->getEllipsoid(); }
	//@}


protected:


private:
	// We don't want these accessible
	/*! Copy Constructor */
	TX0Y0HeProjection( const TX0Y0HeProjection& );

	/*! Copy Assignment Operator  */
	TX0Y0HeProjection& operator=( const TX0Y0HeProjection& );
	
	
private:

	
	TXYHeProjection*			fXYHe; /*!< ellipsoid projection */

};

#endif // SU_X0Y0He_PROJECTION
/*@}*/
//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////
	
	//ClassDef(TXYHeProjection, 1)
	/// Return a pointer to a clone of this reference frame
		//virtual TVReferenceFrame*  clone() const;

		
		//! transforms a spatial position with an affine transformation, if possible
//		virtual bool transform( TSpatialPosition* sp, TVAffineTransformation* trans);

		//! transforms a spatial vector with an affine transformation, if possible
//		virtual bool transform( TSpatialVector* sv, TVAffineTransformation* trans);
	






