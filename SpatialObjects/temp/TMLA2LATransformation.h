//  TMLA2LATransformation.h
//
/** The transformation from a modified local astronomical reference frame to a 
    local astronomical reference frame.
	
	The modified local astronomical system is a local astronomical system that 
	is subject to a rotation around the z-axis (local vertical) 
	and a translation of the origin.

    The orientation vector, and the false origin of the modified local astronomical 
	system define the transformation.


    Patterns:
  
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_MLA_2_LA_TRANSFORMATION
#define SU_MLA_2_LA_TRANSFORMATION


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
#include  "TARefFrameTransformation.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TMLA2LATransformation : public TARefFrameTransformation //: public TObject  
{
public:
	/**@name Constructors and Destructors */
	//@{
		/// Default Constructor 
		TMLA2LATransformation();

		/// Constructor taking pointers to the source and destination reference frames
		TMLA2LATransformation( TVReferenceFrame* from, TVReferenceFrame* to );

		/// Copy Constructor 
		TMLA2LATransformation(const  TMLA2LATransformation&);

		/// Destructor
		virtual  ~TMLA2LATransformation();
	//@}


	/**@name Member Functions */
	//@{
		/// Copy Assignment Operator 
		TMLA2LATransformation& operator=( const TMLA2LATransformation& );

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

	THelmertTransformation*  fTransform;

	//ClassDef(TMLA2LATransformation, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_MLA_2_LA_TRANSFORMATION
