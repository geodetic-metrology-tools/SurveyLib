/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

// TVCoordinateSystem.h

/** Virtual class for Coordonate System */
//////////////////////////////////////////////////////////////////////

#ifndef SU_V_COORDINATE_SYSTEM
#define SU_V_COORDINATE_SYSTEM

#include "T3DMatrix.h"
#include "TCoordSysFactory.h"
#include "TRotationMatrix.h"

////////////////////////////////////////////////////////////////
// Forward declarations

class TACoordSysVector;
class TACoordSysMatrix;
class TLength;
class TAngle;
class TPositionVector;
//
//
//
//
// typedefs
//
//
////////////////////////////////////////////////////////////////

/*! \ingroup MathematicalConcepts
	@{*/
#if USE_SERIALIZER
//! Virtual class for Coordonate System
class TVCoordinateSystem : public Serializable 
#else
//! Virtual class for Coordonate System
class TVCoordinateSystem
#endif // USE_SERIALIZER

{
public:
	virtual ~TVCoordinateSystem() = default;

	/*!\name Functions for Vector*/
	//@{
	virtual TLength getH(const TPositionVector *) const = 0;

	virtual TAngle getLambdaEllipsoid(const TPositionVector *) const = 0;

	virtual TAngle getPhiEllipsoid(const TPositionVector *) const = 0;

	virtual TLength getX(const TACoordSysVector *) const = 0;

	virtual TLength getY(const TACoordSysVector *) const = 0;

	virtual TLength getZ(const TACoordSysVector *) const = 0;

	virtual bool setH(TPositionVector *, const TLength &) = 0;

	virtual bool setLambdaEllipsoid(TPositionVector *, const TAngle &) = 0;

	virtual bool setPhiEllipsoid(TPositionVector *, const TAngle &) = 0;

	virtual bool setX(TACoordSysVector *, const TLength &) = 0;

	virtual bool setY(TACoordSysVector *, const TLength &) = 0;

	virtual bool setZ(TACoordSysVector *, const TLength &) = 0;
	//@}

	/*!\name Functions for Matrix*/
	//@{
	virtual bool setAllRotations(TRotationMatrix *, TRotationMatrix::ERotationType kR, TReal &om, TReal &p, TReal &k) = 0;

	virtual struct Angles getAngles(const TRotationMatrix *, const TRotationMatrix::ERotationType kR) const = 0;

	virtual bool identity(TRotationMatrix *) = 0;

	virtual bool setElt(T3DMatrix *, const int, const int, const TReal) = 0;

	virtual TReal getElt(const T3DMatrix *, const int, const int) const = 0;

	virtual TReal getElt(const TRotationMatrix *, const int, const int) const = 0;
	//@}

	/*!\name Member Functions*/
	//@{
	//! get the coordinate system identifier
	virtual TCoordSysFactory::ECoordSys getCoordSysId() const = 0;
	//@}

#if USE_SERIALIZER
	// Inherited via Serializable
	virtual void serialize(ObjectSerializer &obj) const = 0;
#endif

};


#if USE_SERIALIZER
inline void TVCoordinateSystem::serialize(ObjectSerializer &) const
{

}
#endif // USE_SERIALIZER


/*@}*/
#endif // SU_V_COORDINATE_SYSTEM
