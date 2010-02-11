// TCompositeAffTransform.cpp
//
/** Class for transformations composed of multiple single transformations
Wrappers around those transformations are kept in a list*/
//
// Patterns:
// this class is close to the pattern Composite
// 
// Copyright 2000-10 CERN SU, M.Jones. All rights reserved.
//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
//#include  "TLength.h"

#include  "TCompositeAffTransform.h"
/*#include  "TScaleFactor.h"
#include  "TTranslation.h"
#include  "TReflection.h"
#include  "TRotation.h"
#include  "THelmertTransformation.h"*/

////////////////////////////////////////////////////////////////


//ClassImp(TCompositeAffTransform)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TCompositeAffTransform::TCompositeAffTransform()
{	// default constructor
	fStatus = kNull;
}


TCompositeAffTransform::TCompositeAffTransform( TCompositeAffTransform & original )
{	// copy constructor
	*this = original;
}


// Constructor taking a TAAffineTransformation
TCompositeAffTransform::TCompositeAffTransform( const TAAffineTransformation & transfn )
{
	TAffineTransformWrapper wrapper( transfn.clone() );
	fComposite.push_back(wrapper);
	setStatus(transfn.getStatus());
}


TCompositeAffTransform::~TCompositeAffTransform()
{//destructor
	if(fComposite.size() != 0)
	{
		fComposite.erase(fComposite.begin(), fComposite.end());
	}
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////



TCompositeAffTransform&  TCompositeAffTransform::operator=( TCompositeAffTransform& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		if(fComposite.size() != 0)
		{
			//fComposite.clear();
			fComposite.erase(fComposite.begin(), fComposite.end());
		}
		//fComposite = right.getComposite();
		TCompositeAffTransform::ConstCompositeIter  end = right.getCompositeEndIterator();
		TCompositeAffTransform::ConstCompositeIter  beg = right.getCompositeBeginIterator();

		while(beg != end)
		{
			fComposite.push_back(*beg);
			beg++;
		}

		setStatus(right.getStatus());
	}
	return *this;
}


//////////////////////////////////////////////////////////////////////
// Operator ()
// add to the composite transformation by applying this transformation 
// to an affine transformation
//////////////////////////////////////////////////////////////////////
TCompositeAffTransform& TCompositeAffTransform::operator()( const TAAffineTransformation& right )
{// Add another affine transformation to the composition  f = f(g())
	
	TAffineTransformWrapper wrapper( right.clone() );
	this->fComposite.push_front( wrapper );
	if (right.getStatus() == kNull && this->getStatus() != kNull)
	{
		setStatus(kNull);
	}
	return *this;	
	
}


TAAffineTransformation*  TCompositeAffTransform::clone() 
{// Return a pointer to a clone of this transformation
	return new TCompositeAffTransform( *this );
	
}


bool  TCompositeAffTransform::transform(TPositionVector& pv) const
{/// Return a transformed position vector
	bool trans = false;


	if (isNull() == false)
	{
		ConstCompositeIter iter = fComposite.begin();
		ConstCompositeIter iterEnd = fComposite.end();

		if(iter!=iterEnd) { trans = true; }
	
		while (iter != iterEnd && trans!=false)
		{
			trans = iter->getTransformation()->transform(pv);
			iter ++;
		}
	}

	return trans;	
}


bool  TCompositeAffTransform::transform(TFreeVector& fv) const 
{/// Return a transformed free vector
	bool trans = true;


	if (isNull() == false)
	{
		ConstCompositeIter iter = fComposite.begin();
		ConstCompositeIter iterEnd = fComposite.end();


		while (iter != iterEnd && trans != false)
		{
			trans = iter->getTransformation()->transform(fv);
			iter ++;
		}
	}

	return trans;
}


bool  TCompositeAffTransform::transform(TRotationMatrix& rm) const
{/// Return a transformed Rotation Matrix
	bool trans = true;
	
	if (isNull() == false)
	{
		ConstCompositeIter iter = fComposite.begin();
		ConstCompositeIter iterEnd = fComposite.end();

		if(iter!=iterEnd) { trans = true; }

		while (iter != iterEnd && trans != false)
		{
			trans = iter->getTransformation()->transform(rm);
			iter ++;
		}
	}

	return trans;
}



TCompositeAffTransform TCompositeAffTransform::inverse()
{/// Inverse
	TCompositeAffTransform copy(*this);
	copy.invert();
	return copy;
}


/*void TCompositeAffTransform::invert()
{/// Invert = Inverse but replace the transformation
	
	fComposite.reverse();
	CompositeIterator iter = fComposite.begin();
	CompositeIterator iterEnd = fComposite.end();
	while (iter != iterEnd)
	{	iter->getTransformation()->invert();
		iter ++;
	}
	return;
}*/


/*// Append a TAAffineTransformation
void TCompositeAffTransform::append( const TAAffineTransformation &transf )
{
	TAffineTransformWrapper wrapper( &transf );
	this->fComposite.push_front( wrapper );
	if (transf.getStatus() == kNull && this->getStatus() != kNull)
	{
		setStatus(kNull);
	}
	return;
}


// Prepend a TAAffineTransformation
void TCompositeAffTransform::prepend( const TAAffineTransformation &transf )
{
	TAffineTransformWrapper wrapper( &transf );
	this->fComposite.push_back( wrapper );
	if (transf.getStatus() == kNull && this->getStatus() != kNull)
	{
		setStatus(kNull);
	}
	return;
}*/
	

/*void TCompositeAffTransform::add(const TAAffineTransformation& right)
{ 
	TAffineTransformWrapper wrapper (&right);
	fComposite.push_front(wrapper);
	setStatus(right.getStatus());
	return;
}*/



///////////////////////////////////////////////////////////////////////////////////////
//END
///////////////////////////////////////////////////////////////////////////////////////




