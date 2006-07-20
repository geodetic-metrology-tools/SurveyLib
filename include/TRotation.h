// TRotation.h
//
/** Class for rotations. Affine Transformation. Uses as default representation RzRyRx matrix
It authorizes the inverse rotation and the multiplication 
by an other affine transformation when possible.
 Sub classes for rotations around each axis*/
//
// Patterns:
//
// 
// Copyright 2000 CERN EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////



#ifndef SU_ROTATION_TRANSFO
#define SU_ROTATION_TRANSFO


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
class  TEnlargement;
class  TTranslation;
class  TReflection;
class  THelmertTransformation;
class  TCompositeAffTransform;

#include  "TAngle.h"
#include  "TAAffineTransformation.h"
#include  "TRotationMatrix.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! Class for rotations. Affine Transformation
class  TRotation : public TAAffineTransformation  
{
public:
	//constants

	/**@name Constructors and Destructors */
	//@{
		//! Default Constructor, initialize the matrix to identity
		TRotation();

		/** Constructor taking the rotation matrix*/  
		TRotation(TRotationMatrix matrix);
		
		/** Constructor taking the radians value of the angles in the specified order */  
		TRotation(TRotationMatrix::ERotationType kR, double omega, double phi, double kappa);

		//! Copy Constructor 
		TRotation(const  TRotation&);

		/// Destructor
		virtual  ~TRotation();
	//@}


	/**@name Member Functions */
	//@{
		//! Copy Assignment Operator 
		TRotation& operator=( const TRotation& );

		//! Return a pointer to a clone of this transformation
		TAAffineTransformation*  clone() const;

		//! Return element ri, cj of the rotation matrix
		double operator()(int row, int col) const;

		//! Return element ri, cj of the rotation matrix
//insure		double& operator()(int row, int col);


		//! Multiplication by an affine transformation
		TCompositeAffTransform operator*(const TAAffineTransformation&);

		//! set the 3 rotations taking angles values in the order specified by the enumerator
		void setAllRotations(TRotationMatrix::ERotationType kR, double& omega,double& phi,double& kappa);

		//! return the rotation matrix as TRotationMatrix
		TRotationMatrix getRotationMatrix() const;

		//! Transform a vector of position
		virtual bool transform( TPositionVector& ) const;

		//! Transform a free vector
		virtual bool transform( TFreeVector& ) const;

		//! Transform a rotation matrix
		virtual bool  transform( TRotationMatrix& ) const;

		//! Return the inverse rotation
		TRotation inverse();

		//! Invert the rotation
		void invert();

		//] calculate the angles from the matrix with the specified rotation order
		struct Angles getAngles(TRotationMatrix::ERotationType kR);

	//@}
		

private:

		//! fill the matrix of rotation with the specified type
		void fillRotationMatrix(TRotationMatrix::ERotationType kR, double om, double p, double k);

		//! Member Attributs
		TRotationMatrix		fRotationMatrix; /*!< rotation matrix */
	

	
		


	//ClassDef(TRotation, 1)
};
/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////

inline TRotationMatrix TRotation::getRotationMatrix() const {return fRotationMatrix;}


//////////////////////////////////////////////////////////////////////
// Sous-classes pour rotations autour d'un seul axe
//////////////////////////////////////////////////////////////////////


// rotations autour de l'axe X

class TXAxisRotation : public TRotation
{
public:
	
	//! Constructor
	TXAxisRotation(const double& omega):TRotation(TRotationMatrix::kRzyx, omega, 0.0, 0.0){};

	/// Destructor
	virtual ~TXAxisRotation(){};
};


// rotations autour de l'axe Y

class TYAxisRotation : public TRotation
{
public:
	
	//! Constructor
	TYAxisRotation(const double& phi):TRotation(TRotationMatrix::kRzyx, 0.0, phi, 0.0){};

	/// Destructor
	virtual ~TYAxisRotation(){};
};


// rotations autour de l'axe Z

class TZAxisRotation : public TRotation
{
public:
	
	//! Constructor
	TZAxisRotation(const double& kappa):TRotation(TRotationMatrix::kRzyx, 0.0, 0.0, kappa){};

	/// Destructor
	virtual ~TZAxisRotation(){};
};

#endif // SU_ROTATION_TRANSFO

