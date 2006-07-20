/////////////////////////////////////////////////////////////////////////////
//THelmertTransformation.h
//
/** Classe pour une transformation helmert X1 = Fact*R*X+T*/
//
// Copyright 2000, CERN EST/SU. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#ifndef SU_HELMERT_TRANSFORMATION
#define SU_HELMERT_TRANSFORMATION


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
//
#include  "TEnlargement.h"
#include  "TRotation.h"
#include  "TTranslation.h"
#include  "TCompositeAffTransform.h"
#include  "TAAffineTransformation.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! Classe pour une transformation helmert
class  THelmertTransformation : public TAAffineTransformation  
{
public:
	/**@name  Constructors and destructors */
	//@{
		
		THelmertTransformation();

		THelmertTransformation(const TEnlargement&, const TRotation&, const TTranslation&);

		THelmertTransformation(const TRotation&, const TTranslation&);

		THelmertTransformation(const THelmertTransformation& );
		
		virtual ~THelmertTransformation();
	//@}


	
		/// Copy Assignment Operator 
		THelmertTransformation& operator=( const THelmertTransformation& );

		//! Multiplication by an affine transformation
		TCompositeAffTransform operator*( const TAAffineTransformation& );

		//! Return a pointer to a clone of this transformation
		TAAffineTransformation*  clone() const;

		
		
		/// Return the inverse transformation: X = R~-1*(1/factor)(x-T)
		THelmertTransformation inverse();

		/// Invert the transformation
		void invert();

		
	/**@name Setting Member Functions */
	//@{
		//! Set all 3 transformation
		void setTransformations(const TEnlargement&, const TRotation&, const TTranslation&);
		
		//! Set scaling factor
		void setEnlargement( const TEnlargement&);

		//! Set rotation
		void setRotation(const TRotation&);

		//! Set translation
		void setTranslation(const TTranslation&);
	//@}


	/**@name Getting Member Functions */
	//@{
		//! Get all the Helmert transformation
		THelmertTransformation* getTransformations() const;

		//! Get scaling factor
		TEnlargement getEnlargement()const;

		//! Get rotation
		TRotation getRotation()const;
		
		//! Get translation
		TTranslation getTranslation()const;


	//@}
		
		
	/**@name  Transform Methods */
	//@{	
		/// Return a transformed position vector
		virtual bool  transform( TPositionVector& ) const;

		/// Return a transformed free vector
		virtual bool  transform( TFreeVector& ) const ;

		/// Return a transformed Rotation Matrix
		virtual bool  transform( TRotationMatrix& ) const;
	//@}


private:
		// member attributes

		TEnlargement fEnlargement; /*!< scaling */
		TRotation fRotation; /*!< rotation */
		TTranslation fTranslation; /*!< translation */
		
		
	
	//ClassDef(THelmertTransformation, 1)
};
/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////

inline  void THelmertTransformation::setEnlargement( const TEnlargement& scaling){fEnlargement = scaling; return;}
inline	void THelmertTransformation::setRotation(const TRotation& rotate){fRotation = rotate; return;}
inline	void THelmertTransformation::setTranslation(const TTranslation& trans){fTranslation = trans;return;}

inline  TEnlargement THelmertTransformation::getEnlargement()const{return fEnlargement;}
inline	TRotation    THelmertTransformation::getRotation()const{return fRotation;}
inline	TTranslation THelmertTransformation::getTranslation()const{return fTranslation;}
		

#endif // SU_HELMERT_TRANSFORMATION
