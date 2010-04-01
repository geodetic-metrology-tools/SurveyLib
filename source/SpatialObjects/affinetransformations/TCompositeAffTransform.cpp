// TCompositeAffTransform.cpp
//
/** Class for transformations composed of multiple single transformation*/
//
// Patterns:
// this class follows the pattern Composite
//
// 
// Copyright 2000 CERN EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
//#include  "TLength.h"
#include  "TTranslation.h"
#include  "TRotation.h"
#include  "TReflection.h"
#include  "THelmertTransformation.h"
#include  "TEnlargement.h"

#include  "TCompositeAffTransform.h"

////////////////////////////////////////////////////////////////


//ClassImp(TCompositeAffTransform)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TCompositeAffTransform::TCompositeAffTransform() : fComposite(0)
{	// default constructor
	fStatus = kNull;
}


TCompositeAffTransform::TCompositeAffTransform(  const TCompositeAffTransform& original )
{	// copy constructor
	*this = original;
}


TCompositeAffTransform::TCompositeAffTransform( const TAffineTransformWrapper wrapper )
{
	fComposite.push_back(wrapper);
	setStatus(wrapper.getTransformation()->getStatus());
}


TCompositeAffTransform::~TCompositeAffTransform()
{//destructor
	if(fComposite.size() != 0)
	{
//		fComposite.~list<TAffineTransformWrapper>();
		fComposite.erase(fComposite.begin(), fComposite.end());

		list<TAffineTransformWrapper>::iterator iter;// = fComposite.begin();
		list<TAffineTransformWrapper>::iterator end = fComposite.end();
//		int i = 0;
//		while(i != end)
/*		while((iter = fComposite.begin())  != end)
		{
			TVAffineTransformation* trans = iter->getTransformation();
			TAffineTransformWrapper temp = *iter;
			fComposite.pop_front();//.remove(iter);
			cout<<"avant delete"<<endl;
			//iter->~TAffineTransformWrapper();
			cout<<"test1"<<endl;
			//delete (trans);
			//iter++;
		}*/

//	cout<<"test2"<<endl;
	}
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////



TCompositeAffTransform&  TCompositeAffTransform::operator=( const TCompositeAffTransform& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		if(fComposite.size() != 0)
		{
			//fComposite.clear();
			fComposite.erase(fComposite.begin(), fComposite.end());
		}
		//fComposite = right.getComposite();
		TCompositeAffTransform::CompositeIterator  end = right.getCompositeEndIterator();
		TCompositeAffTransform::CompositeIterator  beg = right.getCompositeBeginIterator();

		while(beg != end)
		{
			fComposite.push_back(*beg);
			beg++;
		}

		setStatus(right.getStatus());
	}
	return *this;
}


TAAffineTransformation*  TCompositeAffTransform::clone() const
{// Return a pointer to a clone of this transformation
	return new TCompositeAffTransform( *this );
	
}

//////////////////////////////////////////////////////////////////////
// Operator *
//////////////////////////////////////////////////////////////////////
TCompositeAffTransform TCompositeAffTransform::operator*( const TAAffineTransformation& right)
{// Multiplication by affine transformation  C = P * right
	
/*	TVAffineTransformation*  trans = right.clone();
	TAffineTransformWrapper wrapper(trans);
	fComposite.push_front(wrapper);	
	delete trans;
	
	if (right.getStatus() == kNull)
	{setStatus(kNull);}*/

	TCompositeAffTransform result;
	result = *this;

//	TVAffineTransformation*  trans = right.clone();
//	TAffineTransformWrapper wrapper(trans);
	result.add(right);	
//	delete trans;
	
	if (right.getStatus() == kNull)
	{setStatus(kNull);}
	
	return result;	
	
}



bool  TCompositeAffTransform::transform(TPositionVector& pv) const
{/// Return a transformed position vector
	bool trans = false;


	if (isNull() == false)
	{
		CompositeIterator iter = fComposite.begin();
		CompositeIterator iterEnd = fComposite.end();

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
		CompositeIterator iter = fComposite.begin();
		CompositeIterator iterEnd = fComposite.end();


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
		CompositeIterator iter = fComposite.begin();
		CompositeIterator iterEnd = fComposite.end();

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


void TCompositeAffTransform::invert()
{/// Invert = Inverse but replace the transformation
	
	fComposite.reverse();
	CompositeIterator iter = fComposite.begin();
	CompositeIterator iterEnd = fComposite.end();
	while (iter != iterEnd)
	{	iter->getTransformation()->invert();
		iter ++;
	}
	return;
}


void TCompositeAffTransform::add(const TAAffineTransformation& right)
{ 
	TAffineTransformWrapper wrapper (&right);
	fComposite.push_front(wrapper);
	setStatus(right.getStatus());
	return;
}


///////////////////////////////////////////////////////////////////////////////////////
//END
///////////////////////////////////////////////////////////////////////////////////////




