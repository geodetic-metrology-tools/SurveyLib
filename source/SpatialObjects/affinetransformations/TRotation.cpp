// TRotation.cpp
//
/** Class for rotations of TPositionVector and TFreeVector. 
It authorizes the inverse rotation and the multiplication 
by an other rotation or vector. Sub classes for rotations around each axis*/
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
#include  "TTranslation.h"
#include  "TRotation.h"
#include  "TEnlargement.h"
#include  "TReflection.h"
#include  "THelmertTransformation.h"
#include  "TCompositeAffTransform.h"
#include  "TAffineTransformWrapper.h"
#include  "TGraph.h"
////////////////////////////////////////////////////////////////


//ClassImp(TRotation)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TRotation::TRotation()
{	// default constructor

	fStatus = kNull;
	fRotationMatrix.identity();

}

TRotation::TRotation( const TRotationMatrix matrix)
{//Constructor taking the rotation matrix
	fRotationMatrix = matrix;
	setStatus(kKnown);
}





TRotation::TRotation(TRotationMatrix::ERotationType kR, double omega, double phi, double kappa)
: fRotationMatrix(kR, omega, phi, kappa)
{//Constructor taking the radians values of the angles in the specified order
	
	//fillRotationMatrix(kR, omega, phi, kappa);
	setStatus(kKnown);
}




TRotation::TRotation( const  TRotation& original )
{	// copy constructor
	*this = original;
}


TRotation::~TRotation()
{
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////


TRotation&  TRotation::operator=(const TRotation& right)
{	// Copy Assignment operator


	fRotationMatrix = right.getRotationMatrix();
	setStatus(kKnown);

	return *this;
}


TAAffineTransformation*  TRotation::clone() const
{// Return a pointer to a clone of this transformation
	return new TRotation( *this );
}


double TRotation::operator()(int i, int j) const
{
	// return the ri, cj element with 0<=i,j<=2
	return fRotationMatrix.getElt(i,j);
}

/*insure
double& TRotation::operator()(int i, int j) 
{
	// return the ri, cj element with 0<=i,j<=2
	double* d = new double (fRotationMatrix.getElt(i,j));
	return *d;
}*/

//////////////////////////////////////////////////////////////////////
// Composition
//////////////////////////////////////////////////////////////////////
TCompositeAffTransform TRotation::operator*(const TAAffineTransformation& right)
{
	TAAffineTransformation* trans = new TRotation(*this);
	TAffineTransformWrapper wrapper(trans);//effectue une copie avec clone
	TCompositeAffTransform result(wrapper);
	delete trans;

	return result * right;
}


void TRotation::setAllRotations(TRotationMatrix::ERotationType kR, double &om, double &p, double &k)
{
	fRotationMatrix.setAllRotations(kR,om,p,k);
}



//////////////////////////////////////////////////////////////////////
// Transforme
//////////////////////////////////////////////////////////////////////

bool TRotation::transform(TPositionVector& pv) const
{/// Rotate a vector of position

	bool trans = false;

	if (isNull()==false)
	{
		pv = this->getRotationMatrix() * pv;
		trans = true;
	}
	return trans;
}
		
		
bool TRotation::transform(TFreeVector& fv) const
{/// Rotate a free vector
	bool trans = false;

	if (isNull()==false)
	{
		fv = this->getRotationMatrix() * fv;
		trans = true;
	}
	return trans;
}


bool  TRotation::transform(TRotationMatrix& rm) const 
{

	bool trans = false;

	if (isNull()==false)
	{
		rm = this->getRotationMatrix() * rm;
		trans = true;
	}
	return trans;
}



	
TRotation TRotation::inverse()
{/// Return the inverse rotation
	TRotation  copy(*this);
	copy.invert();
	return copy;
}
	
	
void TRotation::invert()
{
	fRotationMatrix.invert();
	return;
}


//////////////////////////////////////////////////////////////////////
// Private Member Functions
//////////////////////////////////////////////////////////////////////
void TRotation::fillRotationMatrix(TRotationMatrix::ERotationType kR, double om, double p, double k)
{
	fRotationMatrix.setAllRotations(kR,om,p,k);
	return;
}



Angles TRotation::getAngles(TRotationMatrix::ERotationType kR)
{
	Angles xyz;
	xyz=fRotationMatrix.getAngles(kR);

	return xyz;
}

//////////////////////////////////////////////////////////////////////
//END
//////////////////////////////////////////////////////////////////////