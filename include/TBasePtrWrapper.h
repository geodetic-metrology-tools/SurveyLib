//!
//! TBasePtrWrapper
//!
//! A templated wrapper around a pointer to a base class. 
//! The wrapper is not responsible for deleting the object being pointed to. 
//!
//! Makes a shallow copy of the pointer.
//!
//! 
//! Copyright 2002, CERN, EST/SU. All rights reserved.
//!////////////////////////////////////////////////////////////////////




#ifndef SU_BASEPOINTERWRAPPER
#define SU_BASEPOINTERWRAPPER

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

////////////////////////////////////////////////////////////////
// Forward declarations
//
//include files
//using namespace std;
//typedefs
//
//
////////////////////////////////////////////////////////////////


template <class T>
class TBasePtrWrapper 
{
public:
	/*!@name Constructors / Destructor*/
	//@{
	//!Default constructor
    TBasePtrWrapper();
	//!Constructor taking a pointer to the template object
    explicit  TBasePtrWrapper( T* pointer );
	//!Copy constructor
    TBasePtrWrapper( TBasePtrWrapper<T>& source ); 
	//!Destructor
    ~TBasePtrWrapper();
	//@}
	
	//!Copy assignment operator
    TBasePtrWrapper<T>& operator=( TBasePtrWrapper<T>& right );
	
	//!Get the pointer
	const T* getPtr() const { return fPointer; };
	//!Get the pointer
    T* getPtr() { return fPointer; };


private:

    T*	  fPointer;
};


template <class T>
bool operator==( const TBasePtrWrapper<T>& wrapper1, const TBasePtrWrapper<T>& wrapper2 ) 
{
    return *(wrapper1.getPtr())  ==  *(wrapper2.getPtr());
}

template <class T>
bool operator<( const TBasePtrWrapper<T>& wrapper1, const TBasePtrWrapper<T>& wrapper2 ) 
{
    return *( wrapper1.getPtr() )  <  *( wrapper2.getPtr() );
}

//Default constructor
template <class T>
TBasePtrWrapper<T>::TBasePtrWrapper<T>() : fPointer(0)
{ 
}

//Constructor taking a pointer to the template object
template <class T>
TBasePtrWrapper<T>::TBasePtrWrapper<T>( T* pointer ) : fPointer( pointer ) 
{ 
}


//Copy constructor
template <class T>
TBasePtrWrapper<T>::TBasePtrWrapper<T>( TBasePtrWrapper<T>& source ) : fPointer(0)
{
    fPointer = source.getPtr();
}


//Destructor
template <class T>
TBasePtrWrapper<T>::~TBasePtrWrapper<T>() 
{ 
}


//Assignment operator
template <class T>
TBasePtrWrapper<T>& TBasePtrWrapper<T>::operator= ( TBasePtrWrapper<T>& right ) 
{
    if( this != &right )
		fPointer = right.getPtr();

    return *this;
}




#endif  //SU_BASEPOINTERWRAPPER
