//  TTrf2TrfTransformation.cpp
//
/** A Helmert transformation between two terrestrial reference frames.

	The two reference frames should be terrestrial reference frames


	Patterns:


	Copyright 2021 CERN BE/GM. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////

//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations

#include  "TTrf2TrfTransformation.h"
#include  "THelmertTransformation.h"
#include  "TCompositeAffTransform.h"
#include  "THelmertRefFrameTransform.h"
#include  "TAReferenceFrame.h"
////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// CONSTRUCTOR / DESTRUCTOR
//////////////////////////////////////////////////////////////////////
TTrf2TrfTransformation::TTrf2TrfTransformation()
	: fFrom(0), fTo(0), fTransform(0)
{	// default constructor
}


TTrf2TrfTransformation::TTrf2TrfTransformation(TTerrestrialReferenceFrame* from,
											   TTerrestrialReferenceFrame* to,
											   THelmertTransformation* transform)
: fFrom(from), fTo(to), fTransform(0)
{	// constructor taking pointers to the source and destination reference frames
}

TTrf2TrfTransformation::TTrf2TrfTransformation(TTerrestrialReferenceFrame* from,
											   TTerrestrialReferenceFrame* to,
											   const TScaleFactor& enlarg, const TRotation& rot, const TTranslation& transl)
: fFrom(from), fTo(to), fTransform(0)
{
	setTransform(enlarg, rot, transl);
}


TTrf2TrfTransformation::TTrf2TrfTransformation(const  TTrf2TrfTransformation& original)
	: fFrom(0), fTo(0), fTransform(0)
{// copy constructor
	*this = original;
}

TTrf2TrfTransformation::~TTrf2TrfTransformation()
{//destructor
}

//////////////////////////////////////////////////////////////////////
//MEMBER FUNCTIONS
//////////////////////////////////////////////////////////////////////

void TTrf2TrfTransformation::calcDeltaEpoch()
{
	
	this->setDetltaEpoch (this->fFrom->getEpoch() - this->fTo->getEpoch());
	//this->getSourceFrame()->epoch

}


TTrf2TrfTransformation& TTrf2TrfTransformation::operator=(const TTrf2TrfTransformation& right)
{	// Copy Assignment operator
	if (this != &right)
	{
		setSourceFrame(right.getSourceFrame());
		setDestinationFrame(right.getDestinationFrame());
	}
	return *this;
}

TTrf2TrfTransformation* TTrf2TrfTransformation::clone() const
{// Return a pointer to a clone of this reference frame
	TTrf2TrfTransformation* result = new TTrf2TrfTransformation();
	result->setSourceFrame(this->getSourceFrame());
	result->setDestinationFrame(this->getDestinationFrame());
	result->setTransform(this->getTransform()->clone());
	return result;
}


TTrf2TrfTransformation* TTrf2TrfTransformation::inverse() const
{// Return a pointer to the inverse of this transformtion

	TTrf2TrfTransformation* inver = this->clone();
	inver->invert();
	return inver;
}


void  TTrf2TrfTransformation::invert()
{
	TTerrestrialReferenceFrame* tmp = getSourceFrame();
	this->setSourceFrame(getDestinationFrame());
	this->setDestinationFrame(tmp);
	this->getTransform()->invert();
	return;
}



bool  TTrf2TrfTransformation::transform(TPositionVector& pv) const
{// transform a position vector
	bool result = false;

	if (isInitialised())
		result = fTransform->transform(pv);

	return result;
}


bool  TTrf2TrfTransformation::transform(TFreeVector& fv) const
{// transform a free vector
	bool result = false;

	if (isInitialised())
		result = fTransform->transform(fv);

	return result;
}


bool  TTrf2TrfTransformation::transform(TRotationMatrix& rmx) const
{// transform a Rotation Matrix
	bool result = false;

	if (isInitialised())
		result = fTransform->transform(rmx);

	return result;
}


void TTrf2TrfTransformation::setTransform(THelmertTransformation* helmert)
{// set the transformation
	if (fTransform != 0)
		delete fTransform;

	fTransform = helmert;
}


void TTrf2TrfTransformation::setTransform(const TScaleFactor& scale, const TRotation& rot, const TTranslation& transl)
{
	if (fTransform != 0)
		delete fTransform;

	fTransform = new THelmertTransformation(scale, rot, transl);
	return;
}




//////////////////////////////////////////////////////////////////////
//END
//////////////////////////////////////////////////////////////////////
