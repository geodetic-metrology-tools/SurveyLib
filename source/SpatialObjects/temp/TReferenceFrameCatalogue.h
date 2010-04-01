// TReferenceFrameCatalogue.h
//
/** A catalogue of unique reference frames which is assembled
    at run time.

   
    Patterns:
    A facade to a set of Reference Frames.
    
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_REF_FRAME_CATALOGUE
#define SU_REF_FRAME_CATALOGUE


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
//#include  <**classname**>
//using namespace std;
//
//class  **classname**;
//#include  "**classname**.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TReferenceFrameCatalogue //: public TObject  
{

public:
	typedef set<TVReferenceFrame> refFrameSet;
	typedef set<TVReferenceFrame>::iterator refFrameIterator;


	/**@name Constructors and Destructors */
	//@{
		/// Default Constructor 
		TReferenceFrameCatalogue();

		/// Destructor
		virtual  ~TReferenceFrameCatalogue();
	//@}


	/**@name Member Functions */
	//@{
		/// Instance method to obtain a pointer to the Factory
		static	TReferenceFrameCatalogue*  instance();
		
		/// add a reference frame to the catalogue
		refFrameIterator  addFrame( TVReferenceFrame* );

		/// determine the number of reference frames in the catalogue
		int	 numberOfFrames() const;

		/// get an iterator to the first reference frame
		refFrameIterator  getFramesBegin() const;

		/// get an iterator to the last reference frame
		refFrameIterator  getFramesEnd() const;

		/// get an iterator to a specific reference frame
		refFrameIterator  getRefFrame( const string& ) const;

	//@}


protected:


private:
	/// Copy Constructor 
	TReferenceFrameCatalogue(const  TReferenceFrameCatalogue&);

	/// Copy Assignment Operator 
	TReferenceFrameCatalogue& operator=( const TReferenceFrameCatalogue& );
	

private:
	int  fLastFrameNbr;
	refFrameSet  fFrames;
	
	//ClassDef(TReferenceFrameCatalogue, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_REF_FRAME_CATALOGUE
