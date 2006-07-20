//  TRefFrameProxy.h
//
/** A Proxy for a Reference Frame. 
    Not the owner of the reference frame.

  
    Patterns:
    Wrapper around TReferenceFrame.
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_REFERENCE_FRAME_PROXY
#define SU_REFERENCE_FRAME_PROXY


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include  <string>
using namespace std;
//
#include  "TVReferenceFrame.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TRefFrameProxy //: public TObject  
{
public:

	/**@name Constructors and Destructors */
	//@{
		/// Constructor taking a pointer to a reference frame
		TRefFrameProxy( TVReferenceFrame* );

		/// Copy Constructor 
		TRefFrameProxy( const TRefFrameProxy& );

		/// Destructor
		virtual  ~TRefFrameProxy();
	//@}


	/**@name Member Functions */
	//@{
		/// Return the name of the reference frame
		string  getName() const;

		/// Copy Assignment Operator 
		TRefFrameProxy& operator=( const TRefFrameProxy& );

		/// Equivalence Operator
		bool operator==( const TRefFrameProxy& right ) const;

		/// Less Than Comparison Operator
		bool operator<( const TRefFrameProxy& right ) const;

		/// Return a pointer to the Reference Frame
		TVReferenceFrame*  getFrame() const;

		/// Return an Iterator to the beginning of the set of Transformations
		TVReferenceFrame::iterator  begin();

		/// Return an Iterator to the end of the set of Transformations
		TVReferenceFrame::iterator  end();

	//@}


protected:


private:

	TVReferenceFrame*  fFrame;
	//ClassDef(TRefFrameProxy, 1)
};



//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_REFERENCE_FRAME_PROXY
