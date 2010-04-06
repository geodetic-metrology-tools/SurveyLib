// TVCoordinateSystem.h
//
/** Virtual class for Coordonate System 
//
// Patterns:
//
// 
// Copyright 2002 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_V_COORDINATE_SYSTEM
#define SU_V_COORDINATE_SYSTEM


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations

class TACoordSysVector;
class TACoordSysMatrix;
class TLength;
class TAngle;
class TPositionVector;
#include "TRotationMatrix.h"
#include "T3DMatrix.h"
#include "TCoordSysFactory.h"
//
//
//using namespace std;
//
//
//typedefs
//
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! Virtual class for Coordonate System
class  TVCoordinateSystem  //: public TObject

{
public:
	
	/*!\name Functions for Vector*/
	//@{
	virtual TLength getH(const TPositionVector*) const=0;

	virtual TAngle getLambdaEllipsoid(const TPositionVector*) const=0;

	virtual TAngle getPhiEllipsoid(const TPositionVector*) const=0;

	virtual TLength getX(const TACoordSysVector*) const=0;

	virtual TLength getY(const TACoordSysVector*) const=0;

	virtual TLength getZ(const TACoordSysVector*) const=0;

	virtual bool setH(TPositionVector*, const TLength&)=0;

	virtual bool setLambdaEllipsoid(TPositionVector*, const TAngle&)=0;

	virtual bool setPhiEllipsoid(TPositionVector*, const TAngle&)=0;

	virtual bool setX(TACoordSysVector*, const TLength&)=0;

	virtual bool setY(TACoordSysVector*, const TLength&)=0;

	virtual bool setZ(TACoordSysVector*, const TLength&)=0;
	//@}

	/*!\name Functions for Matrix*/
	//@{
	virtual bool setAllRotations(TRotationMatrix*, TRotationMatrix::ERotationType kR, real &om, real &p, real &k)=0;

	virtual	struct Angles getAngles(const TRotationMatrix*, const TRotationMatrix::ERotationType kR) const =0;
	
	virtual bool identity(TRotationMatrix*)=0;
	
	virtual	bool setElt(T3DMatrix*, const int, const int, const real)=0;

	virtual	real getElt(const T3DMatrix*, const int, const int) const=0;

	virtual	real getElt(const TRotationMatrix*, const int, const int) const=0;
	//@}


	/*!\name Member Functions*/
	//@{
	//! get the coordinate system identifier
	virtual TCoordSysFactory::ECoordSys getCoordSysId() const = 0;
	//@}


};

/*@}*/
#endif // SU_V_COORDINATE_SYSTEM
