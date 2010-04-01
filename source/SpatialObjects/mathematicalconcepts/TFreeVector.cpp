// TFreeVector.cpp
//
/** 3D Vector used as a Spatial Position for stations or as translation vector in Helmert transformation */
//
// Patterns:
//
// 
// Copyright 2000 CERN EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
//#include  "TLength.h"
#include  "TVCoordinateSystem.h"
#include  "TDouble.h"
#include  "TFreeVector.h"
////////////////////////////////////////////////////////////////


//ClassImp(TFreeVector)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TFreeVector::TFreeVector(TCoordSysFactory::ECoordSys en)
{	// default constructor
	
	setCoordSys(en);
	setStatus(kNull);
}

TFreeVector::TFreeVector(const quad& x, const quad& y, const quad&z, TCoordSysFactory::ECoordSys en)
{
	setX(0, x);
	setX(1, y);
	setX(2, z);
	setCoordSys(en);
	setStatus(kKnown);
}

/*TFreeVector::TFreeVector(const quad& x, const quad& y, const quad&z)
{
	setX(0, x);
	setX(1, y);
	setX(2, z);
	setStatus(kKnown);
}
*/

TFreeVector::TFreeVector(  const TFreeVector& original )
{	// copy constructor
	setX(0, original.getX(0));
	setX(1, original.getX(1));
	setX(2, original.getX(2));
	setCoordSys(original.getCoordSys());
	setStatus(original.getStatus());
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
	TANumericValue::EStatus status = this->testStatus(second);
	if (status != kNull && testCoordSysCart(second.getCoordSys())==true)
	{	resultat.setX(0, getX(0) + second.getX(0));
		resultat.setX(1, getX(1) + second.getX(1));
		resultat.setX(2, getX(2) + second.getX(2));
	
	}
	else{status=TVNumericValue::kNull;}
	resultat.setStatus(status);
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
	TANumericValue::EStatus status = this->testStatus(second);
	if (status != kNull && testCoordSysCart(second.getCoordSys())==true)
	{	resultat.setX(0, getX(0) - second.getX(0));
		resultat.setX(1, getX(1) - second.getX(1));
		resultat.setX(2, getX(2) - second.getX(2));
	}
	else{status=TVNumericValue::kNull;}
	resultat.setStatus(status);
	return resultat;
}


TFreeVector& TFreeVector::operator-=( const TFreeVector& second)
{//!Add two FreeVector and replace *this
	*this=(*this)-second;
	return (*this);
}


TFreeVector TFreeVector::operator*( const TDouble& factor)
{//!Multiplication by a TDouble object
	TFreeVector resultat (getCoordSys());
	TANumericValue::EStatus status = this->testStatus(factor);
	if (status != kNull)
		{	resultat.setX(0, factor.getValue()*getX(0)); 
			resultat.setX(1, factor.getValue()*getX(1));
			resultat.setX(2, factor.getValue()*getX(2));
		}
	resultat.setStatus(status);
	return resultat;
}

TFreeVector TFreeVector::operator*( const quad& factor)
{//!Multiplication by a TDouble object
	TFreeVector resultat (getCoordSys());
	if (this->isNull() == false)
	{	resultat.setX(0, factor*getX(0)); 
		resultat.setX(1, factor*getX(1));
		resultat.setX(2, factor*getX(2));
	}
	resultat.setStatus(getStatus());
	return resultat;
}


TFreeVector&  TFreeVector::operator=( const TFreeVector& right)
{//!Copy Assignment operator
	if (this != &right)
	{	setX(0, right.getX(0));
		setX(1, right.getX(1));
		setX(2, right.getX(2));
		if (right.isNull() == true)
			{setStatus(kNull);}
		else
			{setStatus(right.getStatus());}
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
	if(this->getStatus() != kNull)
	{
		length.setMetresValue(__sqrtq(__powq((getX()).getMetresValue(),2)+__powq((getY()).getMetresValue(),2)+__powq((getZ()).getMetresValue(),2)));
		length.setStatus(this->getStatus());
	}
	else
	{
		length.setMetresValue(0);
		length.setStatus(kNull);
	}
	return length;
}



TLength TFreeVector::getHorDist() const
{///give the length of a TFreeVector (meters)
	TLength length;
	if(this->getStatus() != kNull)
	{
		length.setMetresValue( __sqrtq( __powq((getX()).getMetresValue(),2) + __powq((getY()).getMetresValue(),2) ) );
		length.setStatus(this->getStatus());
	}
	else
	{
		length.setMetresValue(0);
		length.setStatus(kNull);
	}
	return length;
}