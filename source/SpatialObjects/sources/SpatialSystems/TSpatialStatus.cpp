#include "TAReferenceFrame.h"
#include  "TSpatialStatus.h"


//////////////////////////////////////////////////////////////////////
//CONSTRUCTOR / DESTRUCTOR
//////////////////////////////////////////////////////////////////////
TSpatialStatus::TSpatialStatus()
{// default constructor	
	fSpatialStatus = kPosNull;
}


TSpatialStatus::TSpatialStatus( const  TSpatialStatus& source ):
fSpatialStatus(source.fSpatialStatus)
{// copy constructor	
}


TSpatialStatus::~TSpatialStatus()
{// destructor
}


//////////////////////////////////////////////////////////////////////
//MEMBER FUNCTIONS
//////////////////////////////////////////////////////////////////////
TSpatialStatus&  TSpatialStatus::operator=(const TSpatialStatus& source)
{// Copy Assignment operator	

	if (this != &source)
		fSpatialStatus  = source.getObjectStatus();
	return *this;
}



int TSpatialStatus::getVariableDimension() const
{// gets the number of variable coordinates

	switch(fSpatialStatus){

	case kCala:
	case kPosNull:
	case kUnknown:
		return 0;
		break;

	case kVx:
	case kVy:
	case kVz:
		return 1;
		break;

	case kVxy:
	case kVxz:
	case kVyz:
		return 2;
		break;

	case kVxyz:
		return 3;
		break;

	default:
		return 0;
		break;
	}
}


#ifdef USE_SERIALIZER
void TSpatialStatus::serialize(SerializerObject::SerializationHelper &obj) const
{
	obj.addProperty("fSpatialStatus", fSpatialStatus);
}
#endif // USE_SERIALIZER


//////////////////////////////////////////////////////////////////////
//END
//////////////////////////////////////////////////////////////////////
