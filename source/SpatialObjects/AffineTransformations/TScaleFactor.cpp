
#include  "TScaleFactor.h"
#include  "TPositionVector.h"
#include  "TFreeVector.h"
#include  "TRotationMatrix.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TScaleFactor::TScaleFactor()
{	// default constructor
	fScaleFactor = LITERAL(1.0);
}

TScaleFactor::TScaleFactor( TReal f )
{	// constructor taking factor
	fScaleFactor = f;
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
		fScaleFactor = right.getScaleFactor();

	return *this;
}

//! Multiplication by another scaling transformation
TScaleFactor TScaleFactor::operator*( const TScaleFactor & right )
{
	return TScaleFactor(fScaleFactor * right.getScaleFactor());
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
	if(isInitialise())
	{
		pv *= fScaleFactor;
		return true;
	}
	return false;
}

bool TScaleFactor::transform(TFreeVector& fv) const
{/// Return a transformed free vector
	if (isInitialise())
	{
		fv *= fScaleFactor;
		return true;
	}
	return false;
}
	
bool TScaleFactor::transform(TRotationMatrix& rm) const
{/// Return a transformed rotation matrix
	ignoring(rm);

	if (isInitialise())
		return  true;

	return false;
}

TPositionVector &  TScaleFactor::operator() ( TPositionVector & right ) const
{// apply this transformation to a position vector
	if (!this->isInitialise() || !right.isInitialise())
	{
		//right.setStatus( TVNumericValue::kNull );
	}
	   right = right * fScaleFactor;

	return right;
}

TFreeVector &  TScaleFactor::operator() ( TFreeVector & right ) const
{// apply this transformation to a free vector
	if (!this->isInitialise() || !right.isInitialise())
	{
		//right.setStatus( TVNumericValue::kNull );
	}
      right = right * fScaleFactor;

	return right;
}

TRotationMatrix &  TScaleFactor::operator() ( TRotationMatrix & right ) const
{// apply this transformation to a Rotation Matrix
	if (!this->isInitialise())
		//right.setStatus( TVNumericValue::kNull );
	
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

bool TScaleFactor::isInitialise() const
{
	if (fScaleFactor == NO_VALf)
		return false;
	else
		return true;
}

