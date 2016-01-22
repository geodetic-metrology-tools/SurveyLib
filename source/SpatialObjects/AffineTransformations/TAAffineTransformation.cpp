
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

	if (!spos.isNull() && this->isInitialise())
	{
		TPositionVector vect = spos.getCoordinates(TCoordSysFactory::k3DCartesian);
		this->operator ()(vect);
		spos.setCoordinates(vect);
	}
	else
	{
		spos.setStatus( TVNumericValue::kNull );
	}
	return spos;
}


TSpatialVector &  TAAffineTransformation::operator() ( TSpatialVector & svec) const
{// apply this transformation to a spatial vector
	if (!svec.isNull() && this->isInitialise())
	{
		TFreeVector vect = svec.getElements(TCoordSysFactory::k3DCartesian);
		this->operator ()(vect);
		svec.setElements(vect);
	}
	else
	{
		svec.setStatus( TVNumericValue::kNull );
	}
	return svec;
}


TSpatialOrientation &  TAAffineTransformation::operator() ( TSpatialOrientation & sori) const
{// apply this transformation to a spatial orientation

	if( !sori.isNull() && this->isInitialise() )
	{
		TRotationMatrix matrix = sori.getElements(TCoordSysFactory::k3DCartesian);
		this->operator ()(matrix);
		sori.setElements(matrix);
	}
	else
	{
		sori.setStatus( TVNumericValue::kNull );
	}
	return sori;
}
