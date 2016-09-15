//  TAffineTransformWrapper.h
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



#ifndef SU_AFFINE_TRANSFORMATION_WRAPPER
#define SU_AFFINE_TRANSFORMATION_WRAPPER

#if _MSC_VER >= 1000
#pragma once
#endif

#include  "TPtrWrapper.h"
#include  "TAAffineTransformation.h"


//! Wrapper class
class  TAffineTransformWrapper : public TPtrWrapper<TAAffineTransformation>
{
public:
		/// default constructeur
		TAffineTransformWrapper();

		/// Constructor taking a pointer to a transformation
		TAffineTransformWrapper( TAAffineTransformation* transformer );

		/// Copy Constructor 
		TAffineTransformWrapper( const TAffineTransformWrapper & );

		/// Destructor
		virtual  ~TAffineTransformWrapper();

		TAAffineTransformation*  getTransformation()  {return this->getPtr();}
		const TAAffineTransformation*  getTransformation() const {return this->getPtr();}

private:
		//!Copy assignment operator
		TAffineTransformWrapper& operator=( TAffineTransformWrapper & right );

};

#endif // SU_TRANSFORMATION_WRAPPER
