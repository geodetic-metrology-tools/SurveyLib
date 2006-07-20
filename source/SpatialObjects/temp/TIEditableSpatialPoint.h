// 
// TIEditableSpatialPoint.h
//
// Purely Abstract Base Class (Interface) for an editable spatial point
// Serves to define the functionality necessary for a spatial point
// to be editable, i.e. for its features to be updateable
//
// Copyright 1999,2000, CERN, EST/SU. All rights reserved.
////////////////////////////////////////////////////////////////

#ifndef SU_I_EDITABLE_SPATIAL_POINT
#define SU_I_EDITABLE_SPATIAL_POINT

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
//using namespace std;
//
// typedefs
//
//
////////////////////////////////////////////////////////////////



// Interface Definition
class	TIEditableSpatialPoint //: public TObject
{

public:	
	virtual  void 	 setPosition( TSpatialPosition * ) = 0;
	virtual  TSpatialPosition  getPosition( const TReferenceFrame & ) const = 0;

	virtual  TSpatialPointName	getName()  const = 0;
	virtual  void  setName( const TSpatialPointName& ) = 0;
	virtual  string  getPtName()  const = 0;
 
	virtual  bool  operator ==( const TSpatialPoint & ) const = 0; //compare equal 

protected:
	virtual  TSpatialPosition  getPosition() const = 0;

	//ClassDef(TVariableSpatialPoint, 1)
};



#endif  //  SU_I_EDITABLE_SPATIAL_POINT
