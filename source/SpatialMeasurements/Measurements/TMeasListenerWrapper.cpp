/*!  TMeasListenerWrapper
/
/    A Wrapper around a TVMeasurementListener.
/    The wrapper enables a pointer to a measurement listener to be stored
/    in an STL container.
/
/  
/    Patterns:
/    Wrapper around TVMeasurementListener.
/   
/    Copyright 2002 CERN EST/SU. All rights reserved.
/
//////////////////////////////////////////////////////////////////////*/



//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations

#include  "TVMeasurementListener.h"
#include  "TMeasListenerWrapper.h"
////////////////////////////////////////////////////////////////


//ClassImp(TMeasListenerWrapper)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TMeasListenerWrapper::TMeasListenerWrapper()
	:  fListener( 0 )
{	// Default Constructor
}


TMeasListenerWrapper::TMeasListenerWrapper( TVMeasurementListener* listener )
	:  fListener( listener )
{	// Constructor taking a pointer to a  measurement listener
}


TMeasListenerWrapper::TMeasListenerWrapper( const  TMeasListenerWrapper& original )
{	// copy constructor

	// shallow copy of the measurement listener
	fListener = original.getlistener();
}


TMeasListenerWrapper::~TMeasListenerWrapper()
{
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////


TMeasListenerWrapper&  TMeasListenerWrapper::operator=(const TMeasListenerWrapper& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		// shallow copy of the measurement listener
		fListener = right.getlistener();
	}
	return *this;
}


bool  TMeasListenerWrapper::operator==(const TMeasListenerWrapper& right) const
{	// Equivalence Operator

	// two nodes are equivalent if their measurement listeners are the same
	if ( getName() == right.getName() )
		return true;
	else
		return false;
}


bool  TMeasListenerWrapper::operator<(const TMeasListenerWrapper& right) const
{	// Less Than Operator
	
	// perform the comparison of nodes using the measurement listeners
	if ( getName() < right.getName() )
		return true;
	else
		return false;
}


string  TMeasListenerWrapper::getName() const
{	// get the name of the measurement listener

	// the wrapper has the same name as the measurement listener itself
	return fListener->getName();
}


TVMeasurementListener*  TMeasListenerWrapper::getlistener() const
{	// get a pointer to the measurement listener

	return fListener;
}


void TMeasListenerWrapper::setlistener( TVMeasurementListener* listener )
{	//set the pointer to the measurement listener
	fListener = listener;
	return;
}


void TMeasListenerWrapper::setIdentifier(int i)
{
//	fListener->setIdentifier(i);
	return;
}


//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////

