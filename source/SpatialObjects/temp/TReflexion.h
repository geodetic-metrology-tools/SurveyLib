// TReflection.h
//
/** 3D reflexion, affine transformation, six cases are distinguished:
reflexion by a plane x=0, y=0, z=0 or reflexion by the plane x=y, x=z or y=z*/
//
// Patterns:
//
// 
// Copyright 2000 CERN EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////



#ifndef SU_SPATIAL_REFLEXION
#define SU_SPATIAL_REFLEXION


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
class  TLength;
class  TPositionVector;
class  TFreeVector;
class  TTranslation;
class  TRotation;
//#include  "**classname**.h"
// ETypedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TReflection : public TVAffineTransformation  
{
public:
	//constants
	enum EType {kNull, kXEq0, kYEq0, kZEq0, kXEqY, kXEqZ, kYEqZ};

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
		TReflection& operator=( TReflection& );

		// Return a pointer to a clone of this transformation
		TVAffineTransformation*  clone() const;

		/// Multiply operators overloaded for Translations and Rotations 
		TTranslation operator*( const TTranslation& );
		TRotation operator*(const TRotation& );

		/// Return element ri, cj of the reflexion matrix
		double operator()(int row, int col) const;
		double& operator()(int row, int col);


		/// set the EType of reflexion cf enum
		void setType( EType );

		/// get the EType of reflexion
		TReflection::EType getType() const;
		
		/// Transform a TPosition Vector
		TPositionVector transform( const TPositionVector& ) const;

		/// Transform a TFreeVector
		TFreeVector transform( const TFreeVector & ) const;

		/// Transform a TRotationMatrix
		TRotationMatrix transform( const TRotationMatrix& ) const;

		/// Inverse
		TReflection inverse();

		/// Invert = Inverse but replace the transformation
		void invert();


	//@}


private:
	 	//Member Attributes
		
			TReflection::EType fReflexionType;

			double fReflexionMatrix[3][3];

		// private functions

			void fillMatrix(const TReflection::EType);



	//ClassDef(TReflection, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////

inline void TReflection::setType(TReflection::EType type){fReflexionType = type; return;}
inline TReflection::EType TReflection::getType()const{return fReflexionType;}

#endif // SU_SPATIAL_REFLEXION
