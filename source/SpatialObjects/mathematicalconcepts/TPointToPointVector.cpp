// TPointToPointVector.cpp
//
/** 3D Vector used as a Spatial Position for stations or as translation vector in Helmert transformation */
//
// Patterns:
//
// 
// Copyright 2000 CERN EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
#include  "TPointToPointVector.h"
#include  "TVCoordinateSystem.h"
#include  "TDouble.h"
#include  "TScalar.h"
////////////////////////////////////////////////////////////////


//ClassImp(TFreeVector)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TPointToPointVector::TPointToPointVector(TCoordSysFactory::ECoordSys en, const TPositionVector* firstPos, 
										 const TPositionVector* secondPos) : TFreeVector(en)
{
	firstPosition = firstPos;
	secondPosition = secondPos;
}

TPointToPointVector::~TPointToPointVector()
{
}


TLength TPointToPointVector::getX() const
{//!get the X coordinate of a vector in a specific Coordinate System
	return TLength(secondPosition->getX().getMetresValue() - firstPosition->getX().getMetresValue());
}

TLength TPointToPointVector::getY() const
{//!get the Y coordinate of a vector in a specific Coordinate System
	return TLength(secondPosition->getY().getMetresValue() - firstPosition->getY().getMetresValue());
}

TLength TPointToPointVector::getZ() const
{//!get the Z coordinate of a vector in a specific Coordinate System
	return TLength(secondPosition->getZ().getMetresValue() - firstPosition->getZ().getMetresValue());
}
