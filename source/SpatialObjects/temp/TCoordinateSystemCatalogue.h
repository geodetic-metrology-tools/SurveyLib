// TCoordinateSystemCatalogue.h 
//
// Class(singleton) for a Catalogue of Coordinate Systems.
//
// Used by a TReferenceFrame 
// 
// Patterns: singleton
//
// Copyright 1999,2000, Mark Jones, EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////



#ifndef SU_COORDINATE_SYSTEM_CATALOGUE
#define SU_COORDINATE_SYSTEM_CATALOGUE

#if _MSC_VER >= 1000
#pragma once
#pragma warning (disable:4786)
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include  <string>
using namespace std;
#include <set>
//
class  TCoordinateSystem;
#include  "TCoorSysWrapper.h"
////////////////////////////////////////////////////////////////



//Class definition
class TCoordinateSystemCatalogue //: public TObject  
{
public:
	//member functions
	static  TCoordinateSystemCatalogue* Instance();


	TCoordinateSystem *getCoordSys (TCoordinateSystem::ECoordinateSystem);  

	static  TCoordinateSystemCatalogue*  fCoordSysCatalogue;
protected:
	//constructor & destructor
	TCoordinateSystemCatalogue();
	~TCoordinateSystemCatalogue();

private:
	//variables
	

	//copy constructor declaration
	TCoordinateSystemCatalogue(const TCoordinateSystemCatalogue&);

	//functions
	TCoordinateSystem  *create3DCartesianSystem();//create a 3D Cartesian CS
	TCoordinateSystem  *create2DCartesianSystem();//create a 2D Cartesian CS
	TCoordinateSystem  *createGeodeticSystem();//create a geodetic CS

	//set of ccordinate systems
	TCoordSysSet  fCoordSystems;//set of CSWrappers
};

#endif //SU_COORDINATE_SYSTEM_CATALOGUE