// TSpatialOrientation.cpp
//
/** Class used for a spatial orientation for RF or stations */
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
#include  "TAngle.h"
//#include  "TRotationMatrix.h"
#include  "TSpatialOrientation.h"
////////////////////////////////////////////////////////////////

//ClassImp(TSpatialOrientation)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TSpatialOrientation::TSpatialOrientation(TEuclideanRefFrame* frame)
{	// default constructor
	setReferenceFrame(frame);
}


/*TSpatialOrientation::TSpatialOrientation(double om, double p, double k)
{//Constructor takink the radians value of the angles in the order omega-phi-kappa
	fXAxisRotation.setRadiansValue(om);//omega
	fYAxisRotation.setRadiansValue(p);//phi
	fZAxisRotation.setRadiansValue(k);//kappa
}
*/

TSpatialOrientation::TSpatialOrientation(TAngle& om, TAngle& p, TAngle& k, TEuclideanRefFrame* frame)
{//Constructor takink the angles in the order omega-phi-kappa
	setXAxisRotation(om);//omega
	setYAxisRotation(p);//phi
	setZAxisRotation(k);//kappa
	setReferenceFrame(frame);
}


TSpatialOrientation::TSpatialOrientation( const  TSpatialOrientation& original )
{	// copy constructor
	fXAxisRotation = original.getXAxisRotation();//omega
	fYAxisRotation = original.getYAxisRotation();//phi
	fZAxisRotation = original.getZAxisRotation();//kappa
	fFrameOfReference = original.getReferenceFrame();
}


TSpatialOrientation::~TSpatialOrientation()
{
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////


TSpatialOrientation&  TSpatialOrientation::operator=(const TSpatialOrientation& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		fXAxisRotation = right.getXAxisRotation();//omega
		fYAxisRotation = right.getYAxisRotation();//phi
		fZAxisRotation = right.getZAxisRotation();//kappa
		fFrameOfReference = right.getReferenceFrame();
	}
	return *this;
}


void TSpatialOrientation::setMatrix(const TRotationMatrix& rm)
{
	fRotationMatrix = rm;
	return;
}


TRotationMatrix TSpatialOrientation::getMatrix()
{ // Return the TRotationMatrix (Rzyx) associated
	return fRotationMatrix;
}

//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////
void TSpatialOrientation::setReferenceFrame(TEuclideanRefFrame* trf)
{
	fFrameOfReference = trf; return;
}


void TSpatialOrientation::setAllRotations(TAngle &om, TAngle &p, TAngle &k)
{
	fXAxisRotation = om;
	fYAxisRotation = p;
	fZAxisRotation = k;
}


void TSpatialOrientation::setXAxisRotation(TAngle &om)
{
	fXAxisRotation = om;
}


void TSpatialOrientation::setYAxisRotation(TAngle &p)
{
	fYAxisRotation = p;
}


void TSpatialOrientation::setZAxisRotation(TAngle &k)
{
	fZAxisRotation = k;
}


TAngle TSpatialOrientation::bearing()
{/// return the bearing
	double b = - this->getZAxisRotation().getRadiansValue();
	TAngle bearing(b);
	return bearing;
}


void TSpatialOrientation::fillRotationMatrix()
{
	fRotationMatrix(0,0) = fZAxisRotation.cosine()*fYAxisRotation.cosine();
	fRotationMatrix(0,1) = fZAxisRotation.sine()*fXAxisRotation.cosine()+fZAxisRotation.cosine()*fYAxisRotation.sine()*fXAxisRotation.sine();
	fRotationMatrix(0,2) = fZAxisRotation.sine()*fXAxisRotation.sine()-fZAxisRotation.cosine()*fYAxisRotation.sine()*fXAxisRotation.cosine();
	fRotationMatrix(1,0) = (-fZAxisRotation.sine()*fYAxisRotation.cosine());
	fRotationMatrix(1,1) = fZAxisRotation.cosine()*fXAxisRotation.cosine()-fZAxisRotation.sine()*fYAxisRotation.sine()*fXAxisRotation.sine();
	fRotationMatrix(1,2) = fZAxisRotation.cosine()*fXAxisRotation.sine()+fZAxisRotation.sine()*fYAxisRotation.sine()*fXAxisRotation.cosine();
	fRotationMatrix(2,0) = fYAxisRotation.sine();
	fRotationMatrix(2,1) = fYAxisRotation.cosine()*fXAxisRotation.sine();
	fRotationMatrix(2,2) = fYAxisRotation.cosine()*fXAxisRotation.cosine();
}


