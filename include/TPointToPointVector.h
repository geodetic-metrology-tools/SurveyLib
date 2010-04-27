// TPointToPointVector.h
//
/** 3D Vector used as a free vector only affected by rotations and scaling
//
// Patterns:
//
// 
// Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_POINT_TO_POINT_VECTOR
#define SU_POINT_TO_POINT_VECTOR


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#if __INTEL_COMPILER
#include	<mathimf.h>
#else
#include <math.h>
#endif

class TDouble;
class TScalar;

#include "TFreeVector.h"
#include "TPositionVector.h"
using namespace std;

//
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! 3D Vector used as a free vector
class  TPointToPointVector : public TFreeVector   
{
public:
	
	

	/*!\name Constructors and Destructors */
	//@{
		//!Default Constructor 
		TPointToPointVector(TCoordSysFactory::ECoordSys en, const TPositionVector* firstPos, 
										 const TPositionVector* secondPos);

		//!Destructor
		virtual  ~TPointToPointVector();
	//@}

		//!get the X coordinate of a vector in a specific Coordinate System
		virtual TLength getX() const;

		//!get the Y coordinate of a vector in a specific Coordinate System
		virtual TLength getY() const;

		//!get the Z coordinate of a vector in a specific Coordinate System
		virtual TLength getZ() const;
	
private:

	const TPositionVector* firstPosition;
	const TPositionVector* secondPosition;
	
	//ClassDef(TFreeVector, 1)
};

/*@}*/
//////////////////////////////////////////////////////////////////////
// Inline Definitions 
//////////////////////////////////////////////////////////////////////

#endif // SU_POINT_TO_POINT_VECTOR
