//T2DCartesianCoordSys.h 
//
//Class for explain vector in a 2D cartesian
//Coordinate system 
//
//Copyright 2002, CERN, EST/SU. All rights reserved.
/////////////////////////////////////////////////////////

//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
#include "T2DCartesianCoordSys.h"
//
// other forward declarations

////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
///Public Functions for Vector
//////////////////////////////////////////////////////////////////


TLength T2DCartesianCoordSys::getX(const TACoordSysVector* vec) const
{//get the X coordinate of a position vector or a free vector
	TLength retVal;
	retVal.setMetresValue(this->TACoordinateSystem::getX(vec, 2));
	return retVal;
}

TLength T2DCartesianCoordSys::getY(const TACoordSysVector* vec) const
{//get the Y coordinate of a position vector or a free vector
	TLength retVal;
	retVal.setMetresValue(this->TACoordinateSystem::getX(vec, 2));
	return retVal;
}


bool T2DCartesianCoordSys::setX(TACoordSysVector* vec, const TLength& len)
{//set the X in meters Coordinate of a position vector or a free vector 
this->TACoordinateSystem::setX(vec,0,len.getMetresValue());
return true; 
}

bool  T2DCartesianCoordSys::setY(TACoordSysVector* vec, const TLength& len)
{//set the Y Coordinate of a position vector or a free vector, default def: return false
this->TACoordinateSystem::setX(vec,1,len.getMetresValue());
return true;
}



//ClassImp(T2DCartesianCoordSys)



	


