// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

// TAReferenceFrame.cpp
//
/** An abstract base class for a reference frame. 
  
    Patterns:
    An Abstract STATE of a Spatial Position
   
*/
//////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////
//forward declarations
////////////////////////////////////////////////////////////////
#include	"TCompositeAffTransform.h"

#include	"TGeodeticRefFrame.h"

#include    <TARefFrameTransformation.h>
#include    <THelmertRefFrameTransform.h>

#include	"TAReferenceFrame.h"

#include    <memory>

//////////////////////////////////////////////////////////////////////
// Initialisation
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TAReferenceFrame::TAReferenceFrame( const std::string& name )
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

std::string  TAReferenceFrame::getName() const
{	//return the name of the reference frame
	
	return fName;
}

////////////////////////////////
// return the reference frame id
////////////////////////////////
TRefSystemFactory::ERefFrame  TAReferenceFrame::getId() const
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
	return TGeodeticRefFrame::instance();
}

TAReferenceFrame* TAReferenceFrame::getGraphAnchorRF() const
{
	return getGeodeticRF();
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
{
	TPositionVector position(sp->getCoordinates(sp->getCoordSys()));
	TRefFrameWrapper from(this);
	TRefFrameWrapper to(rf);
	std::unique_ptr<TARefFrameTransformation> postGraphTrafo;

	if (! this->isInGraph()) {
		// transform to the graph anchor frame manually
		TARefFrameTransformation* toGRF = this->getRFTransfo2CGRF();
		toGRF->transform(position);

		from.setFrame(this->getGraphAnchorRF());
	}

	if (! rf->isInGraph()) {
		// destination system is not in the graph (local system, geoid height frame...)
		// transform from the graph anchor frame manually
		postGraphTrafo.reset(rf->getRFTransfo2CGRF()->inverse());

		to.setFrame(rf->getGraphAnchorRF());
	}

	if (! (from == to)) {
		std::vector<TARefFrameTransformation*> transfo = TGraph::getGraph()->getTransform(from, to);
		
		if (transfo[0] == 0)
		{return false;}

		// application of the successive transformations
		for (std::vector<TARefFrameTransformation*>::iterator iter = transfo.begin();
			 iter != transfo.end(); 
			 iter++)
			(*iter)->transform(position);
	}

	if (postGraphTrafo) {
		// The destination system is not in the graph
		postGraphTrafo->transform(position);
		
	}
	sp->changeRefFrameTo(rf);
	sp->setCoordinates(position);

	return true;
}

// TODO: merge with the function above, same content, only signature differences
// between  TSpatialVector an TSpatialPosition
bool TAReferenceFrame::transform( TSpatialVector* sv, TAReferenceFrame* rf ) 
{
	// transform a vector from a reference frame to another
	TFreeVector freeVector(sv->getElements(sv->getCoordSys()));

	TRefFrameWrapper from(this);
	TRefFrameWrapper to(rf);
	std::unique_ptr<TARefFrameTransformation> postGraphTrafo;

	if (! this->isInGraph()) {
		// transform to the graph anchor frame manually
		TARefFrameTransformation* toGRF = this->getRFTransfo2CGRF();
		toGRF->transform(freeVector);

		from.setFrame(this->getGraphAnchorRF());
	}

	if (! rf->isInGraph()) {
		// destination system is not in the graph (local system, geoid height frame...)
		// transform from the graph anchor frame manually
		postGraphTrafo.reset(rf->getRFTransfo2CGRF()->inverse());

		to.setFrame(rf->getGraphAnchorRF());
	}

	if (! (from == to)) {
		std::vector<TARefFrameTransformation*> transfo = TGraph::getGraph()->getTransform(from, to);
		
		if (transfo[0] == 0)
		{return false;}

		// application of the successive transformations
		for (std::vector<TARefFrameTransformation*>::iterator iter = transfo.begin();
			 iter != transfo.end(); 
			 iter++)
			(*iter)->transform(freeVector);
	}

	if (postGraphTrafo) {
		// The destination system is not in the graph
		postGraphTrafo->transform(freeVector);
	}
	sv->changeRefFrameTo(rf);
	sv->setElements(freeVector);
		
	return true;
}

TARefFrameTransformation* TAReferenceFrame::getRFTransfo2CGRF()
{// transformation from this reference frame to CGRF (in case of a reference frame not included in TGraph)
	static THelmertRefFrameTransform* t = new THelmertRefFrameTransform();
	return t; 
}

