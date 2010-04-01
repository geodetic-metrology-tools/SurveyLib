//  TLG2LATransformation.h
//
/** The transformation from a local geodetic reference frame to a 
    local astronomical reference frame.
	
    The deflection of the vertical, and the laplace correction at the
	origin of the reference frames define the transformation.


    Patterns:
  
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_LG_2_LA_TRANSFORMATION
#define SU_LG_2_LA_TRANSFORMATION


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
//#include  <##classname##>
//using namespace std;
//
class  TCompositeAffTransform;
#include  "TARefFrameTransformation.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TLG2LATransformation : public TARefFrameTransformation //: public TObject  
{
public:

	/**@name Constructors and Destructors */
	//@{
		/// Default Constructor 
		TLG2LATransformation();

		/// Constructor taking pointers to the source and destination reference frames
		TLG2LATransformation( TVReferenceFrame* from, TVReferenceFrame* to );

		/// Copy Constructor 
		TLG2LATransformation(const  TLG2LATransformation&);

		/// Destructor
		virtual  ~TLG2LATransformation();
	//@}


	/**@name Member Functions */
	//@{
		/// Copy Assignment Operator 
		TLG2LATransformation& operator=( const TLG2LATransformation& );

		/// Return a pointer to a clone of this reference frame
		virtual TVRefFrameTransformation*  clone() const;

		/// Return a pointer to the inverse of this transformtion
		virtual  TVRefFrameTransformation*  inverse() const;


		/// Return a transformed position vector
		virtual  TPositionVector  transform( const TPositionVector& ) const;

		/// Return a transformed free vector
		virtual  TFreeVector  transform( const TFreeVector& ) const;

		/// Return a transformed Rotation Matrix
		virtual  TRotationMatrix  transform( const TRotationMatrix& ) const;

	//@}


protected:
	/**@name Protected Member Functions */
	//@{
		/// Initialise the transformation using the parameters of the two reference frames
		virtual  void  initialise();

	//@}


private:
	
	TCompositeAffTransform*  fTransform;

	//ClassDef(TLG2LATransformation, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_LG_2_LA_TRANSFORMATION
