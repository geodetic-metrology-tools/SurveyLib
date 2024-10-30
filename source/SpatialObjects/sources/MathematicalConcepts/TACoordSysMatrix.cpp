#include "TACoordSysMatrix.h"

#include "TVCoordinateSystem.h"

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////

TACoordSysMatrix::TACoordSysMatrix()
{
	int i = 0;
	while (i < 3)
	{
		int j = 0;
		while (j < 3)
		{
			mx[i][j] = NO_VALf;
			j++;
		}
		i++;
	}

	fCoordSys = 0;
}

bool TACoordSysMatrix::testCoordSysCart(TCoordSysFactory::ECoordSys en) const
{ // test if two object have the same cartesian coordinate system
	if (getCoordSys() == en && (en == TCoordSysFactory::k2DCartesian || en == TCoordSysFactory::k3DCartesian))
		return true;
	else
		return false;
}

bool TACoordSysMatrix::testCoordSysGen(TCoordSysFactory::ECoordSys en) const
{ // test if two object have the same general coordinate system
	if (getCoordSys() == en)
		return true;
	else
		return false;
}

TVCoordinateSystem *TACoordSysMatrix::getCoordSysPtr() const
{ // get the *TVCoordinateSystem
	return fCoordSys;
}

TCoordSysFactory::ECoordSys TACoordSysMatrix::getCoordSys() const
{ // get the ECoordSys
	return fCoordSys->getCoordSysId();
}

void TACoordSysMatrix::setCoordSys(TCoordSysFactory::ECoordSys en)
{ // sets the coordinate system
	fCoordSys = TCoordSysFactory::getCoordSysFactoryPtr()->getCoordSys(en);
	return;
}

void TACoordSysMatrix::setCoordSysTRotation(TRotationMatrix *rotmx, TCoordSysFactory::ECoordSys en)
{ // set the coordinate system for a rotation matrix
	if (en == TCoordSysFactory::k3DCartesian)
		fCoordSys = TCoordSysFactory::getCoordSysFactoryPtr()->getCoordSys(en);
	else
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				rotmx->setC(i, j, NO_VALf);
}

//////////////////////////////////////////////////////////////////////
// Member Protected Functions
//////////////////////////////////////////////////////////////////////

TReal TACoordSysMatrix::getC(const int &i, const int &j) const
{ // get the (i,j) value
	return mx[i][j];
}

Eigen::Matrix3d TACoordSysMatrix::getMat() const
{
	Eigen::Matrix3d rotMat;
	rotMat << mx[0][0], mx[0][1], mx[0][2], mx[1][0], mx[1][1], mx[1][2], mx[2][0], mx[2][1], mx[2][2];
	return rotMat;
}

void TACoordSysMatrix::setC(const int &i, const int &j, TReal value)
{ //! set value to (i,j)
	mx[i][j] = value;
}

bool TACoordSysMatrix::isInitialise() const
{
	int i = 0;
	while (i < 3)
	{
		int j = 0;
		while (j < 3)
		{
			if (mx[i][j] == NO_VALf)
				return false;
			j++;
		}
		i++;
	}

	return true;
}
