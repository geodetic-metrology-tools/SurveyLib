//  TTransformWrapper.h
/*
© Copyright CERN 2000-2017. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
/** A Wrapper around a spatial transformation.
    The wrapper enables a pointer to a transformation to be stored
	in an STL container.

  
    Patterns:
    Wrapper around TVTransformation

*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_TRANSFORMATION_WRAPPER
#define SU_TRANSFORMATION_WRAPPER


#if _MSC_VER >= 1000
#pragma once
#pragma warning (disable:4786)
#endif // _MSC_VER >= 1000




////////////////////////////////////////////////////////////////
// Forward declarations
//
//#include  <##classname##>
//
class  TVGraphRefFrame;
class  TARefFrameTransformation;
// typedefs
//
//
////////////////////////////////////////////////////////////////

/*!\ingroup ShortestPath
	@{*/

//! A Wrapper around a spatial transformation
class  TTransformWrapper //: public TObject  
{
public:
	/**@name Constructors and Destructors */
	//@{

		/// Default constructor
		TTransformWrapper();

		/// Constructor taking a pointer to a transformation
		TTransformWrapper( TARefFrameTransformation* transformer);

		/// Copy Constructor 
		TTransformWrapper( const TTransformWrapper& );

		/// Destructor
		virtual  ~TTransformWrapper();
	//@}


	/**@name Member Functions */
	//@{
		/// Copy Assignment Operator 
		TTransformWrapper& operator=( const TTransformWrapper& );

		/// Returns the transformation.
		TARefFrameTransformation*  getTransformation()  const;

		TARefFrameTransformation*  getCopyOfTransformation() const;

		void setTransformation (TARefFrameTransformation* transform);
	//@}

private:

		TARefFrameTransformation*  fTransformer;

	//ClassDef(TTransformWrapper, 1)
};

/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_TRANSFORMATION_WRAPPER
