// 
// TLGCReferenceFrameNetwork.h : Header File
//
// Class for a network of frame of reference. 
// Transform the positions in the different RF. 
//
// Copyright 1999,2000, Jerome Henry, EST/SU. All rights reserved.
/////////////////////////////////////////////////////////////////////////////////

#ifndef SU_LGC_REFERENCE_FRAME_NETWORK
#define SU_LGC_REFERENCE_FRAME_NETWORK

#if _MSC_VER >= 1000
#pragma once
#pragma warning (disable:4786)
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
#include  "TVReferenceFrameNetwork.h"
#include  "TReferenceFrame.h"
#include  "TSpatialPosition.h"
////////////////////////////////////////////////////////////////

// Class Definition
class	TLGCReferenceFrameNetwork : public TVReferenceFrameNetwork
{

public:
	//constants
	
	// constructors and destructors

	TLGCReferenceFrameNetwork();
//	TLGCReferenceFrameNetwork(const TReferenceFrameNetwork&);
	virtual	~TLGCReferenceFrameNetwork();
//	TReferenceFrame& operator=(const TReferenceFrame&);

	// member functions

	TSpatialPosition getPositionInThisRF(const TReferenceFrame& ) const;

private:
	// member attributes
	
	
	//ClassDef(TLGCReferenceFrameNetwork, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////
inline  TSpatialPosition TLGCReferenceFrameNetwork::getPositionInThisRF(const TReferenceFrame& frame)const{TSpatialPosition fPosition(frame); return fPosition;}


#endif // SU_LGC_REFERENCE_FRAME_NETWORK
		
		