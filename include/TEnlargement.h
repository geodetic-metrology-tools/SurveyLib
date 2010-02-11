// TEnlargement.h
//
/** Class for scaling */
//
// Patterns:
//
// 
// Copyright 2000 CERN EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////



#ifndef SU_ENLARGEMENT_TRANSFO
#define SU_ENLARGEMENT_TRANSFO


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//

class  TTranslation;
class  TRotation;
class  TReflection;
class  THelmertTransformation;
class  TCompositeAffTransform;
#include  "TAAffineTransformation.h"
#include  "TDouble.h"
#include  "TScalar.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! Class for scaling
class  TEnlargement : public TAAffineTransformation  
{
public:
		
	/**@name Constructors and Destructors */
	//@{
		/// Default Constructor, factor initialized to 1 
		TEnlargement();

		/// Constructor taking a scale factor as a double
		explicit TEnlargement(double);

		/// Constructor taking a scale factor as a TDouble
		explicit TEnlargement(TDouble);

		/// Constructor taking a scale factor as a TDouble
		explicit TEnlargement(TScalar);

		/// Copy Constructor 
		TEnlargement(const  TEnlargement&);

		/// Destructor
		virtual  ~TEnlargement();
	//@}


	/**@name Member Functions */
	//@{
		/// Copy Assignment Operator 
		TEnlargement& operator=(const TEnlargement& );

		//! Multiplication by an affine transformation
		TCompositeAffTransform operator*(const TAAffineTransformation&);
		
		//! Multiplication by another enlargement transformation
		TEnlargement& operator*(const TEnlargement&);
		
		//! Follow another affine transformation
		TCompositeAffTransform operator+(TAAffineTransformation&);

		//! Follow a composite affine transformation
		TCompositeAffTransform& operator+(TCompositeAffTransform&);
		
		// Return a pointer to a clone of this transformation
		TAAffineTransformation*  clone() const;

		/// Set the factor of Enlargement
		void setFactor( TDouble );

		/// Set the factor of Enlargement
		void setFactor( TScalar );

		/// Return the factor
		TDouble getFactor() const;
		
		/// Return a transformed position vector
		virtual bool  transform( TPositionVector& )const;

		/// Return a transformed free vector
		virtual bool  transform( TFreeVector& )const ;

		/// Return a transformed rotation matrix
		virtual bool transform( TRotationMatrix&) const;

		/// Inverse
		TEnlargement inverse();

		/// Invert = Inverse but replace the transformation
		void invert();
	//@}


private:
	
		TDouble	fScaleFactor; /*!< scale factor */

	//ClassDef(TEnlargement, 1)
};
/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////

inline void TEnlargement::setFactor( TDouble fact) {fScaleFactor = fact; return;}

inline TDouble TEnlargement::getFactor() const { return fScaleFactor;}




#endif // SU_ENLARGEMENT_TRANSFO
