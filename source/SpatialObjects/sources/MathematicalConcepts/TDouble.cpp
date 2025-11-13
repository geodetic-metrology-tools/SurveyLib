// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include	"T3DMatrix.h"
#include	"TFreeVector.h"
#include	"TDouble.h"




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


TDouble::TDouble(): fValue(NO_VALf)
{	// default constructor 
}



TDouble::TDouble(TReal	value): fValue(value)
{	// constructor taking a given length value in metres
}

TDouble::TDouble(const TDouble& tD)
{	// copy constructor
	fValue = tD.fValue;
}

TDouble::~TDouble()
{
}


//////////////////////////////////////////////////////////////////////
// operators definitions
//////////////////////////////////////////////////////////////////////

//////////////
// set and get
//////////////
void TDouble::setValue(const TReal value)
{	// set a value to a TDouble Object
	fValue = value;
	return;
}

TReal TDouble::getValue() const
{	// give the value of a TDouble Object
	 return fValue;
}


////////////////////
// basic operator
////////////////////
bool TDouble::operator==(const TDouble& right) const
{
	if ( getValue() == right.getValue())
		return true;
	else
		return false;
}


bool TDouble::operator<(const TDouble& right) const
{//comparaison between two TDouble objects
	if ( getValue() < right.getValue())
		return true;
	else
		return false;
}


TDouble TDouble::operator+(const TDouble& double1)
{//add two Double objects
	TDouble resultat;

	if (double1.getValue() != NO_VALf && this->getValue() != NO_VALf)
		resultat = (double1.getValue() + this->getValue());


	return resultat;
}


TDouble TDouble::operator-(const TDouble &double1)
{//substract two TDouble objects
	TDouble resultat;
	if (double1.getValue() != NO_VALf && this->getValue() != NO_VALf)
		resultat = (this->getValue() -double1.getValue());

	return resultat;
}	

	
TDouble TDouble::operator*(const TDouble& factor)
{//multiply a TDouble object by an other
	TDouble resultat;
	if (factor.getValue() != NO_VALf && this->getValue() != NO_VALf)
	{
		TDouble resul(this->getValue()*factor.getValue());
		resultat=resul;
	}

return resultat;
}


TDouble TDouble::operator/(const TDouble& div)
{//divide a TDouble object by an other
	TDouble resultat;
	if (div.getValue() != NO_VALf && this->getValue() != NO_VALf)
		if (div.getValue() != 0)
		{
			TDouble resul(this->getValue() / div.getValue());
			resultat = resul;
		}
		else
			throw std::runtime_error("Division by 0. ");



	return resultat;
}

TDouble&	TDouble::operator=(const TDouble &double1)
{//assign a TDouble object to an other
	if (this != &double1) 
		fValue=(double1.getValue());

	return *this;
}


TDouble& TDouble::operator+=(const TDouble &double1)
{//add two TDouble objects and rewrite this
	TDouble noconst (double1);
	*this=(*this)+noconst;
	return (*this);
}


TDouble& TDouble::operator-=(const TDouble &double1)
{//substract two TDouble objects and rewrite this
	TDouble noconst (double1);
	*this=(*this)-noconst;
	return *this;
}


TDouble& TDouble::operator*=(const TDouble& factor)
{//multiply a TDouble object by an other TDouble object and rewrite this
	TDouble noconst (factor);
	*this=(*this)*noconst;
	return *this;
}


TDouble& TDouble::operator/=(const TDouble& div)
{//divide a TDouble object by an other TDouble object and rewrite this
	TDouble noconst (div);
	*this=(*this)/noconst;
	return *this;
}

//////////////////////////
///Special Methods
//////////////////////////////
TAngle TDouble::operator *(const TAngle angle)
{//multiply a TDouble object by a TAngle object
	TAngle resultat;
	if (angle != NO_VALf && this->getValue() != NO_VALf)
	{	
		TAngle noconst(angle);
		TAngle	resul=noconst*(this->getValue());
		resultat=resul;
	}

	return resultat;
}


TLength TDouble::operator *(const TLength length)
{//multiply a TDouble object by a TLength object
	TLength resultat;
	if (length != NO_VALf && this->getValue() != NO_VALf)
	{	
		TLength noconst (length);
		TLength resul=noconst*(this->getValue());
		resultat=resul;
	}

	return resultat;
}


TMatrix TDouble::operator *(const TMatrix mx)
{//multiply a TDouble object by a TMatrix object
	TMatrix resultat(mx.numRows(),mx.numCols());
	if (mx.isInitialise() && this->getValue() != NO_VALf)
	{	
		TMatrix noconst(mx);
		TMatrix resul= noconst * (this->getValue());
		resultat=resul;
	}

	return resultat;
}

T3DMatrix TDouble::operator *(const T3DMatrix mx)
{//multiply a TDouble object by a T3DMatrix object
	T3DMatrix resultat(mx.getCoordSys());

	if (mx.isInitialise() && this->getValue() != NO_VALf)
	{	
		T3DMatrix noconst(mx);
		T3DMatrix resul= noconst * (this->getValue());
		resultat=resul;
	}

return resultat;
}

TColumnVector TDouble::operator *(const TColumnVector cv)
{//multiply a TDouble object by a TColumnVector object
	TColumnVector resultat (cv.dimension());
	if (cv.isInitialise() && this->getValue() != NO_VALf)
	{	
		TColumnVector noconst (cv);
		TColumnVector resul=noconst*(this->getValue());
		resultat=resul;
	}

	return resultat;
}

TFreeVector TDouble::operator *(const TFreeVector cv)
{//multiply a TDouble object by a TColumnVector object
	TFreeVector resultat (cv.getCoordSys());
	if (cv.isInitialise() && this->getValue() != NO_VALf)
	{	
		TFreeVector noconst (cv);
		TFreeVector resul=noconst*(this->getValue());
		resultat=resul;
	}

return resultat;
}

//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////

	


