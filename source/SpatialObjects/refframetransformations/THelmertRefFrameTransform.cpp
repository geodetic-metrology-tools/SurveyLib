//  THelmertRefFrameTransform.cpp
//
/** A Helmert transformation between two reference frames.
    
	The two reference frames should be Euclidean reference frames,
	and the parameters of the transformation have to be defined 
	explicitly.

  
    Patterns:
  
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
#include  "THelmertTransformation.h"
#include  "TCompositeAffTransform.h"
#include  "THelmertRefFrameTransform.h"
#include  "TAReferenceFrame.h"
////////////////////////////////////////////////////////////////


//ClassImp(THelmertRefFrameTransform)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// CONSTRUCTOR / DESTRUCTOR
//////////////////////////////////////////////////////////////////////
THelmertRefFrameTransform::THelmertRefFrameTransform()
	: fFrom(0), fTo(0), fTransform(0)
{	// default constructor
}


THelmertRefFrameTransform::THelmertRefFrameTransform( TAReferenceFrame* from, 
													  TAReferenceFrame* to, 
													  THelmertTransformation* transform )
	: fFrom(from), fTo(to), fTransform(0)
{	// constructor taking pointers to the source and destination reference frames
	TCompositeAffTransform temp;
	(*transform)*temp;
	fTransform = new TCompositeAffTransform(temp);
}


THelmertRefFrameTransform::THelmertRefFrameTransform( TAReferenceFrame* from, 
													  TAReferenceFrame* to, 
													  const TEnlargement& enlarg, const TRotation& rot, const TTranslation& transl)
	: fFrom(from), fTo(to), fTransform(0)
{
	//TTranslation temp(0,0,0);
	THelmertTransformation helmert(enlarg, rot, transl);
/*	TCompositeAffTransform temp;
	temp.setStatus(helmert.getStatus());
	fTransform = new TCompositeAffTransform(temp*helmert);*/
	setTransform(&helmert);
}



THelmertRefFrameTransform::THelmertRefFrameTransform( const  THelmertRefFrameTransform& original )
{// copy constructor
	fTransform = 0;	//initialise in setTransform

	setSourceFrame( original.getSourceFrame() );
	setDestinationFrame( original.getDestinationFrame() );

	setTransform( original.getTransform() );
}


THelmertRefFrameTransform::~THelmertRefFrameTransform()
{//destructor
	if( 0 != fTransform )
	{
		delete fTransform;
	}
}




//////////////////////////////////////////////////////////////////////
//MEMBER FUNCTIONS
//////////////////////////////////////////////////////////////////////
THelmertRefFrameTransform&  THelmertRefFrameTransform::operator=(const THelmertRefFrameTransform& right)
{	// Copy Assignment operator
	if (this != &right)
	{
		setSourceFrame( right.getSourceFrame() );
		setDestinationFrame( right.getDestinationFrame() );
		setTransform( right.getTransform() );
	}
	return *this;
}


TARefFrameTransformation*  THelmertRefFrameTransform::clone() const
{// Return a pointer to a clone of this reference frame
	return new THelmertRefFrameTransform( *this );
}


TARefFrameTransformation*  THelmertRefFrameTransform::inverse() const
{// Return a pointer to the inverse of this transformtion

	TCompositeAffTransform* inv;
	inv = new TCompositeAffTransform ( *this->getTransform() );
	inv->invert();

	THelmertRefFrameTransform* result = new THelmertRefFrameTransform;
	result->setSourceFrame( getDestinationFrame() );
	result->setDestinationFrame( getSourceFrame() );
	result->setTransform( inv );

	delete inv;

	return result;
}


bool  THelmertRefFrameTransform::transform( TPositionVector& pv ) const
{// transform a position vector
	bool result;
	  
	if( isInitialised() )
		  result = fTransform->transform(pv);

	return result;
}


bool  THelmertRefFrameTransform::transform( TFreeVector& fv ) const
{// transform a free vector
	bool result;
	  
	if( isInitialised() )
		  result = fTransform->transform(fv);

	return result;
}


bool  THelmertRefFrameTransform::transform( TRotationMatrix& rmx ) const
{// transform a Rotation Matrix
	bool result;
	  
	if( isInitialised() )
		  result = fTransform->transform(rmx);

	return result;
}


void THelmertRefFrameTransform::setTransform(THelmertTransformation* helmert)
{// set the transformation
	if (fTransform != 0)
	{
		delete fTransform;
	}
	TAffineTransformWrapper wrapper (helmert);
	fTransform = new TCompositeAffTransform(wrapper);
}


void THelmertRefFrameTransform::setTransform( TCompositeAffTransform* composite )
{ 
	if (fTransform != 0)
	{
		delete fTransform;
	}
	TAffineTransformWrapper wrapper (composite);
	fTransform = new TCompositeAffTransform(wrapper);
	return;
}



//////////////////////////////////////////////////////////////////////
//END
//////////////////////////////////////////////////////////////////////

