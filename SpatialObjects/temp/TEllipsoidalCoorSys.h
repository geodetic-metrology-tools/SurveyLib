// T3DCartesianSystem.h : Header File.
//
// Class for a 3D Cartesian Coordinate System
//////////////////////////////////////////////////////////////////////

#if !defined(SU_3D_CARTESIAN_SYSTEM)
#define SU_3D_CARTESIAN_SYSTEM

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000



//Class definition
class T3DCartesianSystem : public TVCoordSystemType  
{
public:
	T3DCartesianSystem();
	virtual ~T3DCartesianSystem();

private:
	TVCoordinatesType	*fCoordsType;


	//ClassDef(T3DCartesianSystem, 1)
};



#endif // !defined(SU_3D_CARTESIAN_SYSTEM)
