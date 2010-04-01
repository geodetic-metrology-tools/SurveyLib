//  THelmertRefFrameTransform.h
//
/** A Helmert transformation between two reference frames.
    
	The two reference frames should be Euclidean reference frames,
	and the parameters of the transformation have to be defined 
	explicitly.

  
    Patterns:
    A WRAPPER around a THelmertTransformation
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_HELMERT_REF_FRAME_TRANSFORMATION
#define SU_HELMERT_REF_FRAME_TRANSFORMATION


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
//#include  <##classname##>
//using namespace std;
//
class  THelmertTransformation;
class  TEnlargement;
class  TRotation;
class  TTranslation;
class  TCompositeAffTransform;
#include  "TARefFrameTransformation.h"
#include  "TSpatialPosition.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////

/*!\ingroup spatialobjects
	@{*/

//! A Helmert transformation between two reference frames
class  THelmertRefFrameTransform : public TARefFrameTransformation //: public TObject  
{
public:
	/**@name Constants */
	//@{
		/// To be removed if there are none!!
	//@}


	/**@name Constructors and Destructors */
	//@{
		/// Default Constructor 
		THelmertRefFrameTransform();

		/// Constructor taking pointers to the source and destination reference frames
		THelmertRefFrameTransform( TAReferenceFrame* from, TAReferenceFrame* to, THelmertTransformation* );

		/// Constructor taking parameters of a THelmertTransformation
		THelmertRefFrameTransform( TAReferenceFrame* from, TAReferenceFrame* to, const TEnlargement&, const TRotation&, const TTranslation&);

		/// Copy Constructor 
		THelmertRefFrameTransform(const  THelmertRefFrameTransform&);

		/// Destructor
		virtual  ~THelmertRefFrameTransform();
	//@}


	/**@name Member Functions */
	//@{
		/// Copy Assignment Operator 
		THelmertRefFrameTransform&			operator=( const THelmertRefFrameTransform& );

		/// Return a pointer to a clone of this reference frame
		virtual TARefFrameTransformation*	clone() const;

		/// Return a pointer to the inverse of this transformtion
		virtual TARefFrameTransformation*	inverse() const;

		/// Return the LG source frame
		virtual TAReferenceFrame*			getSourceFrame() const { return fFrom; }

		/// Return the LA destination frame
		virtual TAReferenceFrame*			getDestinationFrame() const { return fTo; }

		/// Return the helmert transformation
		virtual TCompositeAffTransform*		getTransform() const { return fTransform; }

		/// Set the LG source frame
		virtual void						setSourceFrame( TAReferenceFrame* from) { fFrom = from; return; }

		/// Set the LA destination frame
		virtual void						setDestinationFrame( TAReferenceFrame* to) { fTo = to; return; }

		/// Set the Helmert transformation
		virtual void						setTransform( THelmertTransformation* helmert);

		/// Set the helmert transformation by using a composite affine transformation
		virtual void						setTransform( TCompositeAffTransform* composite );// { fTransform = composite; return; }

		/// transform a position vector
		virtual  bool						transform( TPositionVector& pv ) const;

		/// transform a free vector
		virtual  bool						transform( TFreeVector& fv ) const;

		/// transform a Rotation Matrix
		virtual  bool						transform( TRotationMatrix& rmx ) const;

		bool								isInitialised() const { return (fFrom != 0 && fTo!=0); }
	//@}


private:

	TCompositeAffTransform*		fTransform;
	TAReferenceFrame*			fFrom;
	TAReferenceFrame*			fTo;


	//ClassDef(THelmertRefFrameTransform, 1)
};
/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_HELMERT_REF_FRAME_TRANSFORMATION
