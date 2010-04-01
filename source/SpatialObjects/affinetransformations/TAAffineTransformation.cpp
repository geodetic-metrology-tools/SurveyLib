// TAAffineTransformation.cpp
//
/** Class abstract for affine transformation. Deals with the status */
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
#include  "TSpatialPosition.h"
#include  "TSpatialVector.h"
#include  "TSpatialOrientation.h"

#include  "TAAffineTransformation.h"
////////////////////////////////////////////////////////////////


//ClassImp(TAAffineTransformation)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



TAAffineTransformation::TAAffineTransformation()
{
}

	
TAAffineTransformation::~TAAffineTransformation()
{
}


//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////
bool  TAAffineTransformation::transform( TSpatialPosition& spos) const
{// transform a spatial position
	TPositionVector vect = spos.getCoordinates(TCoordSysFactory::k3DCartesian);
	bool transformed = transform(vect);
	if (transformed == true)
	{
		spos.setCoordinates(vect);
	}
	return transformed;

}

bool  TAAffineTransformation::transform( TSpatialVector& svec) const
{// transform a spatial vector
	TFreeVector vect = svec.getElements(TCoordSysFactory::k3DCartesian);
	bool transformed = transform(vect);
	if (transformed == true)
	{
		svec.setElements(vect);
	}
	return transformed;
}

bool  TAAffineTransformation::transform( TSpatialOrientation& sori) const
{// transform a spatial orientation
	TRotationMatrix matrix = sori.getElements(TCoordSysFactory::k3DCartesian);
	bool transformed = transform(matrix);
	if (transformed == true)
	{
		sori.setElements(matrix);
	}
	return transformed;
}


bool  TAAffineTransformation::transform( TPositionVector& pos) const
{// transform a position vector : default function
	return false;
}

bool  TAAffineTransformation::transform( TFreeVector& free) const
{// transform a free vector : default function
	return false;
}

bool  TAAffineTransformation::transform( TRotationMatrix& rotation) const
{// transform a rotation matrix : default function
	return false;
}



void TAAffineTransformation::setStatus(const TVNumericValue::EStatus status)
{
	fStatus = status;
	return;
}

bool TAAffineTransformation::isNull()const
{
	if (fStatus == kNull)
		{return true;}
	else
		{return false;}
}



/*TVNumericValue::EStatus TAAffineTransformation::testStatus(TAAffineTransformation trans) const
{// give the status returned by an operator using two TAAffineTransfoamtion objects
	
	if (fStatus==kNull || trans.getStatus()==kNull)
	{
		return kNull;
	}
	else if (fStatus==trans.getStatus())
	{
		return fStatus;
	}
	else
	{
		return kUnknown;
	}
			
}*/