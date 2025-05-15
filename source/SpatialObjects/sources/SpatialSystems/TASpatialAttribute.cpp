// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include  "TASpatialAttribute.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TASpatialAttribute::TASpatialAttribute() : fRefFrame(0)
{	// default constructor
	TSpatialStatus* ps = new TSpatialStatus();
	counted_ptr< TSpatialStatus >* tempPtr = new counted_ptr< TSpatialStatus >(ps);
	fSpatialStatus = *tempPtr;

	delete tempPtr;

}


TASpatialAttribute::TASpatialAttribute( TAReferenceFrame* rf )
{
	fRefFrame = rf;

	TSpatialStatus* ps = new TSpatialStatus();
	counted_ptr<TSpatialStatus>* tempPtr = new counted_ptr<TSpatialStatus>(ps);
	fSpatialStatus = *tempPtr;
	delete tempPtr;
}


TASpatialAttribute::TASpatialAttribute( TAReferenceFrame* rf, TSpatialStatus* status)
{
	fRefFrame = rf;

	counted_ptr<TSpatialStatus>* tempPtr = new counted_ptr<TSpatialStatus>(status);
	fSpatialStatus = *tempPtr;
	delete tempPtr;
}


TASpatialAttribute::TASpatialAttribute( TAReferenceFrame* rf, counted_ptr<TSpatialStatus> cp )
{
	fRefFrame = rf;
	fSpatialStatus = cp;
}

TASpatialAttribute::~TASpatialAttribute()
{//destructor
}




//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////
TASpatialAttribute&  TASpatialAttribute::operator=(const TASpatialAttribute& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		fSpatialStatus = right.fSpatialStatus;
		fRefFrame = right.fRefFrame;
	}
	return *this;
}


//////////////////////////////////////////////////////////////////////
//END
//////////////////////////////////////////////////////////////////////

