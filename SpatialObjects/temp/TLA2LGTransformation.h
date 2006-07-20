//  TLA2LGTransformation.h
//
/** The transformation from a local astronomical reference frame to a
    local geodetic reference frame.
	
    The deflection of the vertical, and the laplace correction at the
	origin of the reference frames define the transformation.


    Patterns:
  
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_LA_2_LG_TRANSFORMATION
#define SU_LA_2_LG_TRANSFORMATION


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
class  TLA2LGTransformation : public TARefFrameTransformation //: public TObject  
{
public:
	/**@name Constructors and Destructors */
	//@{
		/// Default Constructor 
		TLA2LGTransformation();

		/// Constructor taking pointers to the source and destination reference frames
		TLA2LGTransformation( TVReferenceFrame* from, TVReferenceFrame* to );

		/// Copy Constructor 
		TLA2LGTransformation(const  TLA2LGTransformation&);

		/// Destructor
		virtual  ~TLA2LGTransformation();
	//@}


	/**@name Member Functions */
	//@{
		/// Copy Assignment Operator 
		TLA2LGTransformation& operator=( const TLA2LGTransformation& );

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

	//ClassDef(TLA2LGTransformation, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_LA_2_LG_TRANSFORMATION
