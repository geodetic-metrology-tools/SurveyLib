// TReflection.cpp
//
/** 3D reflexion, affine transformation, six cases are distinguished:
reflexion by a plane x=0, y=0, z=0 or reflexion by the plane x=y, x=z or y=z*/
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
#include  "TLength.h"
#include  "TPositionVector.h"
#include  "TFreeVector.h"
#include  "TTranslation.h"
#include  "TRotation.h"
#include  "TReflection.h"
////////////////////////////////////////////////////////////////


//ClassImp(TReflection)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TReflection::TReflection()
{	// default constructor
	fReflexionType = kNull;
}

TReflection::TReflection(const TReflection::EType type)
{
	fReflexionType = type;
	fillMatrix(type);
}

TReflection::TReflection( const TReflection& original )
{	// copy constructor
	fReflexionType = original.getType();
	fillMatrix(fReflexionType);
}


TReflection::~TReflection()
{
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////



TReflection&  TReflection::operator=( TReflection& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		fReflexionType = right.getType();
		fillMatrix(fReflexionType);
	}
	return *this;
}


TVAffineTransformation*  TReflection::clone() const
{// Return a pointer to a clone of this transformation
	return new TReflection( *this );
}


TTranslation TReflection::operator*(const TTranslation& rightT)
{/// multiplication T2 = P*T1
	TTranslation T2;
	
	for (int i=0; i<3; i++)
	{
		TLength nul(0);
		T2[i] = nul;
		double z;

		for (int j=0; j<3; j++)
		{
			
			z +=  (fReflexionMatrix[i][j]*(rightT[j].getMetresValue()));
		
		}
		TLength component(z);
		T2[i] = component;
		z=0;
	}
	
	return T2;

}


TRotation TReflection::operator*(const TRotation& rightR)
{/// multiplication R2 = P*R1
	TRotation R2;
	
	for (int i=0; i<3; i++)
	{
		for (int j=0; j<3; j++)
		{
			R2(i,j) = 0;

			for (int k=0; k<3; k++)
			{
				R2(i,j) +=  fReflexionMatrix[i][k]*rightR(k,j);
			}
		}
	}
	R2.deduceAngles();
	return R2;
}


double TReflection::operator()(int i, int j) const
{
	// return the ri, cj element with 0<=i,j<=2
	return fReflexionMatrix[i][j];
}


double& TReflection::operator()(int i, int j) 
{
	// return the ri, cj element with 0<=i,j<=2
	return fReflexionMatrix[i][j];
}


TPositionVector TReflection::transform( const TPositionVector& rightV) const
{/// Transform a TPositionVector
	// V2=P*V1
	TPositionVector V2;
	
	for (int i=0; i<3; i++)
	{
		TLength nul(0);
		V2[i] = nul;
		double z;

		for (int j=0; j<3; j++)
		{
			
			z +=  (fReflexionMatrix[i][j]*(rightV[j].getMetresValue()));
		
		}
		TLength component(z);
		V2[i] = component;
		z=0;
	}
	
	return V2;
}

		
TFreeVector TReflection::transform( const TFreeVector & rightV) const
{/// Transform a TFreeVector
	// V2=P*V1
	TFreeVector V2;
	
	for (int i=0; i<3; i++)
	{
		TLength nul(0);
		V2[i] = nul;
		double z;

		for (int j=0; j<3; j++)
		{
			
			z +=  (fReflexionMatrix[i][j]*(rightV[j].getMetresValue()));
		
		}
		TLength component(z);
		V2[i] = component;
		z=0;
	}
	
	return V2;
}
		
TRotationMatrix TReflection::transform( const TRotationMatrix& rm) const
{/// Transform a TRotationMatrix
	return rm;
}


TReflection  TReflection::inverse()
{/// Return the inverse transformation
	TReflection inverse(*this);
	return inverse;
}


void TReflection::invert()
{/// Change this transformation in the inverse
	return ;
}


//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////

void TReflection::fillMatrix( TReflection::EType type )
{
	// create identity
	for (int i=0; i<3; i++)
	{
		for (int j=0; j<3; j++) 
		{
			if (i==j)
			{fReflexionMatrix[i][j]=1;}
			else
			{fReflexionMatrix[i][j]=0;}
		}
	}

	switch (type){

	case kNull:break;

	case kXEq0: fReflexionMatrix[0][0]=-1;break;

	case kYEq0: fReflexionMatrix[1][1]=-1;break;

	case kZEq0: fReflexionMatrix[2][2]=-1;break;

	case kXEqY: fReflexionMatrix[0][0]=0;
				fReflexionMatrix[1][1]=0;
				fReflexionMatrix[0][1]=1;
				fReflexionMatrix[1][0]=1;break;

	case kXEqZ: fReflexionMatrix[0][0]=0;
				fReflexionMatrix[2][2]=0;
				fReflexionMatrix[0][2]=1;
				fReflexionMatrix[2][0]=1;break;

	case kYEqZ: fReflexionMatrix[1][1]=0;
				fReflexionMatrix[2][2]=0;
				fReflexionMatrix[1][2]=1;
				fReflexionMatrix[2][1]=1;break;

	default: break;
	}
	
return;
}

