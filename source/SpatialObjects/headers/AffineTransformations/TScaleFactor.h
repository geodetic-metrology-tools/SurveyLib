/*
 * SPDX-FileCopyrightText: 2025 CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

﻿// TScaleFactor.h

/** A Scaling Transformation */
//////////////////////////////////////////////////////////////////////



#ifndef SU_SCALE_FACTOR_TRANSFO
#define SU_SCALE_FACTOR_TRANSFO


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
class  TCompositeAffTransform;
#include "Quad.h"
#include  "TAAffineTransformation.h"
//
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! Class for scaling
class  TScaleFactor : public TAAffineTransformation  
{
public:
		
	/**@name Constructors and Destructors */
	//@{
		//! Default Constructor, factor initialized to 1 
		TScaleFactor();

		//! Constructor taking a scale factor as a TReal
		explicit TScaleFactor(TReal);

		//! Copy Constructor 
		TScaleFactor( const TScaleFactor & );

		//! Destructor
		virtual  ~TScaleFactor();
	//@}


	/**@name Member Functions */
	//@{
		using TAAffineTransformation::operator();
		using TAAffineTransformation::transform;

		//! Copy Assignment Operator 
		TScaleFactor & operator = ( const TScaleFactor & );

		//! Multiplication by another scaling transformation
		TScaleFactor operator * ( const TScaleFactor & );
		
		//! Set the factor of ScaleFactor
		void setScaleFactor( TReal );

		//! Return the factor
		TReal getScaleFactor() const;
		
		//! Create a composite transformation by applying this transformation to an affine transformation
		//virtual  TCompositeAffTransform operator() ( const TAAffineTransformation & ) const;

		//! Return a pointer to a clone of this transformation
		virtual  TScaleFactor*  clone() const;

		//! Transform a position vector
		virtual  bool transform( TPositionVector & )const;

		//! Transform a  free vector
		virtual  bool transform( TFreeVector & )const;

		//! Transform a rotation matrix
		virtual  bool transform( TRotationMatrix & ) const;

		//! apply this transformation to a position vector
		virtual  TPositionVector &  operator() ( TPositionVector & ) const;

		//! apply this transformation to a free vector
		virtual  TFreeVector &  operator() ( TFreeVector & ) const;

		//! apply this transformation to a Rotation Matrix
		virtual  TRotationMatrix &  operator() ( TRotationMatrix & ) const;

		//! Return a pointer to the inverse of this transformation
		virtual  TScaleFactor* inverse() const;

		//! Invert the transformation, replaces the current transformation parameters
		virtual  void invert();

		//! Return true if the transformation parameter are not set to NO_VALf
		virtual bool isInitialise() const;
	//@}


private:
	
		TReal  fScaleFactor; /*!< scale factor */

	//ClassDef(TScaleFactor, 1)
};
/*@}*/



#endif // SU_SCALE_FACTOR_TRANSFO
