// TAReferenceFrame.cpp
//
/** An abstract base class for a reference frame. 
  
    Patterns:
    An Abstract STATE of a Spatial Position
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////
//forward declarations
////////////////////////////////////////////////////////////////
#include	"TCompositeAffTransform.h"

#include	"TGeodeticRefFrame.h"
#include	"TModifiedLocalGeodeticRF.h"
#include	"TModifiedLocalAstronomicalRF.h"

#include    "TVRefFrameTransformation.h"
#include    "TARefFrameTransformation.h"
#include    "THelmertRefFrameTransform.h"

#include	"TAReferenceFrame.h"

#include	"TReferenceEllipsoid.h"

//////////////////////////////////////////////////////////////////////
// Initialisation
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


TAReferenceFrame::TAReferenceFrame( const string& name )
	: fName( name )/*, fRefFrameId(0)*/
{	// default constructor 
	fRefFrameId = TRefSystemFactory::kNotInGraph;
}


//TAReferenceFrame::TAReferenceFrame(const TAReferenceFrame& trf)
//{	// copy constructor 
//}


TAReferenceFrame::~TAReferenceFrame()
{
}


//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////

string  TAReferenceFrame::getName() const
{	//return the name of the reference frame
	
	return fName;
}

////////////////////////////////
// return the reference frame id
////////////////////////////////
TRefSystemFactory::ERefFrame  TAReferenceFrame::getRefFrameId() const
{
	return fRefFrameId;
}

////////////////////////////////////////////////
// return true if the reference frame is in graph
///////////////////////////////////////////////

bool TAReferenceFrame::isInRFFactory() const
{
	return TRefSystemFactory::getRefSystemFactory()->isInRFFactory(this);
}

/////////////////////////////////////////////////////////////
//Default code which return a "null" geodetic reference frame
/////////////////////////////////////////////////////////////

TGeodeticRefFrame* TAReferenceFrame::getGeodeticRF() const 
{ 
	return new TGeodeticRefFrame("NULL"); 
}

/////////////////////////
//Data extraction methods
/////////////////////////

//Access to the position vector of a spatial position 
//using private function of TSpatialPosition
TPositionVector TAReferenceFrame::getPositionVector(const TSpatialPosition* sp) const
{
	return sp->getPositionVector();
}



//Access to the free vector of a spatial vector
//using private function of TSpatialVector
TFreeVector TAReferenceFrame::getVector(const TSpatialVector* sv) const
{
	return sv->getVector();
}


//Access to the rotation matrix of a spatial orientation
//using private function of TSpatialOrientation
TRotationMatrix TAReferenceFrame::getOrientation(const TSpatialOrientation* so) const
{
	return so->getOrientation();
}


//////////////////
//Settings methods
//////////////////
bool TAReferenceFrame::setPositionVector(TSpatialPosition* sp, const TPositionVector& pv)
{//Setting of the position vector for a spatial position
//using private function of TSpatialPosition
	return sp->setPositionVector(pv);
	
}



bool TAReferenceFrame::setVector(TSpatialVector* sv, const TFreeVector& fv)
{//Setting of the free vector for a spatial vector
//using private function of TSpatialVector
	bool result;
	result = sv->setVector(fv);
	return result;
}



bool TAReferenceFrame::setOrientation(TSpatialOrientation* so, const TRotationMatrix& rm)
{//Setting of the rotation matrix for a spatial orientation
//using private function of TSpatialOrientation

	return so->setOrientation(rm);
}



