#include  "TFreeVector.h"
#include  "TVCoordinateSystem.h"
#include  "TDouble.h"
#include  "TScalar.h"

//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TFreeVector::TFreeVector() :TACoordSysVector()
{	// default constructor	
   setCoordSys(TCoordSysFactory::ECoordSys::k3DCartesian);
}

TFreeVector::TFreeVector(const TVector &vec, TCoordSysFactory::ECoordSys en) : TACoordSysVector(vec, en)
{
}

TFreeVector::TFreeVector(TCoordSysFactory::ECoordSys en) :TACoordSysVector()
{	// default constructor	
	setCoordSys(en);
}

TFreeVector::TFreeVector(const TReal& x, const TReal& y, const TReal&z, TCoordSysFactory::ECoordSys en)
{
	setX(0, x);
	setX(1, y);
	setX(2, z);
	setCoordSys(en);

}

TFreeVector::TFreeVector(const TPositionVector& p)
{
	setX(0, p.getX());
	setX(1, p.getY());
	setX(2, p.getZ());
	setCoordSys(p.getCoordSys());
}


TFreeVector::TFreeVector(const TFreeVector& original)
{	// copy constructor
	setX(0, original.getX(0));
	setX(1, original.getX(1));
	setX(2, original.getX(2));
	setCoordSys(original.getCoordSys());
}


TFreeVector::~TFreeVector()
{
}


//////////////////////////////////////////////////////////////////////
// operator Functions 
//////////////////////////////////////////////////////////////////////

//Equivalence Operator 
bool TFreeVector::operator==( const TFreeVector& right) const
{
	return TACoordSysVector::operator ==(right);
}


TFreeVector TFreeVector::operator+( const TFreeVector& second)
{//!Add two FreeVector
	TFreeVector resultat (getCoordSys());
	bool fContinue = second.isInitialise() && this->isInitialise();
	if (fContinue && testCoordSysCart(second.getCoordSys())==true)
	{	
		resultat.setX(0, getX(0) + second.getX(0));
		resultat.setX(1, getX(1) + second.getX(1));
		resultat.setX(2, getX(2) + second.getX(2));	
	}

	return resultat;
}

	
TFreeVector& TFreeVector::operator+=( const TFreeVector& second)
{//!Add two FreeVector and replace *this
	*this=(*this)+second;
	return (*this);
}



TFreeVector TFreeVector::operator-( const TFreeVector& second)
{//!Substract two FreeVector
	TFreeVector resultat (getCoordSys());
	bool fContinue = second.isInitialise() && this->isInitialise();
	if (fContinue && testCoordSysCart(second.getCoordSys()) == true)
	{	
		resultat.setX(0, getX(0) - second.getX(0));
		resultat.setX(1, getX(1) - second.getX(1));
		resultat.setX(2, getX(2) - second.getX(2));
	}

	return resultat;
}


TFreeVector& TFreeVector::operator-=( const TFreeVector& second)
{//!Substract two FreeVector and replace *this
	*this=(*this)-second;
	return (*this);
}


TFreeVector TFreeVector::operator*( const TDouble& factor)
{//!Multiplication by a TDouble object
	TFreeVector resultat (getCoordSys());

	if (factor.getValue() != NO_VALf && this->isInitialise())
    {	
        TReal scalar = factor.getValue();
		resultat.setX( 0, scalar * getX(0) ); 
		resultat.setX( 1, scalar * getX(1) );
		resultat.setX( 2, scalar * getX(2) );
    }

	return resultat;
}

TFreeVector TFreeVector::operator*( const TScalar& factor)
{//!Multiplication by a TScalar object
	TFreeVector resultat (getCoordSys());
	
	if (factor.getValue() != NO_VALf && this->isInitialise())
	{	
		TReal scalar = factor.getValue();
		resultat.setX( 0, scalar * getX(0) ); 
		resultat.setX( 1, scalar * getX(1) );
		resultat.setX( 2, scalar * getX(2) );
	}

	return resultat;
}

TFreeVector TFreeVector::operator*( const TReal& factor)
{//!Multiplication by a TDouble object
	TFreeVector resultat (getCoordSys());

	if (factor != NO_VALf && this->isInitialise())
	{	resultat.setX(0, factor*getX(0)); 
		resultat.setX(1, factor*getX(1));
		resultat.setX(2, factor*getX(2));
	}

	return resultat;
}


TFreeVector& TFreeVector::operator *=( const TScalar& right)
{//Multiply this vector by a TScalar
	*this = (*this) * right;
	return (*this);
}


TFreeVector& TFreeVector::operator *=( const TReal& right)
{//Multiply this vector by a TScalar
	*this = (*this) * right;
	return (*this);
}


TFreeVector&  TFreeVector::operator=( const TFreeVector& right)
{//!Copy Assignment operator
	if (this != &right)
	{	
		setX(0, right.getX(0));
		setX(1, right.getX(1));
		setX(2, right.getX(2));
	}
	setCoordSys(right.getCoordSys());
	return *this;
}


//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////


TLength TFreeVector::length() const
{///give the length of a TFreeVector (meters)
	TLength length;
	if(this->isInitialise())
		length.setMetresValue(sqrtq(powq((getX()).getMetresValue(),2)+powq((getY()).getMetresValue(),2)+powq((getZ()).getMetresValue(),2)));

	return length;
}


TFreeVector& TFreeVector::normalize() 
{
	TLength norml = length();
	if (norml != NO_VALf) {
		TReal norm = norml.getMetresValue();
		setX(0, getX(0)/norm);
		setX(1, getX(1)/norm);
		setX(2, getX(2)/norm);
	}
	return *this;
}


TFreeVector TFreeVector::cross(const TFreeVector& b) {
	TFreeVector resultat (getCoordSys());
	bool fContinue = b.isInitialise() && this->isInitialise();
	if (fContinue && testCoordSysCart(b.getCoordSys()) == true)
	{	
		resultat.setX(0, getX(1)*b.getX(2) - getX(2)*b.getX(1));
		resultat.setX(1, getX(2)*b.getX(0) - getX(0)*b.getX(2));
		resultat.setX(2, getX(0)*b.getX(1) - getX(1)*b.getX(0));
	}
	else
		throw std::runtime_error("One of the FreeVector elements is NULL or coordinate system does not match!");
	
	return resultat;
}

TReal TFreeVector::dot(const TFreeVector& b) const
{

   TReal  result;
   bool fContinue = b.isInitialise() && this->isInitialise();
   if (fContinue && testCoordSysCart(b.getCoordSys()) == true)
      result = getX(0) * b.getX(0) + getX(1) * b.getX(1) + getX(2) * b.getX(2);
   else
      throw std::runtime_error("One of the FreeVector elements is NULL or coordinate system does not match!");

   return result;
}

TLength TFreeVector::getHorDist() const
{///give the length of a TFreeVector (meters)
	TLength length;

	if(this->isInitialise())
		length.setMetresValue( sqrtq( powq((getX()).getMetresValue(),2) + powq((getY()).getMetresValue(),2) ) );


	return length;
}
