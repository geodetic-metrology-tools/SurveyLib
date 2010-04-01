// TTranslation.h
//
/** Class for a translation
    Operators : + Translation */
//
// Patterns:
//
// 
// Copyright 2000 CERN EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////



#ifndef SU_TRANSLATION_TRANSFO
#define SU_TRANSLATION_TRANSFO


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include  "TAAffineTransformation.h"
#include  "TCompositeAffTransform.h"
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! Class for a translation
class  TTranslation : public TAAffineTransformation  
{
public:
	//constants

	/**@name Constructors and Destructors */
	//@{
		/// Default Constructor , create a translation of vector (0,0,0)
		TTranslation();

		/// Translation taking 3 length as Tx, Ty, Tz
		TTranslation(const TLength Tx, const TLength Ty, const TLength Tz);

		/// Translation taking a free vector
		TTranslation(TFreeVector);

		/// Copy Constructor 
		TTranslation(const  TTranslation&);

		/// Destructor
		virtual  ~TTranslation();
	//@}


	/**@name Member Functions */
	//@{
		/// Copy Assignment Operator 
		TTranslation& operator=( const TTranslation& );

		/// operator + : T2 = T + T1
		TTranslation  operator+(const TTranslation&);

		//! Multiplication by an affine transformation
		TCompositeAffTransform operator*(const TAAffineTransformation&);

		/// Return element i
		quad       operator[](int ) const;

		/// Return element i
		quad&      operator[](int );

		/// Return the translation vector
		TFreeVector   getVector() const;

		/// Return a pointer to a clone of this transformation
		TAAffineTransformation*  clone() const;

		/// Transform a position vector 
		virtual bool transform( TPositionVector& )const;

		/// Transform a free vector
		virtual bool transform( TFreeVector& )const;

		/// Transform a rotation matrix
		virtual bool transform( TRotationMatrix& )const;

		/// inverse transformation
		TTranslation inverse();

		/// invert the transformation
		void invert();

	
	//@}


private:

	
		TFreeVector fTranslationVector;



	//ClassDef(TTranslation, 1)
};
/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////

inline TFreeVector TTranslation::getVector() const {return fTranslationVector;}



#endif // SU_TRANSLATION_TRANSFO
