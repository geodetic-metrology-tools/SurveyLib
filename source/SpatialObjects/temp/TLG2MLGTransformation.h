//  TLG2MLGTransformation.h
//
/** The transformation from a local geodetic reference frame to a modified
    local geodetic reference frame.
	
	The modified local geodetic system is a local geodetic system that 
	is subject to a rotation around the z-axis (ellipsoidal normal) 
	and a translation of the origin.

    The orientation vector, and the false origin of the modified local geodetic 
	system define the transformation.


    Patterns:
  
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_LG_2_MLG_TRANSFORMATION
#define SU_LG_2_MLG_TRANSFORMATION


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
//#include  <##classname##>
//using namespace std;
//
//class  ##classname##;
#include  "TARefFrameTransformation.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TLG2MLGTransformation : public TARefFrameTransformation //: public TObject  
{
public:

	/**@name Constructors and Destructors */
	//@{
		/// Default Constructor 
		TLG2MLGTransformation();

		/// Constructor taking pointers to the source and destination reference frames
		TLG2MLGTransformation( TVReferenceFrame* from, TVReferenceFrame* to );

		/// Copy Constructor 
		TLG2MLGTransformation(const  TLG2MLGTransformation&);

		/// Destructor
		virtual  ~TLG2MLGTransformation();
	//@}


	/**@name Member Functions */
	//@{
		/// Copy Assignment Operator 
		TLG2MLGTransformation& operator=( const TLG2MLGTransformation& );

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

	//ClassDef(TLG2MLGTransformation, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_LG_2_MLG_TRANSFORMATION
