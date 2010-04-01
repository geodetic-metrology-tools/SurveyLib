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
#pragma warning(disable:4786)

#endif // _MSC_VER >= 1000

#include  "TConstPtrWrapper.h"
#include  "TAAffineTransformation.h"


//! Wrapper class
class  TAffineTransformWrapper : public TConstPtrWrapper<TAAffineTransformation>
{
public:
		/// default constructeur
		TAffineTransformWrapper();

		/// Constructor taking a pointer to a transformation
		TAffineTransformWrapper( const TAAffineTransformation* transformer );

		/// Copy Constructor 
		TAffineTransformWrapper( TAffineTransformWrapper & );

		/// Copy Constructor 
		TAffineTransformWrapper( const TAffineTransformWrapper & );

		/// Destructor
		virtual  ~TAffineTransformWrapper();


		const TAAffineTransformation*  getTransformation()  const {this->getPtr();}

		//TAAffineTransformation*  getTransformation()  {this->getPtr();}

private:
		//!Copy assignment operator
		TAffineTransformWrapper& operator=( TAffineTransformWrapper & right );

};

//Default constructor
//template <class T>
TAffineTransformWrapper::TAffineTransformWrapper() 
:TConstPtrWrapper<TAAffineTransformation>()
{}

//Constructor taking a pointer to the template object
//template <class T>
TAffineTransformWrapper::TAffineTransformWrapper( const TAAffineTransformation * transformer )
:TConstPtrWrapper<TAAffineTransformation>(transformer)
{ 
}


//Copy constructor
//template <class T>
TAffineTransformWrapper::TAffineTransformWrapper( TAffineTransformWrapper & original )
:TConstPtrWrapper<TAAffineTransformation>(original)
{
}


//Copy constructor
//template <class T>
TAffineTransformWrapper::TAffineTransformWrapper( const TAffineTransformWrapper & original )
:TConstPtrWrapper<TAAffineTransformation>( original.getPtr() )
{
}


//Destructor
//template <class T>
TAffineTransformWrapper::~TAffineTransformWrapper()
{  
}

////////////////////////////////////////////////////////////////
// Forward declarations
//
//#include  <##classname##>
//using namespace std;
//


//mclass  TAAffineTransformation;
// typedefs
//
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! Wrapper class
//mclass  TAffineTransformWrapper //: public TObject  
//m{
//mpublic:
	/**@name Constructors and Destructors */
	//@{
/*		/// default constructeur
		TAffineTransformWrapper();

		/// Constructor taking a pointer to a transformation
		TAffineTransformWrapper( const TAAffineTransformation* transformer);

		/// Copy Constructor 
		TAffineTransformWrapper( const TAffineTransformWrapper& );

		/// Destructor
		virtual  ~TAffineTransformWrapper();
	//@}
*/

	/**@name Member Functions */
	//@{
/*		/// Copy Assignment Operator 
		TAffineTransformWrapper& operator=( const TAffineTransformWrapper& );

		/// Equivalence Operator
		bool operator==( const TAffineTransformWrapper& ) const;

		/// Less Than Comparison Operator
		bool operator<( const TAffineTransformWrapper& ) const;

		/// Returns the transformation.
		TAAffineTransformation*  getTransformation()  const;

	//@}


protected:


private:


private:

	TAAffineTransformation*  fTransformer;*/	/*!< affine transformation */

	//ClassDef(TAffineTransformWrapper, 1)
//m};

/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_TRANSFORMATION_WRAPPER
