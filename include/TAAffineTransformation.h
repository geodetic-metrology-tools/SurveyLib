//  TAAffineTransformation.h
//
/** Classe de base purement abstraite pour une transformation affine
 
  
    Patterns:
  
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_A_AFFINE_TRANSFORMATION
#define SU_A_AFFINE_TRANSFORMATION


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
//
#include  "TVAffineTransformation.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////

/*!\ingroup spatialobjects
	@{*/

//! Classe de base purement abstraite pour une transformation affine
class  TAAffineTransformation : public TVAffineTransformation
{
public:

	/// status enumeration
	//enum EStatus {kNull, kUnknown, kVariable, kFixed};

	/**@name Constructors/destructors */
	//@{
		TAAffineTransformation();
	
		virtual ~TAAffineTransformation();
	
	//@}

	/**@name Member Functions */
	//@{

		/*! transform a spatial position */
		virtual  bool  transform( TSpatialPosition& ) const;

		/*! transform a spatial vector */
		virtual  bool  transform( TSpatialVector& ) const;

		/*! transform a spatial orientation */
		virtual  bool  transform( TSpatialOrientation& ) const;

		/*! transform a position vector */
		virtual  bool  transform( TPositionVector& ) const;

		/*! transform a free vector */
		virtual  bool  transform( TFreeVector& ) const;

		/*! transform a Rotation Matrix */
		virtual  bool  transform( TRotationMatrix& ) const;

		/// Return a pointer to a clone of this reference frame
		virtual  TAAffineTransformation*  clone() const {return 0;}
		
		/*! Returns the enum status */
		virtual	EStatus	getStatus()const { return fStatus; }

		/*! Sets the enum status */
		virtual void setStatus(EStatus);

		/*! Checks the status */
		virtual bool isNull() const;
	//@}


protected:

	TVNumericValue::EStatus fStatus; /*!< Status */

private:

	//ClassDef(TAAffineTransformation, 1)
};

/*@}*/


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_A_AFFINE_TRANSFORMATION
