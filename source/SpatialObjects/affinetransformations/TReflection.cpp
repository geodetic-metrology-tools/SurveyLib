// TReflection.cpp
//
/** 3D Reflection, affine transformation, six cases are distinguished:
Reflection by a plane x=0, y=0, z=0 or Reflection by the plane x=y, x=z or y=z*/
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
#include  "TLength.h"
#include  "TTranslation.h"
#include  "TRotation.h"
#include  "TEnlargement.h"
#include  "THelmertTransformation.h"
#include  "TAffineTransformWrapper.h"
#include  "TGraph.h"

#include  "TReflection.h"
////////////////////////////////////////////////////////////////


//ClassImp(TReflection)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TReflection::TReflection() : fReflectionMatrix(TCoordSysFactory::k3DCartesian)
{	// default constructor
	fReflectionType = kNull;
	setStatus(TAAffineTransformation::kNull);
}

TReflection::TReflection(const TReflection::EType type) : fReflectionMatrix(TCoordSysFactory::k3DCartesian)
{
	fReflectionType = type;
	setStatus(kKnown);
	fillMatrix(type);
}

TReflection::TReflection( const TReflection& original ) : fReflectionMatrix(TCoordSysFactory::k3DCartesian)
{	// copy constructor
	/*fReflectionType = original.getType();
	fillMatrix(fReflectionType);
	
	if (original.isNull()==true)
		{setStatus(TAAffineTransformation::kNull);}
	else
		{setStatus(TAAffineTransformation::kKnown);}
	*/

	*this = original;
}


TReflection::~TReflection()
{
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////



TReflection&  TReflection::operator=( const TReflection& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		fReflectionType = right.getType();
		fillMatrix(fReflectionType);
		
		setStatus(right.getStatus());

	}
	return *this;
}


TAAffineTransformation*  TReflection::clone() const
{// Return a pointer to a clone of this transformation
	return new TReflection( *this );
}


TCompositeAffTransform TReflection::operator*( const TAAffineTransformation& right)
{
	TAAffineTransformation* trans = new TReflection(*this);
	TAffineTransformWrapper wrapper(trans);
	TCompositeAffTransform result(wrapper);
	delete trans;
	return result * right;
}


bool TReflection::transform(TPositionVector& rightV) const
{/// Transform a TPositionVector
	// P*V1

	bool trans = false;

	if (isNull()==false)
	{
		rightV = fReflectionMatrix * rightV;
		trans = true;
	}		
	return trans;
}

		
bool TReflection::transform(TFreeVector & rightV) const
{/// Transform a TFreeVector
	// V2=P*V1
	bool trans = false;
	
	if (isNull()==false)
	{
		rightV = fReflectionMatrix * rightV;
		trans = true;
	}		
	return trans;
}

		
bool TReflection::transform(TRotationMatrix& rm) const
{/// Transform a TRotationMatrix
	bool trans = false;
	if (isNull() == false)
		trans = true;

	return trans;
}


TReflection  TReflection::inverse()
{/// Return the inverse transformation
	/*TReflection inverse(*this);
	return inverse;*/
	return *this;
}


void TReflection::invert()
{/// Change this transformation in the inverse
	return ;
}


//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////

void TReflection::fillMatrix( TReflection::EType type )
{
	// create identity
	fReflectionMatrix.initDiag(1);
	

	switch (type){

	case kNull:break;

	case kXEqual0: fReflectionMatrix.setElt(0,0,-1.0);break;

	case kYEqual0: fReflectionMatrix.setElt(1,1,-1.0);break;

	case kZEqual0: fReflectionMatrix.setElt(2,2,-1.0);break;

	case kXEqualY: fReflectionMatrix.setElt(0,0,0.0);
				fReflectionMatrix.setElt(1,1,0.0);
				fReflectionMatrix.setElt(0,1,1.0);
				fReflectionMatrix.setElt(1,0,1.0);break;

	case kXEqualZ: fReflectionMatrix.setElt(0,0,0.0);
				fReflectionMatrix.setElt(2,2,0.0);
				fReflectionMatrix.setElt(0,2,1.0);
				fReflectionMatrix.setElt(2,0,1.0);break;

	case kYEqualZ: fReflectionMatrix.setElt(1,1,0.0);
				fReflectionMatrix.setElt(2,2,0.0);
				fReflectionMatrix.setElt(1,2,1.0);
				fReflectionMatrix.setElt(2,1,1.0);break;

	default: break;
	}
	
return;
}

//////////////////////////////////////////////////////////////////////
//END
//////////////////////////////////////////////////////////////////////