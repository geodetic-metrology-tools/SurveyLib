//  TVAffineTransformation.h
//
/** Classe de base purement abstraite pour une transformation affine
 
  
    Patterns:
  
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_V_AFFINE_TRANSFORMATION
#define SU_V_AFFINE_TRANSFORMATION


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
//
class  TPositionVector;
class  TFreeVector;
class  TRotationMatrix;
class  TSpatialPosition;
class  TSpatialVector;
class  TSpatialOrientation;

#include  "TVTransformation.h"
#include  "TVNumericValue.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! Classe de base purement abstraite pour une transformation affine
class  TVAffineTransformation : public TVTransformation, public TVNumericValue //: public TObject  
{
public:
	/**@name Member Functions */
	//@{
		/// transform a spatial position
		virtual  bool  transform( TSpatialPosition& ) const = 0;

		/// transform a spatial vector
		virtual  bool  transform( TSpatialVector& ) const = 0;

		/// transform a spatial orientation
		virtual  bool  transform( TSpatialOrientation& ) const = 0;

		//! transform a position vector
		virtual  bool  transform( TPositionVector& ) const = 0;

		//! transform a free vector
		virtual  bool  transform( TFreeVector& ) const = 0;

		//! transform a Rotation Matrix
		virtual  bool  transform( TRotationMatrix& ) const = 0;

		/// Inverse the transfo
		virtual void invert() = 0;

	//@}


protected:


private:

	//ClassDef(TVAffineTransformation, 1)
};
/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_V_AFFINE_TRANSFORMATION
