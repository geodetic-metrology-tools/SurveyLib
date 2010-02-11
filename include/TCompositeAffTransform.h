// TCompositeAffTransform.h
//
/** Class for transformations composed of multiple single transformations
Wrappers around those transformations are kept in a list*/
//
// Patterns:
// this class is close to the pattern Composite
// 
// Copyright 2000-10 CERN SU, M.Jones. All rights reserved.
//////////////////////////////////////////////////////////////////////



#ifndef SU_COMPOSITE_AFFINE_TRANSFO
#define SU_COMPOSITE_AFFINE_TRANSFO


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include <list>
using namespace std;

#include  "TAAffineTransformation.h"
#include  "TAffineTransformWrapper.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! Class for transformations composed using wrappers
class  TCompositeAffTransform : public TAAffineTransformation  
{
public:
	//typedefs
	typedef list<TAffineTransformWrapper> CompositeTransformationSet;
	//typedef CompositeTransformationSet::iterator CompositeIterator;
	typedef CompositeTransformationSet::const_iterator ConstCompositeIter;

	/**@name Constructors and Destructors */
	//@{
		/// Default Constructor 
		TCompositeAffTransform();

		/// Copy Constructor 
		TCompositeAffTransform( TCompositeAffTransform & );

		//! Constructor taking a TAAffineTransformation
		explicit TCompositeAffTransform( const TAAffineTransformation & );

		/// Destructor
		virtual  ~TCompositeAffTransform();
	//@}


	/**@name Member Functions */
	//@{
		/// Copy Assignment Operator 
		TCompositeAffTransform & operator=( TCompositeAffTransform & );

		//! add to the composite transformation by applying this transformation to an affine transformation
		TCompositeAffTransform & operator()( const TAAffineTransformation & );
	
		// Return a pointer to a clone of this transformation
		TAAffineTransformation*  clone();

		/// Transform a TPosition Vector
		virtual bool transform( TPositionVector& ) const;

		/// Transform a TFreeVector
		virtual bool transform( TFreeVector & ) const;

		/// Transform a TRotationMatrix
		virtual bool transform( TRotationMatrix& ) const;

		/// Inverse
		TCompositeAffTransform inverse();

		/// Invert = Inverse but replace the transformation
		void invert();

		//! Append a TAAffineTransformation
//		void append( const TAAffineTransformation& );
	
		//! Prepend a TAAffineTransformation
//		void prepend( const TAAffineTransformation& );
	
		/// iterator begin
		//CompositeIterator		getCompositeBeginIterator() {return fComposite.begin();}
		ConstCompositeIter		getCompositeBeginIterator() const {return fComposite.begin();}
		
		/// iterator end
		//CompositeIterator		getCompositeEndIterator() {	return fComposite.end();}
		ConstCompositeIter		getCompositeEndIterator() const {	return fComposite.end();}
		
		/// return the composite set
		//CompositeTransformationSet getComposite() const;

		//void	add(const TAAffineTransformation& trans) ;

	//@}
protected:
		
private:
	 	// Member Attributes
		
		CompositeTransformationSet		fComposite; /*!< composite transformation */

	//ClassDef(TCompositeAffTransform, 1)
};
/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////

//inline TCompositeAffTransform::CompositeTransformationSet TCompositeAffTransform::getComposite() const {return fComposite;}

/*
// prepend a TAAffineTransformation
TCompositeAffTransform &operator+( TAAffineTransformation& left, TCompositeAffTransform &right )
{// prepend another affine transformation to the composition  right = left + right
	
	right.prepend(left);
	return right;	

}*/


#endif // SU_COMPOSITE_AFFINE_TRANSFO
