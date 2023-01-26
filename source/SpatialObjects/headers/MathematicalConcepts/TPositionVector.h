// TPositionVector.h
/*
© Copyright CERN 2000-2019. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
/** 3D Vector used to define position in a space*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_POS_VECTOR
#define SU_POS_VECTOR


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
#include  <iostream>
#include "TACoordSysVector.h"
#include "TFreeVector.h"
#include "TDouble.h"
#include "TScalar.h"
#include "TLength.h"
////////////////////////////////////////////////////////////////


#ifdef USE_SERIALIZER
#	include <Serializer.hpp>
#endif // USE_SERIALIZER


/*! \ingroup MathematicalConcepts
	@{*/
#ifdef USE_SERIALIZER
	class TPositionVector : public TACoordSysVector
#else
	//! 3D Vector used as a position vector
	class TPositionVector : public TACoordSysVector //: public TObject
#endif // USE_SERIALIZER

{
public:

	/*!\name Constructors and Destructors */
	//@{
		//!Default Constructor 
		TPositionVector(TCoordSysFactory::ECoordSys);
	
		//!Constructor taking 3 TLength
		//TPositionVector(const TLength&, const TLength&, const TLength&);

		//!Constructor taking 3 TReal
		TPositionVector(const TReal&, const TReal&, const TReal&,TCoordSysFactory::ECoordSys);

		//!Copy Constructor 
		TPositionVector( const TPositionVector&);

		//!Destructor
		virtual  ~TPositionVector();
	//@}

		
	/*!\name operator Functions */
	//@{
		//!Equivalence Operator 
		bool operator==( const TPositionVector& ) const;
		
		//!add a PositionVector  and FreeVector, return a PositionVector
		TPositionVector operator+(const TFreeVector& );
		TPositionVector operator-(const TFreeVector& );
		
		//!add a PositionVector  and FreeVector, replace this
		TPositionVector& operator+=(const TFreeVector& );
		//!substract a FreeVector from aPositionVector and replace this
		TPositionVector& operator-=(const TFreeVector& );

		//!substract two TPositionVector objects and return a FreeVector
		TFreeVector operator-(const TPositionVector& );
		
		//!Multiply a TPositionVector object by a TDouble
		TPositionVector operator*(const TDouble&);

		//!Multiply a TPositionVector object by a TSCalar
		TPositionVector operator*(const TScalar&);

		//!Multiply a TPositionVector object by a TReal 
		TPositionVector operator*(const TReal&);

		//!Multiply this vector by a TScalar
		TPositionVector & operator *= ( const TScalar& );

		//!Multiply this vector by a TReal 
		TPositionVector & operator *= ( const TReal& );

		//!Copy Assignment Operator 
		TPositionVector& operator=(const TPositionVector& );

	//@}

	/*!\name member Functions */
	//@{
		//!Give the distance between this and a second position vector
		TLength dist(const TPositionVector& ) const;

		//!get the H value of a TPositionVector if is defined
		TLength getH() const;

		//!get the lambda value of a TPositionVector if is defined
		TAngle getLambdaEllipsoid() const;

		//!get the phi value of a TPositionVector if is defined
		TAngle getPhiEllipsoid() const;

		//!set the H coordinate of a vector in a specific Coordinate System return true if X is defined
		bool setH(const TLength&);

		//!set the Lambda coordinate of a vector in a geodetic Coordinate System return true if X is defined
		bool setLambdaEllipsoid(const TAngle&);

		//!set the Phi coordinate of a vector in a geodetic Coordinate System return true if X is defined
		bool setPhiEllipsoid(const TAngle&);
	//@}

#ifdef USE_SERIALIZER
		// Inherited via Serializable
		virtual void serialize(SerializerObject::SerializationHelper &obj) const override;
		/*!
			\brief See \ref TVAdjustableObject::getLastUidx

			\throws Throws a logic_error if no component of the point is variable, i.e. a fixed point.
		*/
#endif	
	
private:

		//!Default Constructor 
		TPositionVector();
						
	//ClassDef(TPositionVector, 1)
};
/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions 
//////////////////////////////////////////////////////////////////////



#endif // SU_POS_VECTOR
