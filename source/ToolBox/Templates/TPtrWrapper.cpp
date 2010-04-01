//!
//! TPtrWrapper.cpp
//!
//! A templated counter pointer. 
//! A wrapper around the pointed to object that manages a count of it's copies.
//! It is responsible for deleting the object being pointed to, and only does
//! this when the last copy of the wrapper is being deleted. 
//!
//! Only wrap pointers that have memory allocated using new.
//!
//! Don't put the same pointer in a second object also responsible fordeleting 
//! it's children. The TPtrWrapper is responsible for deleting the pointed to object.
//! 
//! Copyright 2002-2010, CERN, SU, M/Jones. All rights reserved.
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


//Default constructor
/*template <class T>
TPtrWrapper<T>::TPtrWrapper() : fPointer(0), fCount(0) 
{ 
}
*/


//Constructor taking a pointer to the template object
template <class T>
TPtrWrapper<T>::TPtrWrapper( T* pointer ) : fPointer( pointer ) 
{ 
	fCount = new int(1);
}


//Copy constructor
template <class T>
TPtrWrapper<T>::TPtrWrapper( TPtrWrapper<T>& source ) : fPointer(0), fCount(0)
{
    fPointer = source.getPtr();
	fCount = source.getCountPtr();
	(*fCount)++;
}


//Destructor
template <class T>
TPtrWrapper<T>::~TPtrWrapper() 
{ 
	deletion(); 
}


//Assignment operator
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


//Manages the changes necessary when a wrapper is deleted
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


