//  TReferenceFrameNetwork.cpp
//
/** A Reference Frame Network providing access to the reference frames
    in the network and the transformation between them. 
  
    Patterns:
	A singleton to ensure only one Network exists.
  
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
#include  "TVTransformation.h"
#include  "TTransformWrapper.h"
#include  "TVReferenceFrame.h"
#include  "TRefFrameProxy.h"
#include  "TReferenceFrameNetwork.h"
////////////////////////////////////////////////////////////////


//ClassImp(TReferenceFrameNetwork)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TReferenceFrameNetwork::TReferenceFrameNetwork()
{	// default constructor
}

// **Deliberately not implemented**
//TReferenceFrameNetwork::TReferenceFrameNetwork( const  TReferenceFrameNetwork& original )
//{	// copy constructor
//}


TReferenceFrameNetwork::~TReferenceFrameNetwork()
{
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////


// **Deliberately not implemented**
//TReferenceFrameNetwork&  TReferenceFrameNetwork::operator=(const TReferenceFrameNetwork& right)
//{	// Copy Assignment operator
//
//	if (this != &right)
//	{
//	}
//	return *this;
//}


// Add a reference frame to the network
TVReferenceFrame*  TReferenceFrameNetwork::insert( TVReferenceFrame* rf )
{
	// insert a wrapped reference frame into the set
	// and return a pointer to the stored copy of the reference frame
	return  (*insertWrapper(rf)).second.getFrame();
}


// Add a reference frame to the network
TReferenceFrameNetwork::iterator  TReferenceFrameNetwork::insertWrapper( TVReferenceFrame* rf )
{
	string name = rf->getName();
	TRefFrameWrapper  refFrame( rf );

	return  ( fNetwork.insert( RefFrameSet::value_type(name, refFrame) ) ).first;
}


// Add a transformation between two reference frames to the network
void  TReferenceFrameNetwork::insert( TVTransformation* transformer, TVReferenceFrame* from, TVReferenceFrame* to )
{
	// insert the two reference frames and get pointers to the stored copy
	TVReferenceFrame*  source = (*insertWrapper(from)).second.getFrame();
	TVReferenceFrame*  destination = (*insertWrapper(to)).second.getFrame();

	// add the reference frames to the transformation
	transformer->setSourceFrame( source );
	transformer->setDestinationFrame( destination );

	// add the transformations into the appropriate reference frame
	source->insert( transformer );
	destination->insert( transformer->inverse() );

	return;
}


// Find a given reference frame 
TVReferenceFrame*  TReferenceFrameNetwork::find( const string& key )  const
{
	// search the network for the idetified element
	iterator  element = fNetwork.find( key );
	
	// if the element is not found return a null pointer
	// otherwise return a pointer to the encapsulated reference frame
	if( element == fNetwork.end() )
		return 0;
	else 
		return (*element).second.getFrame();
}

/*
// Get the transformation between two reference frames
TVTransformation*  getTransformation( TVReferenceFrame* from, TVReferenceFrame* to ) const
{
	// create a set of proxies for the reference frames



	return;
}
*/

// Return an iterator to the start of the set of reference frames
TReferenceFrameNetwork::iterator  TReferenceFrameNetwork::begin()  const
{
	return fNetwork.begin();
}


// Return an iterator to the end of the set of reference frames
TReferenceFrameNetwork::iterator  TReferenceFrameNetwork::end()  const
{
	return fNetwork.end();
}


//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////

