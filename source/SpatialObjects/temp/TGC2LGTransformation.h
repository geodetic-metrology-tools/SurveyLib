//  TGC2LGTransformation.h
//
/** The transformation from a Geodetic reference frame to a 
    local geodetic reference frame.
	
	The origin of the local geodetic system defines the transformation.


    Patterns:
  
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_GC_2_LG_TRANSFORMATION
#define SU_GC_2_LG_TRANSFORMATION


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
class  TGC2LGTransformation : public TARefFrameTransformation //: public TObject  
{
public:

	/**@name Constructors and Destructors */
	//@{
		/// Default Constructor 
		TGC2LGTransformation();

		/// Constructor taking pointers to the source and destination reference frames
		TGC2LGTransformation( TVReferenceFrame* from, TVReferenceFrame* to );

		/// Copy Constructor 
		TGC2LGTransformation(const  TGC2LGTransformation&);

		/// Destructor
		virtual  ~TGC2LGTransformation();
	//@}


	/**@name Member Functions */
	//@{
		/// Copy Assignment Operator 
		TGC2LGTransformation& operator=( const TGC2LGTransformation& );

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

	//ClassDef(TGC2LGTransformation, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_GC_2_LG_TRANSFORMATION
