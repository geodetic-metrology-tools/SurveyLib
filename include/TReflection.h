// TReflection.h
//
/** 3D Reflection, affine transformation, six cases are distinguished:
Reflection by a plane x=0, y=0, z=0 or Reflection by the plane x=y, x=z or y=z*/
//
// Patterns:
//
// 
// Copyright 2000 CERN EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////



#ifndef SU_SPATIAL_REFLECTION
#define SU_SPATIAL_REFLECTION


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
class  TLength;
class  TTranslation;
class  TRotation;
#include  "TAAffineTransformation.h"

#include  "T3DMatrix.h"
#include  "TCompositeAffTransform.h"

// ETypedefs
//
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! 3D Reflection, affine transformation
class  TReflection : public TAAffineTransformation  
{
public:
	//constants
	enum EType {kNull, kXEqual0, kYEqual0, kZEqual0, kXEqualY, kXEqualZ, kYEqualZ};

	/**@name Constructors and Destructors */
	//@{
		/// Default Constructor 
		TReflection();
	
		/// Constructor taking EType
		TReflection(const EType);

		/// Copy Constructor 
		TReflection( const TReflection&);

		/// Destructor
		virtual  ~TReflection();
	//@}


	/**@name Member Functions */
	//@{
		/// Copy Assignment Operator 
		TReflection& operator=( const TReflection& );

		// Return a pointer to a clone of this transformation
		TAAffineTransformation*  clone() const;


		//! Multiplication by an affine transformation
		TCompositeAffTransform operator*( const TAAffineTransformation& );

		/// Return element ri, cj of the Reflection matrix
		double operator()(int row, int col) const;

		/// Return element ri, cj of the Reflection matrix
		double& operator()(int row, int col);

		//! return the reflection matrix
		T3DMatrix getReflectionMatrix() const { return fReflectionMatrix; }

		/// set the EType of Reflection cf enum
		void setType( EType );

		/// get the EType of Reflection
		TReflection::EType getType() const;
		
		/// Transform a TPosition Vector
		virtual bool transform( TPositionVector& ) const;

		/// Transform a TFreeVector
		virtual bool transform( TFreeVector & ) const;

		/// Transform a TRotationMatrix
		virtual bool transform( TRotationMatrix& ) const;

		/// Inverse
		TReflection inverse();

		/// Invert = Inverse but replace the transformation
		void invert();
	//@}


private:
		// private functions

			void fillMatrix(const TReflection::EType);

	 	//Member Attributes
		
			TReflection::EType	fReflectionType; /*!< type of reflexion */

			T3DMatrix			fReflectionMatrix; /*!< reflexion matrix */

		



	//ClassDef(TReflection, 1)
};
/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////

inline void TReflection::setType(TReflection::EType type){fReflectionType = type; fillMatrix(type); return;}
inline TReflection::EType TReflection::getType()const{return fReflectionType;}

#endif // SU_SPATIAL_Reflection
