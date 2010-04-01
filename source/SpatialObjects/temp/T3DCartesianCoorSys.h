// T3DCartesianCoorSys.h
//
// Concrete class of a TCoordinateSystem.
// Used by a TReferenceFrame to identify valid coordinate systems
// for a given reference frame, and thereby valid coordinates for a 
// spatial position.
//
// 
// Patterns:
// This is a Singleton.
//
// Copyright 1999,2000, Mark Jones, EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////

#ifndef SU_3D_CARTESIAN_SYSTEM
#define SU_3D_CARTESIAN_SYSTEM

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
//using namespace std;
//
class  TSpatialPosition;
#include  "TCoordinateSystem.h"
//
// typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class T3DCartesianCoorSys : public TCoordinateSystem //: public TObject  
{
public:
	//constants

	//member functions
	static	T3DCartesianCoorSys *instance();

protected:
	// constructors and destructors
	T3DCartesianCoorSys();
	virtual ~T3DCartesianCoorSys();

private:
	// member attributes
	static T3DCartesianCoorSys	*fCoorSys;

	//ClassDef(T3DCartesianCoorSys, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////


#endif // SU_3D_CARTESIAN_SYSTEM


