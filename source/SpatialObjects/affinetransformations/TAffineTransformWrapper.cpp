//  TAffineTransformWrapper.cpp
//
/** A Wrapper around a spatial transformation.
    The wrapper enables a pointer to a transformation to be stored
	in an STL container, and to add a pointer to each of the two 
	reference frames that are linked by the transformation.

  
    Patterns:
    Wrapper around TVAffineTransformation
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
//#include  "TVReferenceFrame.h"
#include  "TAAffineTransformation.h"
#include  "TAffineTransformWrapper.h"
////////////////////////////////////////////////////////////////


//ClassImp(TAffineTransformWrapper)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*TAffineTransformWrapper::TAffineTransformWrapper( TVAffineTransformation*  transformer, 
										  TRefFrameNodeProxy&  from, 
										  TRefFrameNodeProxy&  to )
	: fTransformer( transformer ), fromRefFrame( from ), toRefFrame( to )
{	// constructor taking a pointer to a transformation and a proxy for 
	// the two reference frames linked by the transformation
}*/


TAffineTransformWrapper::TAffineTransformWrapper() : fTransformer (0)
{
}


TAffineTransformWrapper::TAffineTransformWrapper( const TAAffineTransformation*  transformer )
{	// constructor taking a pointer to a transformation 
	fTransformer =0;
	if(transformer != 0)
	{
		fTransformer = transformer->clone();
	}
}


TAffineTransformWrapper::TAffineTransformWrapper( const  TAffineTransformWrapper& original )
{	// copy constructor
	fTransformer =0;
	// deep copy of the transformation
	// if the transformation is not a null pointer get a clone
	// else set this transformation pointer to 0
	if(fTransformer != original.getTransformation())
	{
		fTransformer = original.getTransformation()->clone();
	}
}


TAffineTransformWrapper::~TAffineTransformWrapper()
{   // destructor

	if(fTransformer != 0)
	{
		delete fTransformer;
		fTransformer=0;
	}
}


//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////


TAffineTransformWrapper&  TAffineTransformWrapper::operator=(const TAffineTransformWrapper& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		// deep copy of the transformation
		if(fTransformer != 0)
		{
			delete fTransformer;
			fTransformer = 0;
		}
		
		if(right.getTransformation() != 0)
		{
			fTransformer = ( right.getTransformation() )->clone();
		}
	}
	return *this;
}


bool  TAffineTransformWrapper::operator==(const TAffineTransformWrapper& right) const
{	// Equivalence Operator
	if(this->getTransformation() == right.getTransformation())
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool  TAffineTransformWrapper::operator<(const TAffineTransformWrapper& right) const
{	// Less Than Operator
	
		return true;
}


TAAffineTransformation*  TAffineTransformWrapper::getTransformation() const
{	// get a pointer to the transformation

	return fTransformer;
}



//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////

