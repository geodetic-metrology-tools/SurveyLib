//  TReferenceFrameNetwork.h
//
/** A Reference Frame Network providing access to a set of reference frames
    transformations between them. 
  

    Patterns:  
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_REFERENCE_FRAME_NETWORK
#define SU_REFERENCE_FRAME_NETWORK


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include  <string>
#include  <map>
using namespace std;
//
class  TVTransformation;
class  TVReferenceFrame;
#include  "TRefFrameWrapper.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TReferenceFrameNetwork //: public TObject  
{
public:
	typedef map< string, TRefFrameWrapper, less<string> > RefFrameSet;
	typedef RefFrameSet::iterator iterator;

	/**@name Constants */
	//@{
		/// To be removed if there are none!!
	//@}


	/**@name Constructors and Destructors */
	//@{
		/// Default Constructor 
		TReferenceFrameNetwork();

		/// Destructor
		virtual  ~TReferenceFrameNetwork();
	//@}

		
	/**@name Member Functions */
	//@{
		/// Add a reference frame to the network
		TVReferenceFrame*  insert( TVReferenceFrame* );

		/// Add a transformation between two reference frames to the network
		void  insert( TVTransformation*, TVReferenceFrame*, TVReferenceFrame* );

		/// Returns a pointer to the Reference frame whose name is given
		TVReferenceFrame*  find( const string& ) const;

		/// Get the transformation between two reference frames
		TVTransformation*  getTransformation( TVReferenceFrame* from, TVReferenceFrame* to ) const;
		
		/// Return an Iterator to the beginning of the set of reference frames
		iterator  begin() const;

		/// Return an Iterator to the end of the set of reference frames
		iterator  end() const;


		/*
		/// Inserts a new Local Geodetic Reference Frame into the network
		void  insertLG( TReferenceFrameServer::ERefFrame, const TSpatialPoint& );

		/// Inserts a new Modified Local Geodetic Reference Frame into the network
		void  insertMLG( TReferenceFrameServer::ERefFrame, const TSpatialPoint& );

		/// Inserts a new Local Astronomical Reference Frame into the network
		void  insertLA( TReferenceFrameServer::ERefFrame, TReferenceDatumServer::EGeoid, const TSpatialPoint& );

		/// Inserts a new Modified Local Astronomical Reference Frame into the network
		void  insertMLA( TReferenceFrameServer::ERefFrame, TReferenceDatumServer::EGeoid, const TSpatialPoint& );
		*/
		
		/// Returns the transformation between two given Reference Frames

	//@}


protected:




private:
	// Private Member Functions
	// Copy Constructor 
	TReferenceFrameNetwork(const  TReferenceFrameNetwork&);

	// Copy Assignment Operator 
	TReferenceFrameNetwork& operator=( const TReferenceFrameNetwork& );

	// Add a reference frame to the network
	iterator  insertWrapper( TVReferenceFrame* );


private:
	 
	RefFrameSet  fNetwork;

	//ClassDef(TReferenceFrameNetwork, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_REFERENCE_FRAME_NETWORK
