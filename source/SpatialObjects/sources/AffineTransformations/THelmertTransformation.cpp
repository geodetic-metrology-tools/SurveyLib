/////////////////////////////////////////////////////////////////////////////
//THelmertTransformation.cpp
//
/** Classe pour une transformation helmert X1 = Fact*R*X+T*/
//
/////////////////////////////////////////////////////////////////////////////

//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
#include  "THelmertTransformation.h"
#include  "TPositionVector.h"
#include  "TFreeVector.h"
#include  "TRotationMatrix.h"
////////////////////////////////////////////////////////////////



//ClassImp(THelmertTransformation)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

THelmertTransformation::THelmertTransformation()
	:fScaleFactor(LITERAL(1.0)), fRotation(), fTranslation(), fTranslationStd(), fRotationStd(), fScaleStd()
{// default constructor
}

THelmertTransformation::THelmertTransformation( const TScaleFactor& scale, const TRotation& rotate, const TTranslation& trans)
	: fScaleFactor(scale), fRotation(rotate), fTranslation(trans), fTranslationStd(), fRotationStd(), fScaleStd()
{//Constructor
}


THelmertTransformation::THelmertTransformation( const TRotation& rotate, const TTranslation& trans)
	:fScaleFactor(LITERAL(1.0)), fRotation(rotate), fTranslation(trans), fTranslationStd(), fRotationStd(), fScaleStd()
{// Constructor
}

THelmertTransformation::THelmertTransformation( const  THelmertTransformation& original )
{	// copy constructor

	*this = original;
}


THelmertTransformation::~THelmertTransformation()
{
}


//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////

THelmertTransformation &  THelmertTransformation::operator=(const THelmertTransformation & right)
{	// Copy Assignment operator

	if (this != &right)
	{
		fScaleFactor = right.getScaleFactor();
		fRotation = right.getRotation();
		fTranslation = right.getTranslation();
		fScaleStd = right.getScaleFactorStd();
		fRotationStd = right.getRotationStd();
		fTranslationStd = right.getTranslationStd();
	}
	return *this;
}


void THelmertTransformation::setTransformations(const TScaleFactor& scale, const TRotation& rotate, const TTranslation& trans)
{ // Set all 3 transformations
	fScaleFactor = scale;
	fRotation = rotate;
	fTranslation = trans;
	
	return;
}


THelmertTransformation*  THelmertTransformation::clone() const
{// Return a pointer to a clone of this transformation
	return new THelmertTransformation( *this );
}


//////////////////////////////////////////////////////////////////////
// Transformation methods
//////////////////////////////////////////////////////////////////////
bool  THelmertTransformation::transform(TPositionVector& pv) const
{/// Transform a position vector
	bool trans = false;
	if (isInitialise())
	{	
		trans = rotation()->transform(pv);
		if (trans == true)
			trans = scaleFactor()->transform(pv);
		if (trans ==true)
			trans = translation()->transform(pv);
	}
	return trans;
}


bool  THelmertTransformation::transform(TFreeVector& fv ) const 
{/// Transform a free vector
	bool trans = false;

	if (isInitialise())
	{	
		trans = rotation()->transform(fv);
		if (trans == true)
			trans = scaleFactor()->transform(fv);
		if (trans ==true)
			trans = translation()->transform(fv);
	}
	return trans;
}



bool  THelmertTransformation::transform(TRotationMatrix& rm) const
{/// Transform a Rotation Matrix
	bool trans = false;

	if (isInitialise())
	{	
		trans = rotation()->transform(rm);
		if (trans == true)
			trans = scaleFactor()->transform(rm);
		if (trans ==true)
			trans = translation()->transform(rm);
	}
	return trans;
}


TPositionVector &  THelmertTransformation::operator() ( TPositionVector & right ) const
{// apply this transformation to a position vector
	if (!isInitialise() || !right.isInitialise())
	{
		//right.setStatus( TVNumericValue::kNull );
	}
	else
	{
      //See that later if we want to replace the class by a TAdjustableHelmertTransformation
		//fTranslation( fScaleFactor( fRotation( right ) ) ); 
	}
	return right;
}


TFreeVector &  THelmertTransformation::operator() ( TFreeVector & right ) const
{// apply this transformation to a free vector
	if (!isInitialise() || !right.isInitialise())
	{
		//right.setStatus( TVNumericValue::kNull );
	}
	else
	{
      //See that later if we want to replace the class by a TAdjustableHelmertTransformation
		//fTranslation( fScaleFactor( fRotation( right ) ) ); 
	}
	return right;
}


TRotationMatrix &  THelmertTransformation::operator() ( TRotationMatrix & right ) const
{// apply this transformation to a Rotation Matrix
	if (!isInitialise() || !right.isInitialise())
	{
		//right.setStatus( TVNumericValue::kNull );
	}
	else
	{
      //See that later if we want to replace the class by a TAdjustableHelmertTransformation
		//fTranslation( fScaleFactor( fRotation( right ) ) ); 
	}
	return right;
}


THelmertTransformation * THelmertTransformation::inverse() const
{/// Return the inverse ht X = R~-1*(1/factor)(x-T);
	THelmertTransformation * inver = this->clone();
	inver->invert();
	return inver;
}


void THelmertTransformation::invert()
{/// Invert the transformation, X = R~-1*(1/factor)(x-T) 
	fScaleFactor.invert();
	fRotation.invert();
	fTranslation.invert();
	fTranslation = (fRotation.getRotationMatrix()*fTranslation.getVector())*fScaleFactor.getScaleFactor();
	return;
}


bool THelmertTransformation::isInitialise() const
{
	if (fScaleFactor.isInitialise() && fRotation.isInitialise() && fTranslation.isInitialise())
		return true;
	else
		return false;
}


