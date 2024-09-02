// TACoordSysMatrix.h
/*
© Copyright CERN 2000-2024. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
/** Abstract class use for explain T3DMatrix and TRotationMatrixin a Coordonate System */
//////////////////////////////////////////////////////////////////////



#ifndef SU_A_COORDSYS_MATRIX
#define SU_A_COORDSYS_MATRIX


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include  "TCoordSysFactory.h"
#include  "Quad.h"
#include <Eigen/Dense>
class TVCoordinateSystem;
class TRotationMatrix;


/*! \ingroup MathematicalConcepts
	@{*/

//! Abstract class use for explain T3DMatrix and TRotationMatrix
class  TACoordSysMatrix
{

public:

	friend class TACoordinateSystem;

	TACoordSysMatrix();
	virtual ~TACoordSysMatrix() { }

	/*!\name member public functions*/
	//@{
	/*!test if two object have the same Cartesian coordinate system
	\return false if it s wrong*/
	bool testCoordSysCart(TCoordSysFactory::ECoordSys) const;

	/*!test if two object have the same general coordinate system
	\return false if it s wrong*/
	bool testCoordSysGen(TCoordSysFactory::ECoordSys) const;

	//! return true if elements of the matrix are not set to NO_VALf
	bool isInitialise() const;
	
	//!get the *TVCoordinateSystem
	TVCoordinateSystem* getCoordSysPtr() const;

	//!get the ECoordSys
	TCoordSysFactory::ECoordSys getCoordSys() const;

	//! sets the coordinate system
	void setCoordSys( TCoordSysFactory::ECoordSys);
	
	//!set the coordinate system for a rotation matrix
	void setCoordSysTRotation(TRotationMatrix*, TCoordSysFactory::ECoordSys);
	//@}
	
	//@{
	//!get the (i,j) value
	TReal getC(const int& i, const int& j) const;
	// get the whole matrix
	Eigen::Matrix3d getMat() const;

	//!set value to (i,j)
	void setC(const int& i, const int& j, TReal value);
	//@}


private:
	
	TReal					mx[3][3]; /*!< element of the 3*3 matrix */
	TVCoordinateSystem*		fCoordSys; /*!< coordinate system */
		
	

	//ClassDef(TACoordSysMatrix, 1)
};
/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////


#endif // SU_A_COORDSYS_MATRIX
