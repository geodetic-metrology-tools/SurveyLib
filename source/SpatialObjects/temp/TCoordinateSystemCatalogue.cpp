// TCoordinateSystemCatalogue 
//
// Class(singleton) for a Catalogue of Coordinate Systems.
//
// Used by a TReferenceFrame 
// 
// Patterns: singleton
//
// Copyright 1999,2000, Mark Jones, EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////
#include  "TCoordinateSystem.h"
#include  "TCoorSysWrapper.h"
#include  "TCoordinateSystemCatalogue.h"



//////////////////////////////////////////////////////////////////////
// initialisation
//////////////////////////////////////////////////////////////////////

TCoordinateSystemCatalogue* TCoordinateSystemCatalogue::fCoordSysCatalogue= 0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TCoordinateSystemCatalogue::TCoordinateSystemCatalogue()
{}

TCoordinateSystemCatalogue::~TCoordinateSystemCatalogue()
{//delete each member of the set of wrappers
	TCoordSysSet::iterator  iter;
	iter = fCoordSystems.begin();
	while (iter != fCoordSystems.end())
		{	delete (iter->getCoordSys());
			iter++;
		}
}


//////////////////////////////////////////////////////////////////////
// Public Member Functions
//////////////////////////////////////////////////////////////////////

TCoordinateSystemCatalogue* TCoordinateSystemCatalogue::Instance() 
{//singleton
	if (fCoordSysCatalogue == 0)
	{	fCoordSysCatalogue = new TCoordinateSystemCatalogue;
	}
	return fCoordSysCatalogue;
}

TCoordinateSystem *TCoordinateSystemCatalogue::getCoordSys (TCoordinateSystem::ECoordinateSystem coordsys)
{//return a pointer to the appropriate CS or create it if not in set 	
	bool coorSysFound=false;
	
	TCoordinateSystem *CSPtr;
	TCoordSysSet::iterator  iter;

	iter = fCoordSystems.begin();

	while ((iter != fCoordSystems.end())  &&  (coorSysFound != true))
		{
			if (iter->getName() == coordsys)
			{
				coorSysFound = true;
			}
			else iter++;
		}


	if (coorSysFound == true) 
	{
		CSPtr = iter->getCoordSys();
	}
	else
	{//creation	
		TCoorSysWrapper csw;
		switch(coordsys)
		{
		case TCoordinateSystem::k3DCartesian:
			CSPtr = create3DCartesianSystem();
			csw.setCoordSys(CSPtr);
			break;

		case TCoordinateSystem::k2DCartesian:
			CSPtr = create2DCartesianSystem();
			csw.setCoordSys(CSPtr);
			break;

		case TCoordinateSystem::kGeodetic:
			CSPtr = createGeodeticSystem();
			csw.setCoordSys(CSPtr);
			break;

		default:
			break;
		
		
		}
		
		fCoordSystems.insert(csw);
	
	}
	
	return CSPtr;
}


/////////////////////////////////////////////////////////////////////
//Private Member Functions used to create pointers to CS
/////////////////////////////////////////////////////////////////////

TCoordinateSystem  *TCoordinateSystemCatalogue::create3DCartesianSystem()
{
	TCoordinateSystem  *cartesian3D = new TCoordinateSystem(TCoordinateSystem::k3DCartesian);
	cartesian3D->setCoordTokens(TSpatialPosition::kX, TSpatialPosition::kY, TSpatialPosition::kZ);
	return cartesian3D;
}

TCoordinateSystem  *TCoordinateSystemCatalogue::create2DCartesianSystem()
{
	TCoordinateSystem  *cartesian2D=new TCoordinateSystem(TCoordinateSystem::k2DCartesian);
	cartesian2D->setCoordTokens(TSpatialPosition::kX, TSpatialPosition::kY);
	return cartesian2D;
}

TCoordinateSystem  *TCoordinateSystemCatalogue::createGeodeticSystem()
{
	TCoordinateSystem  *geodetic = new TCoordinateSystem(TCoordinateSystem::kGeodetic);
	geodetic->setCoordTokens(TSpatialPosition::kPhi, TSpatialPosition::kLambda, TSpatialPosition::kHEllipse);
	return geodetic;
}