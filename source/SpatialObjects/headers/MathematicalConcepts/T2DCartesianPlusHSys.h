/*
 * SPDX-FileCopyrightText: 2025 CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

﻿//T2DCartesianPlusHSys.h 

/*!
	Class for explain vector in a 2D+H cartesian
	Coordinate system 
*/
/////////////////////////////////////////////////////////

#ifndef SU_T2D_PLUSH_COORDSYS
#define SU_T2D_PLUSH_COORDSYS

#if _MSC_VER >= 1000
#pragma once
#endif //! _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
////////////////////////////////////////////////////////////////

//!Includes Files
#include "TACoordinateSystem.h"
#include "TLength.h"
#include "TPositionVector.h"

//!Type Definition
//typedef		
//
////////////////////////////////////////////////////////////////

/*! \ingroup MathematicalConcepts
	@{*/

//! Class for explain vector in a 2D+H cartesian coordinate system
class	T2DCartesianPlusHSys : public  TACoordinateSystem //: public TObject
{

public:
	/*!\name Functions for Vector*/
	//@{
		//!get the X coordinate of a position vector or a free vector	
		virtual TLength getX(const TACoordSysVector*) const;

		//!get the Y coordinate of a position vector or a free vector
		virtual TLength getY(const TACoordSysVector*) const;

		//!get the H coordinate of a position vector
		virtual TLength getH(const TPositionVector*) const;

		//!set the X Coordinate in meters of a position vector or a free vector
		virtual bool setX(TACoordSysVector*, const TLength&);

		//!set the Y Coordinate in meters of a position vector or a free vector
		virtual bool setY(TACoordSysVector*, const TLength&);
		
		//!set the H Coordinate of a position vector, default def:
		virtual bool setH(TPositionVector*, const TLength&);
	//@}


	/*!\name Functions for Matrix*/
	//@{
		using TACoordinateSystem::getElt;

		//!set a element into a 3D matrix
		virtual	bool setElt(T3DMatrix*, const int, const int, const TReal);

		//!get a element from a 3D matrix
		virtual	TReal getElt(const T3DMatrix*, const int, const int) const;
	//@}


private:



	//ClassDef(T2DCartesianPlusHSys, 1)
};

/*@}*/



#endif // SU_T2D_PLUSH_COORDSYS
