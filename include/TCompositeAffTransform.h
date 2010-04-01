// TCompositeAffTransform.h
//
/** Class for transformations composed of multiple single transformations
Wrapper of those transformations are kept in a list*/
//
// Patterns:
// this class is close to the pattern Composite
// 
// Copyright 2000 CERN EST/SU. All rights reserved.
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

class  THelmertTransformation;
#include  "TAffineTransformWrapper.h"
#include  "TAAffineTransformation.h"
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
	typedef CompositeTransformationSet::const_iterator CompositeIterator;

	/**@name Constructors and Destructors */
	//@{
		/// Default Constructor 
		TCompositeAffTransform();

		/// Copy Constructor 
		TCompositeAffTransform( const TCompositeAffTransform&);

		//! Constructor taking a TAffineTransformWrapper
		TCompositeAffTransform( const TAffineTransformWrapper );

		/// Destructor
		virtual  ~TCompositeAffTransform();
	//@}


	/**@name Member Functions */
	//@{
		/// Copy Assignment Operator 
		TCompositeAffTransform& operator=( const TCompositeAffTransform& );

		//! Multiplication by a TAAffineTransformation
		TCompositeAffTransform operator*( const TAAffineTransformation& );

	
		// Return a pointer to a clone of this transformation
		TAAffineTransformation*  clone() const;

		/// iterator begin
		CompositeIterator		getCompositeBeginIterator() const {return fComposite.begin();}
		
		/// iterator end
		CompositeIterator		getCompositeEndIterator() const {	return fComposite.end();}
		
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

		/// return the composite set
		CompositeTransformationSet getComposite() const;

		void	add(const TAAffineTransformation& trans) ;


	//@}
protected:
		
private:
	 	// Member Attributes
		
		CompositeTransformationSet		fComposite; /*!< composite transformation */

		// Private functions
		
		

	//ClassDef(TCompositeAffTransform, 1)
};
/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////

inline TCompositeAffTransform::CompositeTransformationSet TCompositeAffTransform::getComposite() const {return fComposite;}


#endif // SU_COMPOSITE_AFFINE_TRANSFO
