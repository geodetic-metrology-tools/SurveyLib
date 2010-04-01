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


////////////////////////////////////////////////////////////////
// Forward declarations
//
//#include  <##classname##>
//using namespace std;
//


class  TAAffineTransformation;
// typedefs
//
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! Wrapper class
class  TAffineTransformWrapper //: public TObject  
{
public:
	/**@name Constructors and Destructors */
	//@{
		/// default constructeur
		TAffineTransformWrapper();

		/// Constructor taking a pointer to a transformation
		TAffineTransformWrapper( const TAAffineTransformation* transformer);

		/// Copy Constructor 
		TAffineTransformWrapper( const TAffineTransformWrapper& );

		/// Destructor
		virtual  ~TAffineTransformWrapper();
	//@}


	/**@name Member Functions */
	//@{
		/// Copy Assignment Operator 
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

	TAAffineTransformation*  fTransformer;	/*!< affine transformation */

	//ClassDef(TAffineTransformWrapper, 1)
};

/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_TRANSFORMATION_WRAPPER
