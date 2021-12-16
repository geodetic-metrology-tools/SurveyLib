//  TTerrestrialReferenceFrame.cpp
/*
© Copyright CERN 2000-2021. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
/** A Terrestrial reference frame like ETRF or ITRF
	It is a Geodetic Reference Frame with an epoch parameter


	Patterns:
	A concrete STATE of a Spatial Position

	Copyright 2021 CERN EST/SU. All rights reserved.

*/
//////////////////////////////////////////////////////////////////////

#include "TTerrestrialReferenceFrame.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TTerrestrialReferenceFrame::TTerrestrialReferenceFrame(const std::string& name, TReferenceEllipsoid* ell , TReal& epoch)
	: TGeodeticRefFrame(name, ell)
{	// constructor taking the name of the reference frame, the associated ellipsoid and the epoch of the coordinates
		fEpoch = epoch;
}


TTerrestrialReferenceFrame::~TTerrestrialReferenceFrame()
{
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////

bool	TTerrestrialReferenceFrame::setEpoch(const TReal epoch)
{	// set the epoch of the coordinates

	this->fEpoch = epoch;


	return true;
}
