// TScaleFactor.cpp
//
/** A Scaling Transformation */
//
// Patterns:
//
// 
// Copyright 2010 CERN SU, M.Jones. All rights reserved.
//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
#include  "TScaleFactor.h"
#include  "TPositionVector.h"
#include  "TFreeVector.h"
#include  "TRotationMatrix.h"
////////////////////////////////////////////////////////////////


//ClassImp(TScaleFactor)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TScaleFactor::TScaleFactor()
{	// default constructor
	fScaleFactor = LITERAL(1.0);
	this->setStatus( TVNumericValue::kNull );
}

TScaleFactor::TScaleFactor( TReal f )
{	// constructor taking factor
	fScaleFactor = f;
	this->setStatus( TVNumericValue::kKnown );
}

TScaleFactor::TScaleFactor( const  TScaleFactor & original )
{	// copy constructor
	*this = original;

}

TScaleFactor::~TScaleFactor()
{
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////


TScaleFactor& TScaleFactor::operator=(const TScaleFactor & right)
{	// Copy Assignment operator

	if (this != &right)
	{
		fScaleFactor = right.fScaleFactor;
		setStatus( right.getStatus() );
	}

	return *this;
}

//! Multiplication by another scaling transformation
TScaleFactor TScaleFactor::operator*( const TScaleFactor & right )
{
	return TScaleFactor ( fScaleFactor * right.fScaleFactor );
}

TScaleFactor* TScaleFactor::clone() const
{// Return a pointer to a clone of this transformation
	return new TScaleFactor( *this );
}

//////////////////////////////////////////////////////////////////////
// Transforme
//////////////////////////////////////////////////////////////////////

bool TScaleFactor::transform(TPositionVector& pv) const
{/// Return a transformed position vector
	if(!isNull())
	{
		pv *= fScaleFactor;
		return true;
	}
	return false;
}

bool TScaleFactor::transform(TFreeVector& fv) const
{/// Return a transformed free vector
	if (!isNull())
	{
		fv *= fScaleFactor;
		return true;
	}
	return false;
}
	
bool TScaleFactor::transform(TRotationMatrix& rm) const
{/// Return a transformed rotation matrix
	ignoring(rm);

	if (!isNull())
		return  true;

	return false;
}

TPositionVector &  TScaleFactor::operator() ( TPositionVector & right ) const
{// apply this transformation to a position vector
	if ( this->isNull() || right.isNull() )
		right.setStatus( TVNumericValue::kNull );
   else
	   right = right * fScaleFactor;

	return right;
}

TFreeVector &  TScaleFactor::operator() ( TFreeVector & right ) const
{// apply this transformation to a free vector
	if ( this->isNull() || right.isNull() )
		right.setStatus(TVNumericValue::kNull);
	else
      right = right * fScaleFactor;

	return right;
}

TRotationMatrix &  TScaleFactor::operator() ( TRotationMatrix & right ) const
{// apply this transformation to a Rotation Matrix
	if ( this->isNull() )
		right.setStatus( TVNumericValue::kNull );
	
	return right;
}

TScaleFactor* TScaleFactor::inverse() const
{// Return the inverse transformation
   return new TScaleFactor(LITERAL(1.0) / fScaleFactor);
}

void TScaleFactor::invert()
{/// Change this transformation in the inverse
	fScaleFactor = ( LITERAL(1.0) / fScaleFactor );
}

TReal TScaleFactor::getScaleFactor() const 
{//! get the scale factor
   return fScaleFactor;
}