bool TAReferenceFrame::transform(TSpatialPosition *sp, TAReferenceFrame* rf)
{//transforms a spatial position from a rf to another
	TPositionVector position(sp->getCoordinates(sp->getCoordSys()));
	TRefFrameWrapper from, to;

	if ( this->isInGraph() && !(rf->isInGraph()) )
	{//transformation to a MLA not in graph

		//transform to CGRF (LEP or SPS)
		TGeodeticRefFrame* tempGeoRF =rf->getGeodeticRF();//utilise new 
		string geoRFName = tempGeoRF->getEllipsoid()->getName();
	//	if(tempGeoRF != 0) {delete tempGeoRF;}

		if(geoRFName == "SphereSPS")
		{
			to.setFrame(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRFSphere));
		}
		else
		{
			to.setFrame(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF));
		}

		from.setFrame(this);

		if (from.getFrame() != to.getFrame() )
		{
			vector<TARefFrameTransformation*> transfo = TGraph::getGraph()->getTransform(from, to);
		
			if (transfo[0] == 0)
			{return false;}

			// reverse the order of the vector to have transformations as applicated to the point
			reverse(transfo.begin(), transfo.end());
			

			// application of the successive transformations
			vector<TARefFrameTransformation*>::iterator iter = transfo.begin();
			vector<TARefFrameTransformation*>::iterator iterEnd = transfo.end();

			while (iter != iterEnd )
			{
				(*iter)->transform(position);
				iter++;
			}

			sp->changeRefFrameTo(to.getFrame());
			sp->setCoordinates(position);
			
		}

		//CGRF to MLA
		TARefFrameTransformation* temp1 = rf->getRFTransfo2CGRF();//utilise new
		TARefFrameTransformation* temp2 = temp1->inverse();//utilise new
		temp2->transform(position);
		sp->changeRefFrameTo(rf);
		sp->setCoordinates(position);
	//	if(temp1 != 0) {delete temp1;} //temp1 est detruit dans le destructeur de rf
		if(temp2 != 0) {delete temp2;}

	}
	else if( !(this->isInGraph()) && rf->isInGraph() )
	{//transformation from a MLA not in graph

		//MLA to CGRF
		TARefFrameTransformation* temp1 = this->getRFTransfo2CGRF();//utilise new
		temp1->transform(position);
		sp->changeRefFrameTo(this);
		sp->setCoordinates(position);
	//	if(temp1 != 0) {delete temp1;}

		//CGRF to rf
		TGeodeticRefFrame* tempGeoRF =this->getGeodeticRF();//utilise new 
		string geoRFName = tempGeoRF->getEllipsoid()->getName();
	//	if(tempGeoRF != 0) {delete tempGeoRF;}

		if(geoRFName == "SphereSPS")
		{
			from.setFrame(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRFSphere));
		}
		else
		{
			from.setFrame(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF));
		}

		to.setFrame(rf);

		if (from.getFrame() != to.getFrame() )
		{
			vector<TARefFrameTransformation*> transfo = TGraph::getGraph()->getTransform(from, to);
		
			if (transfo[0] == 0)
			{return false;}

			// reverse the order of the vector to have transformations as applicated to the point
			reverse(transfo.begin(), transfo.end());
			

			// application of the successive transformations
			vector<TARefFrameTransformation*>::iterator iter = transfo.begin();
			vector<TARefFrameTransformation*>::iterator iterEnd = transfo.end();

			while (iter != iterEnd )
			{
				(*iter)->transform(position);
				iter++;
			}

			sp->changeRefFrameTo(to.getFrame());
			sp->setCoordinates(position);
			
		}
	}
	else
	{
		from.setFrame(this);
		to.setFrame(rf);

		if (from.getFrame() != to.getFrame() )
		{
			vector<TARefFrameTransformation*> transfo = TGraph::getGraph()->getTransform(from, to);
		
			if (transfo[0] == 0)
			{return false;}

			// reverse the order of the vector to have transformations as applicated to the point
			reverse(transfo.begin(), transfo.end());
			

			// application of the successive transformations
			vector<TARefFrameTransformation*>::iterator iter = transfo.begin();
			vector<TARefFrameTransformation*>::iterator iterEnd = transfo.end();

			while (iter != iterEnd )
			{
				(*iter)->transform(position);
				iter++;
			}

			sp->changeRefFrameTo(to.getFrame());
			sp->setCoordinates(position);
			
		}
	}
	return true;
}



