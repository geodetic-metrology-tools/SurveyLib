// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿
#include  "TSpatialPosition.h"
#include  "TSpatialVector.h"
#include  "TSpatialOrientation.h"
#include  "TCompositeAffTransform.h"
#include  "TAAffineTransformation.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



TAAffineTransformation::TAAffineTransformation()
{
}

	
TAAffineTransformation::~TAAffineTransformation()
{
}


//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Composition
// Create a composite transformation by applying this transformation 
// to an affine transformation
//////////////////////////////////////////////////////////////////////
TCompositeAffTransform & TAAffineTransformation::operator()( TCompositeAffTransform & right ) const
{
	right.prepend( *this );
	return right;
}


TCompositeAffTransform TAAffineTransformation::operator()( const TAAffineTransformation & right ) const
{
	TCompositeAffTransform result( *this );
	return result( right );
}


bool  TAAffineTransformation::transform( TSpatialPosition& spos) const
{// transform a spatial position
	TPositionVector vect = spos.getCoordinates(TCoordSysFactory::k3DCartesian);
	bool transformed = transform(vect);
	if (transformed == true)
	{
		spos.setCoordinates(vect);
	}
	return transformed;

}


bool  TAAffineTransformation::transform( TSpatialVector& svec) const
{// transform a spatial vector
	TFreeVector vect = svec.getElements(TCoordSysFactory::k3DCartesian);
	bool transformed = transform(vect);
	if (transformed == true)
	{
		svec.setElements(vect);
	}
	return transformed;
}


bool  TAAffineTransformation::transform( TSpatialOrientation& sori) const
{// transform a spatial orientation
	TRotationMatrix matrix = sori.getElements(TCoordSysFactory::k3DCartesian);
	bool transformed = transform(matrix);
	if (transformed == true)
	{
		sori.setElements(matrix);
	}
	return transformed;
}


TSpatialPosition &  TAAffineTransformation::operator() ( TSpatialPosition & spos ) const
{// apply this transformation to a spatial position

	if (spos.isInitialise() && this->isInitialise())
	{
		TPositionVector vect = spos.getCoordinates(TCoordSysFactory::k3DCartesian);
		this->operator ()(vect);
		spos.setCoordinates(vect);
	}

	return spos;
}


TSpatialVector &  TAAffineTransformation::operator() ( TSpatialVector & svec) const
{// apply this transformation to a spatial vector
	if (svec.isInitialise() && this->isInitialise())
	{
		TFreeVector vect = svec.getElements(TCoordSysFactory::k3DCartesian);
		this->operator ()(vect);
		svec.setElements(vect);
	}

	return svec;
}


TSpatialOrientation &  TAAffineTransformation::operator() ( TSpatialOrientation & sori) const
{// apply this transformation to a spatial orientation

	if( sori.isInitialise() && this->isInitialise() )
	{
		TRotationMatrix matrix = sori.getElements(TCoordSysFactory::k3DCartesian);
		this->operator ()(matrix);
		sori.setElements(matrix);
	}

	return sori;
}
