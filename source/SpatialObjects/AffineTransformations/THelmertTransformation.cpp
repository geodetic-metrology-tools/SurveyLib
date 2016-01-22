/////////////////////////////////////////////////////////////////////////////
//THelmertTransformation.cpp
//
/** Classe pour une transformation helmert X1 = Fact*R*X+T*/
//
// Copyright 2000-2010 CERN SU, M.Jones. All rights reserved.
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
:fScaleFactor(LITERAL(1.0)), fRotation(), fTranslation()
{// default constructor
	this->setStatus( TVNumericValue::kNull );
}

THelmertTransformation::THelmertTransformation( const TScaleFactor& scale, const TRotation& rotate, const TTranslation& trans)
:fScaleFactor(scale), fRotation(rotate), fTranslation(trans)
{//Constructor
	if (scale.getStatus() != TVNumericValue::kNull 
		&& rotate.getStatus() != TVNumericValue::kNull 
		&& trans.getStatus() != TVNumericValue::kNull)
	{
		setStatus(TVNumericValue::kKnown);
	}
	else
	{
		setStatus(TVNumericValue::kNull);
	}
}


THelmertTransformation::THelmertTransformation( const TRotation& rotate, const TTranslation& trans)
:fScaleFactor(LITERAL(1.0)), fRotation(rotate), fTranslation(trans)
{// Constructor
	if (rotate.getStatus() != TVNumericValue::kNull 
		&& trans.getStatus() != TVNumericValue::kNull)
	{
		setStatus(TVNumericValue::kKnown);
	}
	else
	{
		setStatus(TVNumericValue::kNull);
	}
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
		setStatus(right.getStatus());
	}
	return *this;
}


void THelmertTransformation::setTransformations(const TScaleFactor& scale, const TRotation& rotate, const TTranslation& trans)
{ // Set all 3 transformations
	fScaleFactor = scale;
	fRotation = rotate;
	fTranslation = trans;

	if (scale.getStatus() != TVNumericValue::kNull 
		&& rotate.getStatus() != TVNumericValue::kNull 
		&& trans.getStatus() != TVNumericValue::kNull)
	{
		setStatus(TVNumericValue::kKnown);
	}
	else
	{
		setStatus(TVNumericValue::kNull);
	}	
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
	if (isNull()==false)
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

	if (isNull()==false)
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

	if (isNull()==false)
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
	if ( this->isNull() || !right.isInitialise() )
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
	if (this->isNull() || !right.isInitialise())
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
	if ( this->isNull() || !right.isInitialise() )
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



