#include  "TPositionVector.h"
#include  "TVCoordinateSystem.h"

//////////////////////////////////////////////////////////////////////
// Constructor/Destructor
//////////////////////////////////////////////////////////////////////

TPositionVector::TPositionVector(TCoordSysFactory::ECoordSys en) :TACoordSysVector()
{	// default constructor
	setCoordSys(en); 
}

TPositionVector::TPositionVector(const TReal& x, const TReal& y, const TReal& z,TCoordSysFactory::ECoordSys en)
{
	setX(0, x);
	setX(1, y);
	setX(2, z);
	setCoordSys(en);
}



TPositionVector::TPositionVector(  const TPositionVector& original )
{	// copy constructor

	for (int i=0; i<3; i++)
	{
		setX(i, original.getX(i));
	}
	setCoordSys(original.getCoordSys());
}


TPositionVector::~TPositionVector()
{
}



//////////////////////////////////////////////////////////////////////
// operator Functions
//////////////////////////////////////////////////////////////////////

//Equivalence Operator
bool TPositionVector::operator==( const TPositionVector& right) const
{
	return TACoordSysVector::operator ==(right);
}


TPositionVector TPositionVector::operator+(const TFreeVector& second)
{//!add a PositionVector  and FreeVector, return a PositionVector
	TPositionVector resultat (getCoordSys());
	bool fContinue = second.isInitialise() && this->isInitialise();
	if (fContinue && testCoordSysCart(second.getCoordSys()) == true)
	{
		resultat.setX(getX() + second.getX());
		resultat.setY(getY() + second.getY());
		resultat.setZ(getZ() + second.getZ());
	}

	return resultat;
}

TPositionVector TPositionVector::operator-(const TFreeVector& second)
{//!add a PositionVector  and FreeVector, return a PositionVector
	TPositionVector resultat (getCoordSys());
	bool fContinue = second.isInitialise() && this->isInitialise();
	if (fContinue && testCoordSysCart(second.getCoordSys()) == true)
	{
		resultat.setX(getX() - second.getX());
		resultat.setY(getY() - second.getY());
		resultat.setZ(getZ() - second.getZ());
	}

	return resultat;
}


TPositionVector& TPositionVector::operator+=(const TFreeVector& second)
{//!add a PositionVector and FreeVector, replace this
	*this=(*this)+second;
	return *this;
}

TPositionVector& TPositionVector::operator-=(const TFreeVector& second) {
	*this=(*this)-second;
	return *this;
}


TFreeVector TPositionVector::operator-( const TPositionVector& second)
{//!substract two TPositionVector objects and return a FreeVector
	TFreeVector resultat (getCoordSys());
	bool fContinue = second.isInitialise() && this->isInitialise();
	if (fContinue && testCoordSysCart(second.getCoordSys()) == true)
	{
		resultat.setX(getX() - second.getX());
		resultat.setY(getY() - second.getY());
		resultat.setZ(getZ() - second.getZ());
	}

	return resultat;
}

TPositionVector TPositionVector::operator+(const TPositionVector& second)
{//!Add two TPositionVector objects and return a PositionVector
	TPositionVector resultat(getCoordSys());
	bool fContinue = second.isInitialise() && this->isInitialise();
	if (fContinue && testCoordSysCart(second.getCoordSys()) == true)
	{
		resultat.setX(getX() + second.getX());
		resultat.setY(getY() + second.getY());
		resultat.setZ(getZ() + second.getZ());
	}

	return resultat;
}

TPositionVector TPositionVector::operator*( const TDouble& factor)
{//!Multiplication by a TDouble object
	TPositionVector resultat (getCoordSys());

	if ( factor.getValue() != NO_VALf && this->isInitialise())
	{
		TReal scalar = factor.getValue();
		resultat.setX( 0, scalar * getX(0) );
		resultat.setX( 1, scalar * getX(1) );
		resultat.setX( 2, scalar * getX(2) );
	}

	return resultat;
}


TPositionVector TPositionVector::operator *( const TScalar& factor)
{//!Multiplication by a TScalar
	TPositionVector resultat (getCoordSys());

	if ( factor.getValue() != NO_VALf && this->isInitialise())
	{
		TReal scalar = factor.getValue();
		resultat.setX( 0, scalar * getX(0) );
		resultat.setX( 1, scalar * getX(1) );
		resultat.setX( 2, scalar * getX(2) );
	}

	return resultat;
}


TPositionVector TPositionVector::operator*(const TReal& factor)
{//!Multiplication by a TReal object
	TPositionVector resultat (getCoordSys());
	if ( factor != NO_VALf && this->isInitialise())
	{
		resultat.setX(0, getX(0)*factor); 
		resultat.setX(1, getX(1)*factor);
		resultat.setX(2, getX(2)*factor);
	}

	return resultat;
}


TPositionVector & TPositionVector::operator *=( const TScalar& right)
{//Multiply this vector by a TScalar
	*this = (*this) * right;
	return (*this);
}


TPositionVector & TPositionVector::operator *=( const TReal& right)
{//Multiply this vector by a TScalar
	*this = (*this) * right;
	return (*this);
}


TPositionVector&  TPositionVector::operator=( const TPositionVector& right)
{//! Copy Assignment operator
	if (this != &right)
	{
		setX(0, right.getX(0));
		setX(1, right.getX(1));
		setX(2, right.getX(2));
	}

	setCoordSys(right.getCoordSys());
	return *this;
}


/////////////////////////////////////////////////////////////////////////////////////
///Member Function
/////////////////////////////////////////////////////////////////////////////////////

TLength TPositionVector::dist(const TPositionVector& pv) const
{//!Give the distance between this and a second point defined by theirs position vector
	TFreeVector fv (getCoordSys());
	TPositionVector vect(*this);
	fv = vect - pv;
	return fv.length();
}


TLength TPositionVector::getH() const
{//!get the H value of a TPositionVector if is defined
	return getCoordSysPtr()->getH(this);
}


TAngle TPositionVector::getLambdaEllipsoid() const
{//!get the lambda value of a TPositionVector if is defined
	return getCoordSysPtr()->getLambdaEllipsoid(this);
}


TAngle TPositionVector::getPhiEllipsoid() const
{//!get the phi value of a TPositionVector if is defined
	return getCoordSysPtr()->getPhiEllipsoid(this);
}


bool TPositionVector::setH(const TLength& h)
{//!set the H coordinate of a vector in a specific Coordinate System return true if X is defined
return getCoordSysPtr()->setH(this, h);
}


bool TPositionVector::setLambdaEllipsoid(const TAngle& lambda)
{//!set the Lambda coordinate of a vector in a geodetic Coordinate System return true if X is defined
return getCoordSysPtr()->setLambdaEllipsoid(this, lambda);
}


bool TPositionVector::setPhiEllipsoid(const TAngle& phi)
{//!set the Phi coordinate of a vector in a geodetic Coordinate System return true if X is defined
return getCoordSysPtr()->setPhiEllipsoid(this, phi);
}
