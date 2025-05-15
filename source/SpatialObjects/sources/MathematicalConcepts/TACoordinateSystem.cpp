// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

// TACoordinateSystem.cpp
//
/** Abstract class use for explain  a Coordinate System */
//
// Patterns:
//
// 
//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
#include "TACoordSysVector.h"
#include  "TACoordinateSystem.h"
////////////////////////////////////////////////////////////////


//ClassImp(TACoordinateSystem)

//////////////////////////////////////////////////////////////////
///Public Functions for Vector
//////////////////////////////////////////////////////////////////

	
TLength TACoordinateSystem::getH(const TPositionVector*) const
{//get the H coordinate of a position vector, default def: \return TLength Null
TLength null;
return null;
}

TAngle TACoordinateSystem::getLambdaEllipsoid(const TPositionVector*) const
{//get the Lambda coordinate of a position vector, default def: \return TAngle Null
TAngle null;
return null;
}

TAngle TACoordinateSystem::getPhiEllipsoid(const TPositionVector*) const
{//get the Phi coordinate of a position vector, default def: \return TAngle Null
TAngle null;
return null;
}

TLength TACoordinateSystem::getX(const TACoordSysVector*) const
{//get the X coordinate of a position vector or a free vector, default def: \return TLength Null
TLength null;
return null;
}

TLength TACoordinateSystem::getY(const TACoordSysVector*) const
{//get the Y coordinate of a position vector or a free vector, default def: \return TLength Null
TLength null;
return null;
}

TLength TACoordinateSystem::getZ(const TACoordSysVector*) const
{//get the Z coordinate of a position vector or a free vector, default def: \return TLength Null
TLength null;
return null;
}


bool TACoordinateSystem::setH(TPositionVector*, const TLength&)
{//set the H Coordinate of a position vector, default def: return false
return false;
}

bool TACoordinateSystem::setLambdaEllipsoid(TPositionVector*, const TAngle&)
{//set the Lambda Coordinate of a position vector, default def: return false
return false;
}

bool TACoordinateSystem::setPhiEllipsoid(TPositionVector*, const TAngle&)
{//set the Phi Coordinate of a position vector, default def: return false
return false;
}

bool TACoordinateSystem::setX(TACoordSysVector*, const TLength&)
{//set the X Coordinate of a position vector or a free vector, default def: return false
return false;
}

bool TACoordinateSystem::setY(TACoordSysVector*, const TLength&)
{//set the Y Coordinate of a position vector or a free vector, default def: return false
return false;
}

bool TACoordinateSystem::setZ(TACoordSysVector*, const TLength&)
{//set the Z Coordinate of a position vector or a free vector, default def: return false
return false;
}

//////////////////////////////////////////////////////////////////////////////////
///Public Functions for Matrix
//////////////////////////////////////////////////////////////////////////////////


bool TACoordinateSystem::setAllRotations( TRotationMatrix* /*mat*/, TRotationMatrix::ERotationType , TReal &, TReal &, TReal &)
{//create a TRotationMatrix default def: return false
	return false;
}


struct Angles TACoordinateSystem::getAngles(const TRotationMatrix*, const TRotationMatrix::ERotationType) const
{//get angles of a TRotationMatrix return a structure (omega, phi, kappa), default def return false
	TAngle om;
	TAngle p;
	TAngle k;
	
	om.setRadiansValue(NO_VALf);
	p.setRadiansValue(NO_VALf);
	k.setRadiansValue(NO_VALf);


	Angles null;
	null.omega=om;
	null.phi=p;
	null.kappa=k;
	return null;
}

	
bool TACoordinateSystem::identity(TRotationMatrix* /*mx*/)
{//change a rotation matrix into the identity matrix, default def: return false
return false;
}



bool TACoordinateSystem::setElt(T3DMatrix* /*mx*/, const int, const int, const TReal)
{//set a element into a 3D matrix
return false;
}


TReal TACoordinateSystem::getElt(const T3DMatrix* , const int , const int ) const
{//get a element from a 3D matrix
	assert(false);
	return -1.0;
}

TReal TACoordinateSystem::getElt(const TRotationMatrix*, const int , const int) const
{//get a element from a rotation matrix
return 0;
}

////////////////////////////////////////////////////////////////
///Public Member function
////////////////////////////////////////////////////////////////
void TACoordinateSystem::setCoordSysId(TCoordSysFactory::ECoordSys sys)
{
	fCoordSysId = sys;
	return;
}



TCoordSysFactory::ECoordSys TACoordinateSystem::getCoordSysId() const
{
	return fCoordSysId;
	
}



////////////////////////////////////////////////////////////////
// Member Protected Functions for Vector
////////////////////////////////////////////////////////////////


TReal	TACoordinateSystem::getX(const TACoordSysVector* v, const int& i) const
{//get the Xi coordinate of a vector in all Coordinate System
return v->getX(i);
}


void	TACoordinateSystem::setX(TACoordSysVector* v, const int& i, const TReal& value)
{//!set the Xi coordinate of a vector in all Coordinate System
v->setX(i, value);
return;
}

////////////////////////////////////////////////////////////////
// Member Protected Functions for Matrix
////////////////////////////////////////////////////////////////

TReal	TACoordinateSystem::getC(const TACoordSysMatrix* mx, const int& i, const int& j) const
{//get the (i,j) value of a matrix
return mx->getC(i, j);
}


void	TACoordinateSystem::setC(TACoordSysMatrix* mx, const int& i, const int& j, TReal value)
{//set value to (i,j) of a matrix
mx->setC(i, j, value);
return;
}


#if USE_SERIALIZER
void TACoordinateSystem::serialize(ObjectSerializer &obj) const
{
	TVCoordinateSystem::serialize(obj);
	obj.addProperty("fCoordSysId", fCoordSysId);
}
#endif // USE_SERIALIZER
