// TFreeVector.h
//
/** 3D Vector used as a free vector only affected by rotations and scaling
//
// Patterns:
//
// 
// Copyright 2000 CERN EST/SU. All rights reserved.
*/
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

#include "TACoordSysVector.h"
using namespace std;

//
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! 3D Vector used as a free vector
class  TFreeVector : public TACoordSysVector   
{
public:
	
	

	/*!\name Constructors and Destructors */
	//@{
		//!Default Constructor 
		TFreeVector(TCoordSysFactory::ECoordSys);
	
		//!Constructor taking 3 double (value in meter)
		TFreeVector(const double&, const double&, const double&, TCoordSysFactory::ECoordSys);

		//!Copy Constructor 
		TFreeVector( const TFreeVector&);

		//!Destructor
		virtual  ~TFreeVector();
	//@}

	

	/*!\name operator Functions */
	//@{
		//!Equivalence Operator 
		bool operator==( const TFreeVector& ) const;
		
		//!Add two FreeVector
		virtual TFreeVector operator+(const TFreeVector&);
	
		//!Add two FreeVector and replace *this
		TFreeVector& operator+=(const TFreeVector&);

		//!Substract two FreeVector
		TFreeVector operator-(const TFreeVector&);
		
		//!Substract two FreeVector and replace *this
		TFreeVector& operator-=(const TFreeVector&);

		//!Multiplication by a TDouble object
		TFreeVector operator*( const TDouble& );

		//!Multiplication by a double 
		TFreeVector operator*( const double& );

		//!Copy Assignment Operator 
		TFreeVector& operator=( const TFreeVector& );
	//@}

		/*!\name member function*/
	//@{
		//!give the length of a TFreeVector (meters)
		TLength length() const;

		//!give the horizontal distance of a TFreeVector (meters)
		TLength getHorDist() const;
		
	//@}


private:

		//!Default Constructor 
		TFreeVector();

	
	//ClassDef(TFreeVector, 1)
};

/*@}*/
//////////////////////////////////////////////////////////////////////
// Inline Definitions 
//////////////////////////////////////////////////////////////////////

#endif // SU_FREE_VECTOR
