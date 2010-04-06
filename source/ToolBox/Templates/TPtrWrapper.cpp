//!
//! TPtrWrapper
//!
//! A templated pointer wrapper. The wrapper becomes the parent of the
//! pointed to object and is responsible for deleting it. 
//!
//! Copyright 2002, CERN, EST/SU. All rights reserved.
//!////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
// Forward declarations
//
//include files
//
//using namespace std;
//
#include  "TPtrWrapper.h"
//typedefs
//
//
////////////////////////////////////////////////////////////////


//!Default constructor
template <class T>
TPtrWrapper<T>::TPtrWrapper<T>() : fPointer(0), fCount(0) 
{ 
}

//!Constructor taking a pointer to the template object
template <class T>
TPtrWrapper<T>::TPtrWrapper<T>( T* pointer ) : fPointer( pointer ) 
{ 
	fCount = new int(1);
}


//!Copy constructor
template <class T>
TPtrWrapper<T>::TPtrWrapper<T>( TPtrWrapper<T>& source ) : fPointer(0), fCount(0)
{
    fPointer = source.getPtr();
	fCount = source.getCountPtr();
	(*fCount)++;
}


//!Destructor
template <class T>
TPtrWrapper<T>::~TPtrWrapper<T>() 
{ 
	deletion(); 
}


template <class T>
TPtrWrapper<T>& TPtrWrapper<T>::operator= ( TPtrWrapper<T>& right ) 
{
    if( this != &right  &&  fPointer != right.getPtr() )
	{
		deletion();
		fPointer = right.getPtr();
		fCount = right.getCountPtr();
		(*fCount)++;
	}

    return *this;
}


template <class T>
void  TPtrWrapper<T>::deletion()
{
	// If the wrapper is pointing to something, and this was the last
	// wrapper around the pointer, delete the pointers
	if( fCount  &&  --(*fCount) == 0 )
	{
		delete fPointer;
		delete fCount;

		fPointer = 0;
		fCount = 0;
	}

	return;
}




