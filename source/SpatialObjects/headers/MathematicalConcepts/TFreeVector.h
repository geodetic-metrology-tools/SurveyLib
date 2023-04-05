// TFreeVector.h
/*
© Copyright CERN 2000-2019. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
/** 3D Vector used as a free vector only affected by rotations and scaling*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_FREE_VECTOR
#define SU_FREE_VECTOR


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include <math.h>

class TDouble;
class TScalar;
class TPositionVector;

#include "TACoordSysVector.h"
//
//
////////////////////////////////////////////////////////////////

/*! \ingroup MathematicalConcepts
	@{*/
class TFreeVector : public TACoordSysVector
{
public:
	

	/*!\name Constructors and Destructors */
	//@{
		//!Default Constructor 
		TFreeVector(TCoordSysFactory::ECoordSys);

		//!Default Constructor 
		TFreeVector();
	
		//!Constructor taking 3 TReal
		TFreeVector(const TReal&, const TReal&, const TReal&, TCoordSysFactory::ECoordSys);

		//! Constructor taking a Position Vector
		TFreeVector(const TPositionVector&);

		//!Copy Constructor 
		TFreeVector( const TFreeVector&);

		//!Destructor
		virtual ~TFreeVector();
	//@}

	

	/*!\name operator Functions */
	//@{
		//!Equivalence Operator 
		bool operator==( const TFreeVector& ) const;
		
		//!Add two FreeVector
		virtual TFreeVector operator+(const TFreeVector&);
	
		//!Add two FreeVectors and replace *this
		TFreeVector& operator+=(const TFreeVector&);

		//!Substract two FreeVectors
		TFreeVector operator-(const TFreeVector&);
		
		//!Substract two FreeVectors and replace *this
		TFreeVector& operator-=(const TFreeVector&);

		//!Multiplication by a TDouble object
		TFreeVector operator*( const TDouble& );

		//!Multiplication by a TScalar
		TFreeVector operator*( const TScalar& );

		//!Multiplication by a TReal 
		TFreeVector operator*( const TReal& );

		//!Multiply this vector by a TScalar
		TFreeVector & operator *= ( const TScalar& );

		//!Multiply this vector by a TReal 
		TFreeVector & operator *= ( const TReal& );

		//!Copy Assignment Operator 
		TFreeVector& operator=( const TFreeVector& );
	//@}

		/*!\name member function*/
	//@{
		//!give the length of a TFreeVector (meters)
		TLength length() const;

		//!give the horizontal distance of a TFreeVector (meters)
		TLength getHorDist() const;
		
		// normalize the vector to length 1.0
		TFreeVector& normalize();

		TFreeVector cross(const TFreeVector& b);

		TReal dot(const TFreeVector& b) const;
	//@}

private:

	
	//ClassDef(TFreeVector, 1)
};

/*@}*/
//////////////////////////////////////////////////////////////////////
// Inline Definitions 
//////////////////////////////////////////////////////////////////////

#endif // SU_FREE_VECTOR
