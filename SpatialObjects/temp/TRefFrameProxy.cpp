//  TRefFrameProxy.cpp
//
/** A Proxy for a Reference Frame. 
    Not the owner of the reference frame.

  
    Patterns:
    Wrapper around TReferenceFrame.
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
//#include  "TReferenceFrameNode.h"
#include  "TRefFrameProxy.h"
////////////////////////////////////////////////////////////////


//ClassImp(TRefFrameProxy)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TRefFrameProxy::TRefFrameProxy( TVReferenceFrame* frame )
	:  fFrame( frame )
{	// Constructor taking a pointer to a  reference frame
}


TRefFrameProxy::TRefFrameProxy( const  TRefFrameProxy& original )
{	// copy constructor

	// shallow copy of the reference frame
	fFrame = original.getFrame();
}


TRefFrameProxy::~TRefFrameProxy()
{
	delete fFrame;
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////


string  TRefFrameProxy::getName() const
{	// get the name of the reference frame

	// the proxy has the same name as the reference frame itself
	return fFrame->getName();
}


TRefFrameProxy&  TRefFrameProxy::operator=(const TRefFrameProxy& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		// shallow copy of the reference frame
		fFrame = right.getFrame();
	}
	return *this;
}


bool  TRefFrameProxy::operator==(const TRefFrameProxy& right) const
{	// Equivalence Operator

	// two proxies are equivalent if their reference frames have the same name
	if ( getName() == right.getName() )
		return true;
	else
		return false;
}


bool  TRefFrameProxy::operator<(const TRefFrameProxy& right) const
{	// Less Than Operator
	
	// perform the comparison of proxies using the names of the reference frames
	if ( getName() < right.getName() )
		return true;
	else
		return false;
}


TVReferenceFrame*  TRefFrameProxy::getFrame() const
{	// get a pointer to the reference frame

	return fFrame;
}


// Return an Iterator to the beginning of the set of Transformations
TVReferenceFrame::iterator  TRefFrameProxy::begin() 
{	
	return  fFrame->begin();
}


// Return an Iterator to the end of the set of Transformations
TVReferenceFrame::iterator  TRefFrameProxy::end() 
{	
	return  fFrame->end();
}



//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////

