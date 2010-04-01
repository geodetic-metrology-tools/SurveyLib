// TEnlargement.cpp
//
/** Class for scaling */
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
#include  "TTranslation.h"
#include  "TRotation.h"
#include  "TReflection.h"
#include  "TEnlargement.h"
#include  "THelmertTransformation.h"
#include  "TCompositeAffTransform.h"
////////////////////////////////////////////////////////////////


//ClassImp(TEnlargement)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TEnlargement::TEnlargement()
{	// default constructor
	fScaleFactor.setValue(1.0);
	fStatus = kNull;
}


TEnlargement::TEnlargement(quad f)
{	// constructor taking factor
	fScaleFactor.setValue(f);
	setStatus(kKnown);
}

TEnlargement::TEnlargement(TDouble f)
{	// constructor taking factor
	fScaleFactor = f;
	setStatus(kKnown);
}


TEnlargement::TEnlargement( const  TEnlargement& original )
{	// copy constructor
	*this = original;
	
}


TEnlargement::~TEnlargement()
{
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////


TEnlargement&  TEnlargement::operator=(const TEnlargement& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		fScaleFactor = right.getFactor();
		setStatus(right.getStatus());
	}
	return *this;
}

//////////////////////////////////////////////////////////////////////
// Composition
//////////////////////////////////////////////////////////////////////
TCompositeAffTransform TEnlargement::operator*( const TAAffineTransformation& trans )
{
	TAAffineTransformation* transfo = new TEnlargement(*this);
	TAffineTransformWrapper wrapper(transfo);
	TCompositeAffTransform result(wrapper);
	delete transfo;

	return (result*trans);
}



TAAffineTransformation*  TEnlargement::clone() const
{// Return a pointer to a clone of this transformation
	return new TEnlargement( *this );
}

//////////////////////////////////////////////////////////////////////
// Transforme
//////////////////////////////////////////////////////////////////////

bool  TEnlargement::transform(TPositionVector& pv)const
{/// Return a transformed position vector
	bool trans = false;

	if (isNull()==false)
	{
		pv = pv * this->getFactor();
		trans = true;
	}
	return trans;
}

	
bool  TEnlargement::transform(TFreeVector& fv)const
{/// Return a transformed free vector
	bool trans = false;
	if (isNull()==false)
	{
		fv = fv * this->getFactor().getValue();
		trans = true;
	}
	return trans;
}

	
bool TEnlargement::transform(TRotationMatrix& rm)const
{/// Return a transformed rotation matrix
	bool trans = false;
	if (isNull()==false)
	{
		trans = true;
	}
	return trans;
}

		



TEnlargement  TEnlargement::inverse()
{/// Return the inverse transformation
	TEnlargement inverse(1/(this->getFactor().getValue()));
	return inverse;
}


void TEnlargement::invert()
{/// Change this transformation in the inverse
	fScaleFactor.setValue(1/fScaleFactor.getValue());
	return;
}


