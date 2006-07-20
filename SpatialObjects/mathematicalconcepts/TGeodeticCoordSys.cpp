//TGeodeticCoordSys.h 
//
//Class for explain vector in a geodetic Coordinate system 
//
//Copyright 2002, CERN, EST/SU. All rights reserved.
/////////////////////////////////////////////////////////

//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
#include "TGeodeticCoordSys.h"
//
// other forward declarations

////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
///Member Functions for vector
////////////////////////////////////////////////////////////////
	
	TAngle TGeodeticCoordSys::getPhiEllipsoid(const TPositionVector* vec) const
	{//get the Phi coordinate of a position vector
	return this->TACoordinateSystem::getX(vec, 0);
	}


	TAngle TGeodeticCoordSys::getLambdaEllipsoid(const TPositionVector* vec) const
	{//get the Lambda coordinate of a position vector 
	return this->TACoordinateSystem::getX(vec, 1);
	}

	TLength TGeodeticCoordSys::getH(const TPositionVector* vec) const
	{//get the H coordinate of a position vector
	return this->TACoordinateSystem::getX(vec, 2);
	}


	bool TGeodeticCoordSys::setPhiEllipsoid(TPositionVector* vec, const TAngle& ang)
	{//set the phi  Coordinate in radian of a position vector 
	this->TACoordinateSystem::setX(vec,0,ang.getRadiansValue());
	return true; 
	}


	bool TGeodeticCoordSys::setLambdaEllipsoid(TPositionVector* vec, const TAngle& ang)
	{//set the lambda  Coordinate in radian of a position vector 
	this->TACoordinateSystem::setX(vec,1,ang.getRadiansValue());
	return true; 
	}


	bool TGeodeticCoordSys::setH(TPositionVector* vec, const TLength& len)
	{//set the H  Coordinate in meters of a position vector 
	this->TACoordinateSystem::setX(vec,2,len.getMetresValue());
	return true; 
	}


////////////////////////////////////////////////////////////////
///Member Functions for matrix
////////////////////////////////////////////////////////////////



bool TGeodeticCoordSys::setElt(T3DMatrix* mx, const int i, const int j, const double value)
{//set a element into a 3D matrix
setC(mx, i, j, value);
return true;
}


double TGeodeticCoordSys::getElt(const T3DMatrix* mx, const int i, const int j) const
{//get a element from a 3D matrix
return getC(mx, i, j);
}





//ClassImp(TGeodeticCoordSys)