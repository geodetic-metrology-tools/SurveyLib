// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

// TTranslation.cpp
//
/** A Scaling Transformation */
//
// Patterns:
//
// 
//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
#include  "TTranslation.h"
#include  "TPositionVector.h"
#include  "TFreeVector.h"
#include  "TRotationMatrix.h"
////////////////////////////////////////////////////////////////


//ClassImp(TTranslation)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TTranslation::TTranslation() : fTranslationVector(TCoordSysFactory::k3DCartesian)
{	// default constructor
}




TTranslation::TTranslation(const TLength Tx, const TLength Ty, const TLength Tz)
 : fTranslationVector(TCoordSysFactory::k3DCartesian)
{
	fTranslationVector.setX(Tx);
	fTranslationVector.setY(Ty);
	fTranslationVector.setZ(Tz);
}


TTranslation::TTranslation(const TFreeVector vector) : fTranslationVector(TCoordSysFactory::k3DCartesian)
{
	fTranslationVector = vector;
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


TTranslation&  TTranslation::operator=(const TTranslation & right)
{	// Copy Assignment operator

	if (this != &right)	
		fTranslationVector = right.fTranslationVector;			

	return *this;
}


TTranslation TTranslation::operator+(const TTranslation& right)
{
	TTranslation result( fTranslationVector + right.fTranslationVector );
	return result;
}


TTranslation*  TTranslation::clone() const
{// Return a pointer to a clone of this transformation
	return new TTranslation( *this );
}


//////////////////////////////////////////////////////////////////////
// Transformations
//////////////////////////////////////////////////////////////////////

bool TTranslation::transform(TPositionVector& pv)const
{// TTranslate a vector of position

	if (fTranslationVector.isInitialise())
	{
		pv += fTranslationVector;
		return true;
	}
	else
		return false;
}


bool TTranslation::transform(TFreeVector& fv)const
{// Transform a free vector
	ignoring(fv);

	return fTranslationVector.isInitialise();

}


bool TTranslation::transform(TRotationMatrix& rm)const
{// Transform a rotation matrix
	ignoring(rm);
	return fTranslationVector.isInitialise();
}


/* apply this transformation to a position vector */
TPositionVector &  TTranslation::operator() ( TPositionVector & right ) const
{
	if (fTranslationVector.isInitialise() && right.isInitialise())
		right += this->getVector();

	return right;
}


/* apply this transformation to a free vector */
TFreeVector &  TTranslation::operator() ( TFreeVector & right ) const
{
	return right;
}


/* apply this transformation to a Rotation Matrix */
TRotationMatrix &  TTranslation::operator() ( TRotationMatrix & right ) const
{
	return right;
}


TTranslation * TTranslation::inverse() const
{// Return a pointer to the inverse of this transformation
	TTranslation * copy = this->clone();
	copy->invert();
	return copy;
}


void TTranslation::invert()
{// Invert the transformation, replaces the current transformation parameters
	TFreeVector defaut(0,0,0, TCoordSysFactory::k3DCartesian);
	fTranslationVector= defaut-fTranslationVector;
	
	return;
}
