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
#include  "TAffineTransformWrapper.h"
////////////////////////////////////////////////////////////////


//ClassImp(TAffineTransformWrapper)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Default constructor
//template <class T>
TAffineTransformWrapper::TAffineTransformWrapper() 
:TPtrWrapper<TVAffineTransformation>()
{}

//Constructor taking a pointer to the template object
//template <class T>
TAffineTransformWrapper::TAffineTransformWrapper( TVAffineTransformation * transformer )
:TPtrWrapper<TVAffineTransformation>(transformer)
{ 
}


//Copy constructor
//template <class T>
TAffineTransformWrapper::TAffineTransformWrapper( const TAffineTransformWrapper & original )
:TPtrWrapper<TVAffineTransformation>( original )
{
}


//Destructor
//template <class T>
TAffineTransformWrapper::~TAffineTransformWrapper()
{  
}
