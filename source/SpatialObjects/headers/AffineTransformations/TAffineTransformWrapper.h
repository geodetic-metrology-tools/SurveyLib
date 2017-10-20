//  TAffineTransformWrapper.h
/*
© Copyright CERN 2000-2017. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
/** A Wrapper around a spatial transformation.
    The wrapper enables a pointer to a transformation to be stored
	in an STL container, and to add a pointer to each of the two 
	reference frames that are linked by the transformation.

  
    Patterns:
    Wrapper around TVAffineTransformation
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