bool TAReferenceFrame::transform( TSpatialVector* sv, TAReferenceFrame* rf ) 
{// transform a vector from a reference frame to another
	TFreeVector freeVector(sv->getElements(sv->getCoordSys()));
	TRefFrameWrapper from, to;

	if ( this->isInGraph() && !(rf->isInGraph()) )
	{//transformation to a MLA not in graph

		//transform to CGRF (LEP or SPS)
		TGeodeticRefFrame* tempGeoRF =rf->getGeodeticRF();//utilise new 
		string geoRFName = tempGeoRF->getEllipsoid()->getName();
	//	if(tempGeoRF != 0) {delete tempGeoRF;}

		if(geoRFName == "SphereSPS")
		{
			to.setFrame(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRFSphere));
		}
		else
		{
			to.setFrame(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF));
		}

		from.setFrame(this);

		if (from.getFrame() != to.getFrame() )
		{
			vector<TARefFrameTransformation*> transfo = TGraph::getGraph()->getTransform(from, to);
		
			if (transfo[0] == 0)
			{return false;}

			// reverse the order of the vector to have transformations as applicated to the point
			reverse(transfo.begin(), transfo.end());
			

			// application of the successive transformations
			vector<TARefFrameTransformation*>::iterator iter = transfo.begin();
			vector<TARefFrameTransformation*>::iterator iterEnd = transfo.end();

			while (iter != iterEnd )
			{
				(*iter)->transform(freeVector);
				iter++;
			}

			sv->changeRefFrameTo(to.getFrame());
			sv->setElements(freeVector);		
		}

		//CGRF to MLA
		TARefFrameTransformation* temp1 = rf->getRFTransfo2CGRF(); //utilise new
		TARefFrameTransformation* temp2 = temp1->inverse(); //utilise new
		temp2->transform(freeVector);
		sv->changeRefFrameTo(rf);
		sv->setElements(freeVector);
	//	if(temp1 != 0) {delete temp1;} //temp1 est detruit dans le destructeur de rf
		if(temp2 != 0) {delete temp2;}

	}
	else if( !(this->isInGraph()) && rf->isInGraph() )
	{//transformation from a MLA not in graph

		//MLA to CGRF
		TARefFrameTransformation* temp1 = this->getRFTransfo2CGRF(); //utilise new
		temp1->transform(freeVector);
		sv->changeRefFrameTo(this);
		sv->setElements(freeVector);
		if(temp1 != 0) {delete temp1;}

		//CGRF to rf
		TGeodeticRefFrame* tempGeoRF =this->getGeodeticRF();//utilise new 
		string geoRFName = tempGeoRF->getEllipsoid()->getName();
	//	if(tempGeoRF != 0) {delete tempGeoRF;}

		if(geoRFName == "SphereSPS")
		{
			from.setFrame(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRFSphere));
		}
		else
		{
			from.setFrame(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF));
		}

		to.setFrame(rf);

		if (from.getFrame() != to.getFrame() )
		{
			vector<TARefFrameTransformation*> transfo = TGraph::getGraph()->getTransform(from, to);
		
			if (transfo[0] == 0)
			{return false;}

			// reverse the order of the vector to have transformations as applicated to the point
			reverse(transfo.begin(), transfo.end());
			

			// application of the successive transformations
			vector<TARefFrameTransformation*>::iterator iter = transfo.begin();
			vector<TARefFrameTransformation*>::iterator iterEnd = transfo.end();

			while (iter != iterEnd )
			{
				(*iter)->transform(freeVector);
				iter++;
			}

			sv->changeRefFrameTo(to.getFrame());
			sv->setElements(freeVector);
			
		}
	}
	else
	{
		from.setFrame(this);
		to.setFrame(rf);

		if (from.getFrame() != to.getFrame() )
		{
			vector<TARefFrameTransformation*> transfo = TGraph::getGraph()->getTransform(from, to);
		
			if (transfo[0] == 0)
			{return false;}

			// reverse the order of the vector to have transformations as applicated to the point
			reverse(transfo.begin(), transfo.end());
			

			// application of the successive transformations
			vector<TARefFrameTransformation*>::iterator iter = transfo.begin();
			vector<TARefFrameTransformation*>::iterator iterEnd = transfo.end();

			while (iter != iterEnd )
			{
				(*iter)->transform(freeVector);
				iter++;
			}

			sv->changeRefFrameTo(to.getFrame());
			sv->setElements(freeVector);		
		}
	}
	return true;
}




TARefFrameTransformation*   TAReferenceFrame::getRFTransfo2CGRF()
{// transformation from this reference frame to CGRF (in case of a reference frame not included in TGraph)
	return new THelmertRefFrameTransform();
}

