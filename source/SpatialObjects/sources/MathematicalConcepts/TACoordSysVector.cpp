#include  "TVCoordinateSystem.h"
#include  "TACoordSysVector.h"



TACoordSysVector::TACoordSysVector()
{
	int i = 0;
	while(i<3)
	{
		fVector[i] = NO_VALf;
		i++;
	}
	fCoordSys = 0;
}

TACoordSysVector::TACoordSysVector(const TVector & vec, TCoordSysFactory::ECoordSys en)
{
   if (vec.rows() != 3)
   {
	   throw std::runtime_error("Vector needs to be initialized with a 3-dimensional vector");
   }
   for (int i = 0; i < 3; i++)
   {
	   fVector[i] = vec[i];
   }
   setCoordSys(en);
}

TReal TACoordSysVector::operator[](int i) const
{//! Allows to retrieve one of the coordinates of the vector
	if (i >= 0 && i <= 3)
		return fVector[i];
	throw std::out_of_range("Try to access a TACoordSysVector with a wrong indice : " + i);
}


//Equivalence Operator 
bool TACoordSysVector::operator==( const TACoordSysVector& right) const
{
	bool equal = false;

	if(fVector[0] == right.fVector[0] 
		&& fVector[1] == right.fVector[1] 
		&& fVector[2] == right.fVector[2]
		&& fCoordSys == right.fCoordSys
		) 
		equal = true;

	return equal;
}


//////////////////////////////////////////////////////////////////////
// Member Public Functions
//////////////////////////////////////////////////////////////////////

	
bool TACoordSysVector::testCoordSysCart(TCoordSysFactory::ECoordSys en) const
{//test if two object have the same coordinate system
	if (getCoordSys()== en  && (en==TCoordSysFactory::k3DCartesian || en==TCoordSysFactory::k2DCartesian))
	{return true;}
else
	{return false;}
}


TLength TACoordSysVector::getX()const
{//!get the X coordinate of a vector in a specific Coordinate System
	return fCoordSys->getX(this);
}

TLength TACoordSysVector::getY()const
{//!get the Y coordinate of a vector in a specific Coordinate System
	return fCoordSys->getY(this);
}

TLength TACoordSysVector::getZ()const
{//!get the Z coordinate of a vector in a specific Coordinate System
	return fCoordSys->getZ(this);
}

bool TACoordSysVector::setX(const TLength& xc)
{//!set the X coordinate of a vector in a specific Coordinate System return true if X is defined
return fCoordSys->setX(this, xc);
}

bool TACoordSysVector::setY(const TLength& yc)
{//!set the Y coordinate of a vector in a specific Coordinate System return true if Y is defined
return fCoordSys->setY(this, yc); 
}

bool TACoordSysVector::setZ(const TLength& zc)
{//!set the Z coordinate of a vector in a specific Coordinate System return true if Z is defined
return fCoordSys->setZ(this, zc);
}

TReal& TACoordSysVector::operator[](int i)
{//! Allows to retrieve one of the coordinates of the vector and to modify it
   if(i >= 0 && i <= 3)
      return fVector[i];
   throw std::out_of_range("Try to access a TACoordSysVector with a wrong indice : " + i);
}

TVCoordinateSystem* TACoordSysVector::getCoordSysPtr() const
{//!get fCoordSys
	return fCoordSys;
}

TCoordSysFactory::ECoordSys TACoordSysVector::getCoordSys() const
{//!get ECoordSys
return fCoordSys->getCoordSysId();
}

void TACoordSysVector::setCoordSys(const TCoordSysFactory::ECoordSys en )
{//! sets the coordinate system
	fCoordSys=TCoordSysFactory::getCoordSysFactoryPtr()->getCoordSys(en);
return;
}

T3DMatrix TACoordSysVector::transposed() const
{//!return the tranposed column vector as a 3D matrix
	T3DMatrix result = T3DMatrix(this->getCoordSys());
	for (int i=0; i<3; i++)
	{
		result.setElt(0, i,this->getX(i));
	}
	return result;
}

TVector TACoordSysVector::toRealVector() const
{
	TVector vector(3);
	vector.setZero();
	vector << getX(), getY(), getZ();
	return vector;
}


//////////////////////////////////////////////////////////////////////
// Member Protected Functions
//////////////////////////////////////////////////////////////////////

TReal TACoordSysVector::getX(const int& i) const
{//!get the Xi coordinate of a vector in all Coordinate System
	return fVector[i];
}


void TACoordSysVector::setX(const int& i, const TReal& value)
{//!set the Xi coordinate of a vector in all Coordinate System
	fVector[i]=value;
	return;
}


bool TACoordSysVector::isInitialise() const
{
	if (this->getX() != NO_VALf
		&& this->getY() != NO_VALf
		&& this->getZ() != NO_VALf)
		return true;
	else
		return false;
}


#if USE_SERIALIZER
void TACoordSysVector::serialize(ObjectSerializer &obj) const
{
	obj.addProperty("fVector", fVector);
	obj.addProperty("fCoordSys", fCoordSys);
}
#endif // USE_SERIALIZER
