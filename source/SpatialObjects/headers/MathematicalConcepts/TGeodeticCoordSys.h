/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

//TGeodeticCoordSys.h 

/*! Class for explain vector in a geodetic coordinate system */
/////////////////////////////////////////////////////////

#ifndef SU_GEO_COORDSYS
#define SU_GEO_COORDSYS


////////////////////////////////////////////////////////////////
// Forward declarations
////////////////////////////////////////////////////////////////

//!Includes Files
#include "TACoordinateSystem.h"
#include "TLength.h"
#include <TAngle.h>
//!Type Definition
//typedef		
//
////////////////////////////////////////////////////////////////

/*! \ingroup MathematicalConcepts
	@{*/

//! Class for explain vector in a geodetic coordinate system
class	TGeodeticCoordSys : public  TACoordinateSystem
{

public:

	/*!@name static member functions */
	//@{
	/*! Return the number of additional decimal needed for 1m precidion.
	 *!
	 *! Depending on the unit used for the angle, you need more or less precision to have in the end
	 *! a precision of 1 meter at the surface of the Earth.
	 *!
	 *! @param unit the angle unit
	 */
	static int precisionNeeded(TAngle::EUnits unit);
	//@}

	/*!\name Member Functions for vector*/
	//@{
	
		//!get the Phi coordinate of a position vector 
		virtual TAngle getPhiEllipsoid(const TPositionVector*) const;
		
		//!get the Lambda coordinate of a position vector
		virtual TAngle getLambdaEllipsoid(const TPositionVector*) const;
		
		//!get the H coordinate of a position vector
		virtual TLength getH(const TPositionVector*) const;
		
		//!set the Phi Coordinate of a position vector
		virtual bool setPhiEllipsoid(TPositionVector*, const TAngle&);

		//!set the Lambda Coordinate of a position vector
		virtual bool setLambdaEllipsoid(TPositionVector*, const TAngle&);
		
		//!set the H Coordinate of a position vector
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

	//ClassDef(TGeodeticCoordSys, 1)
};
/*@}*/

#endif // SU_GEO_COORDSYS
