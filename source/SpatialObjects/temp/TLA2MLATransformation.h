//  TLA2MLATransformation.h
//
/** The transformation from a local astronomical reference frame to a modified
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



#ifndef SU_LA_2_MLA_TRANSFORMATION
#define SU_LA_2_MLA_TRANSFORMATION


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
class  TLA2MLATransformation : public TARefFrameTransformation //: public TObject  
{
public:

	/**@name Constructors and Destructors */
	//@{
		/// Default Constructor 
		TLA2MLATransformation();

		/// Constructor taking pointers to the source and destination reference frames
		TLA2MLATransformation( TVReferenceFrame* from, TVReferenceFrame* to );

		/// Copy Constructor 
		TLA2MLATransformation(const  TLA2MLATransformation&);

		/// Destructor
		virtual  ~TLA2MLATransformation();
	//@}


	/**@name Member Functions */
	//@{
		/// Copy Assignment Operator 
		TLA2MLATransformation& operator=( const TLA2MLATransformation& );

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

	//ClassDef(TLA2MLATransformation, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_LA_2_MLA_TRANSFORMATION
