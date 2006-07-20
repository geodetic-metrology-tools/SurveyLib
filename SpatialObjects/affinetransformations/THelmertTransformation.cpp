/////////////////////////////////////////////////////////////////////////////
//THelmertTransformation.cpp
//
/** Classe pour une transformation helmert X1 = Fact*R*X+T*/
//
// Copyright 2000, CERN EST/SU. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations

#include  "THelmertTransformation.h"
////////////////////////////////////////////////////////////////



//ClassImp(THelmertTransformation)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

THelmertTransformation::THelmertTransformation():fEnlargement(1.0),fRotation(),fTranslation()
{
	fStatus = kNull;
}

THelmertTransformation::THelmertTransformation( const TEnlargement& scale, const TRotation& rotate, const TTranslation& trans)
{
	fEnlargement = scale;
	fRotation = rotate;
	fTranslation = trans;
	if (scale.getStatus() != kNull && rotate.getStatus() != kNull && trans.getStatus() != kNull)
	{setStatus(kKnown);}
	else
	{setStatus(kNull);}
}


THelmertTransformation::THelmertTransformation( const TRotation& rotate, const TTranslation& trans):fEnlargement(1.0)
{
	fRotation = rotate;
	fTranslation = trans;
	if (rotate.getStatus() != kNull && trans.getStatus() != kNull)
	{setStatus(kKnown);}
	else
	{setStatus(kNull);}

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

THelmertTransformation&  THelmertTransformation::operator=(const THelmertTransformation& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		fEnlargement = right.getEnlargement();
		fRotation = right.getRotation();
		fTranslation = right.getTranslation();
		setStatus(right.getStatus());

	}
	return *this;
}

//////////////////////////////////////////////////////////////////////
// Composition
//////////////////////////////////////////////////////////////////////
TCompositeAffTransform THelmertTransformation::operator*( const TAAffineTransformation& right )
{
	TAAffineTransformation* trans = new THelmertTransformation(*this);
	TAffineTransformWrapper wrapper(trans);
	TCompositeAffTransform result(wrapper);
	delete trans;

	return result * right;
}



TAAffineTransformation*  THelmertTransformation::clone() const
{// Return a pointer to a clone of this transformation
	return new THelmertTransformation( *this );
}


void THelmertTransformation::setTransformations(const TEnlargement& scaling, const TRotation& rotate, const TTranslation& trans)
{ 
	fEnlargement = scaling;
	fRotation = rotate;
	fTranslation = trans;
	return;
}


THelmertTransformation* THelmertTransformation::getTransformations() const
{
	return new THelmertTransformation(*this);
}
	

//////////////////////////////////////////////////////////////////////
// Transforme
//////////////////////////////////////////////////////////////////////
bool  THelmertTransformation::transform(TPositionVector& pv) const
{/// Return a transformed position vector
	bool trans = false;
	if (isNull()==false)
	{	
		trans = fRotation.transform(pv);
		if (trans == true)
			trans = fEnlargement.transform(pv);
		if (trans ==true)
			trans = fTranslation.transform(pv);

	}
	return trans;
}


bool  THelmertTransformation::transform(TFreeVector& fv ) const 
{/// Return a transformed free vector
	bool trans = false;

	if (isNull()==false)
	{	
		trans = fRotation.transform(fv);
		if (trans == true)
			trans = fEnlargement.transform(fv);
		if (trans ==true)
			trans = fTranslation.transform(fv);

	}
	return trans;
}



bool  THelmertTransformation::transform(TRotationMatrix& rm) const
{/// Return a transformed Rotation Matrix
	bool trans = false;

	if (isNull()==false)
	{	
		trans = fRotation.transform(rm);
		if (trans == true)
			trans = fEnlargement.transform(rm);
		if (trans ==true)
			trans = fTranslation.transform(rm);

	}
	return trans;
}




THelmertTransformation THelmertTransformation::inverse()
{/// Return the inverse ht X = R~-1*(1/factor)(x-T);
	THelmertTransformation inver(*this);
	inver.invert();
	return inver;
}


void THelmertTransformation::invert()
{/// Invert the transformation 
	fEnlargement.invert();
	fRotation.invert();
	fTranslation.invert();
	fTranslation=(fRotation.getRotationMatrix()*fTranslation.getVector())*fEnlargement.getFactor();
	return;
}



