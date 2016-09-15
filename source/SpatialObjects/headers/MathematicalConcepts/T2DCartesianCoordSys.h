//T2DCartesianCoordSys.h 
/*!
//Class for explain vector in a 2D cartesian
//Coordinate system 
//
//Copyright 2002, CERN, EST/SU. All rights reserved.
*/
/////////////////////////////////////////////////////////

#ifndef SU_T2D_CART_COORDSYS
#define SU_T2D_CART_COORDSYS

#if _MSC_VER >= 1000
#pragma once
#endif //! _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
////////////////////////////////////////////////////////////////

//!Includes Files
#include "TACoordinateSystem.h"
#include "TLength.h"

//!Type Definition
//typedef		
//
////////////////////////////////////////////////////////////////

/*! \ingroup MathematicalConcepts
	@{*/

//! Class for explain vector in a 2D cartesian coordinate system
class	T2DCartesianCoordSys : public  TACoordinateSystem //: public TObject
{

public:
	/*!\name Functions for Vector*/
	//@{
	//!get the X coordinate of a position vector or a free vector	
	virtual TLength getX(const TACoordSysVector*) const;

	//!get the Y coordinate of a position vector or a free vector
	virtual TLength getY(const TACoordSysVector*) const;

	//!set the X Coordinate in meters of a position vector or a free vector
	virtual bool setX(TACoordSysVector*, const TLength&);

	//!set the Y Coordinate in meters of a position vector or a free vector
	virtual bool setY(TACoordSysVector*, const TLength&);
	//@}


private:



	//ClassDef(T2DCartesianCoordSys, 1)
};

/*@}*/



#endif // SU_T2D_CART_COORDSYS
