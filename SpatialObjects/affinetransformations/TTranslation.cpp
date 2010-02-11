// TTranslation.cpp
//
/** Class for translations 
    Operators: + Translation*/
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
#include  "TPositionVector.h"
#include  "TTranslation.h"
#include  "TGraph.h"
////////////////////////////////////////////////////////////////


//ClassImp(TTranslation)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TTranslation::TTranslation() : fTranslationVector(TCoordSysFactory::k3DCartesian)
{	// default constructor
	fStatus=kNull;
	
}




TTranslation::TTranslation(const TLength Tx, const TLength Ty, const TLength Tz)
 : fTranslationVector(TCoordSysFactory::k3DCartesian)
{
	fTranslationVector.setX(Tx);
	fTranslationVector.setY(Ty);
	fTranslationVector.setZ(Tz);
	fTranslationVector.setStatus(kKnown);
	setStatus(kKnown);
}


TTranslation::TTranslation(const TFreeVector vector) : fTranslationVector(TCoordSysFactory::k3DCartesian)
{
	fTranslationVector = vector;
	setStatus(kKnown);
}


TTranslation::TTranslation( const  TTranslation& original )
 : fTranslationVector(TCoordSysFactory::k3DCartesian)
{	// copy constructor

	*this = original;
}


TTranslation::~TTranslation()
{
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////


TTranslation&  TTranslation::operator=(const TTranslation& right)
{	// Copy Assignment operator

	if (this != &right)
	{		
		fTranslationVector = right.fTranslationVector;			
		setStatus(right.getStatus());
	}
	return *this;
}


TCompositeAffTransform TTranslation::operator*( TAAffineTransformation& right)
{ 
	TAAffineTransformation* trans = new TTranslation(*this);
	TAffineTransformWrapper wrapper(trans);
	TCompositeAffTransform result(wrapper);
	delete trans;

	return result * right;
}



TAAffineTransformation*  TTranslation::clone() const
{// Return a pointer to a clone of this transformation
	return new TTranslation( *this );
}


TTranslation TTranslation::operator+(const TTranslation& right)
{
	TTranslation sum((fTranslationVector + right.fTranslationVector));
	
	
	if (getStatus()==kNull || right.getStatus()==kNull)
	{
		sum.setStatus( kNull );
	}
	else if (getStatus()==right.getStatus())
	{
		sum.setStatus(getStatus());
	}
	else 
	{
		sum.setStatus(kKnown);
	}
	

	return sum;
}


//////////////////////////////////////////////////////////////////////
// Transformations
//////////////////////////////////////////////////////////////////////

bool TTranslation::transform(TPositionVector& pv)const
{/// TTranslate a vector of position

	bool trans = false;
	if (isNull()==false)
	{
		pv += fTranslationVector;
		trans = true;
	}
	return trans;
}


bool TTranslation::transform(TFreeVector& fv)const
{/// Transform a free vector
	bool trans = false;
	if (isNull() == false)
	{
		trans = true;
	}

	return trans;
}


bool TTranslation::transform(TRotationMatrix& rm)const
{/// Transform a rotation matrix
	bool trans = false;
	if (isNull() == false)
	{
		trans = true;
	}

	return trans;
}





TTranslation TTranslation::inverse()
{
	TTranslation copy(*this);
	copy.invert();
	return copy;
}


void TTranslation::invert()
{
	TFreeVector defaut(0,0,0, TCoordSysFactory::k3DCartesian);
	fTranslationVector.setStatus(kKnown);
	fTranslationVector= defaut-fTranslationVector;
	
	return;
}
