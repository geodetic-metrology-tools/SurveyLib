// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include	"TFreeVector.h"
#include	"T3DMatrix.h"
#include	"TScalar.h"
#include	"TDouble.h"




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


TScalar::TScalar(): fValue(NO_VALf)
{	// default constructor 
}



TScalar::TScalar(TReal	value): fValue(value)
{	// constructor taking a given scalar value
}

TScalar::TScalar(const TScalar& tD)
{	// copy constructor
	fValue = tD.fValue;
}

TScalar::~TScalar()
{
}


//////////////////////////////////////////////////////////////////////
// operators definitions
//////////////////////////////////////////////////////////////////////

//////////////
// set and get
//////////////
void TScalar::setValue(const TReal value)
{	// set a value to a TScalar Object
	fValue = value;
	return;
}

TReal TScalar::getValue() const
{	// give the value of a TScalar Object
	 return fValue;
}


////////////////////
// basic operator
////////////////////
bool TScalar::operator==(const TScalar& right) const
{
	if ( getValue() == right.getValue())
		return true;
	else
		return false;
}


bool TScalar::operator<(const TScalar& right) const
{//comparaison between two TScalar objects
	if ( getValue() < right.getValue())
		return true;
	else
		return false;
}


bool TScalar::operator>(const TScalar& right) const
{//comparaison between two TScalar objects
	if ( getValue() > right.getValue())
		return true;
	else
		return false;
}


TScalar TScalar::operator+(const TScalar& Scalar1)
{//add two Scalar objects
	TScalar resultat;

	if (Scalar1.getValue() != NO_VALf && this->getValue() != NO_VALf)
		resultat = Scalar1.getValue() + this->getValue();

return resultat;
}


TScalar TScalar::operator-(const TScalar &Scalar1)
{//substract two TScalar objects
	TScalar resultat;
	if (Scalar1.getValue() != NO_VALf && this->getValue() != NO_VALf)
		resultat = this->getValue() -Scalar1.getValue();

return resultat;
}	

	
TScalar TScalar::operator*(const TScalar& factor)
{//multiply a TScalar object by an other
	TScalar resultat;
	if (factor.getValue() != NO_VALf && this->getValue() != NO_VALf)
		resultat = (this->getValue()*factor.getValue());

return resultat;
}


TScalar TScalar::operator/(const TScalar& div)
{//divide a TScalar object by an other
	TScalar resultat;
	if (div.getValue() != NO_VALf && this->getValue() != NO_VALf)
		if (div.getValue() != 0)
			resultat = (this->getValue() / div.getValue());
		else
			throw std::runtime_error("Division by 0!");


return resultat;
}

TScalar&	TScalar::operator=(const TScalar &Scalar1)
{//assign a TScalar object to an other
	if (this != &Scalar1) 
		fValue=(Scalar1.getValue());

	return *this;
}


TScalar& TScalar::operator+=(const TScalar &Scalar1)
{//add two TScalar objects and rewrite this
	TScalar noconst (Scalar1);
	*this=(*this)+noconst;
	return (*this);
}


TScalar& TScalar::operator-=(const TScalar &Scalar1)
{//substract two TScalar objects and rewrite this
	TScalar noconst (Scalar1);
	*this=(*this)-noconst;
	return *this;
}


TScalar& TScalar::operator*=(const TScalar& factor)
{//multiply a TScalar object by an other TScalar object and rewrite this
	TScalar noconst (factor);
	*this=(*this)*noconst;
	return *this;
}


TScalar& TScalar::operator/=(const TScalar& div)
{//divide a TScalar object by an other TScalar object and rewrite this
	TScalar noconst (div);
	*this=(*this)/noconst;
	return *this;
}

//////////////////////////
///Special Methods
//////////////////////////////
TAngle TScalar::operator *(const TAngle angle)
{//multiply a TScalar object by a TAngle object
	TAngle resultat;

	if (angle != NO_VALf && this->getValue() != NO_VALf)
	{	
		TAngle noconst(angle);
		TAngle	resul=noconst*(this->getValue());
		resultat=resul;
	}

return resultat;
}


TLength TScalar::operator *(const TLength length)
{//multiply a TScalar object by a TLength object
	TLength resultat;
	if (length != NO_VALf && this->getValue() != NO_VALf)
	{	
		TLength noconst (length);
		TLength resul=noconst*(this->getValue());
		resultat=resul;
	}

return resultat;
}


TMatrix TScalar::operator *(const TMatrix mx)
{//multiply a TScalar object by a TMatrix object
	TMatrix resultat(mx.numRows(),mx.numCols());
	if (mx.isInitialise() && this->getValue() != NO_VALf)
	{	
		TMatrix noconst(mx);
		TMatrix resul= noconst * (this->getValue());
		resultat=resul;
	}

return resultat;
}

T3DMatrix TScalar::operator *(const T3DMatrix mx)
{//multiply a TScalar object by a T3DMatrix object
	T3DMatrix resultat(mx.getCoordSys());

	if (mx.isInitialise() && this->getValue() != NO_VALf)
	{	
		T3DMatrix noconst(mx);
		T3DMatrix resul= noconst * (this->getValue());
		resultat=resul;
	}

return resultat;
}

TColumnVector TScalar::operator *(const TColumnVector cv)
{//multiply a TScalar object by a TColumnVector object
	TColumnVector resultat (cv.dimension());
	if (cv.isInitialise() && this->getValue() != NO_VALf)
	{	
		TColumnVector noconst (cv);
		TColumnVector resul=noconst*(this->getValue());
		resultat=resul;
	}

return resultat;
}

TFreeVector TScalar::operator *(const TFreeVector cv)
{//multiply a TScalar object by a TColumnVector object
	TFreeVector resultat (cv.getCoordSys());

	if (cv.isInitialise() && this->getValue()!= NO_VALf)
	{	
		TFreeVector noconst (cv);
		TFreeVector resul=noconst*(this->getValue());
		resultat=resul;
	}

return resultat;
}

TScalar TScalar::operator*(const TReal factor)
{//multiply a TLength object by a factor
	TScalar resultat;
	if(factor != NO_VALf && this->getValue() != NO_VALf)
		resultat.setValue(factor*(this->getValue()));

	return resultat;
}

//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////

	


