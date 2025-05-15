//  TTerrestrialReferenceFrame.cpp

/** A Terrestrial reference frame like ETRF or ITRF
	It is a Geodetic Reference Frame with an epoch parameter


	Patterns:
	A concrete STATE of a Spatial Position


*/
//////////////////////////////////////////////////////////////////////

#include "TTerrestrialReferenceFrame.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TTerrestrialReferenceFrame::TTerrestrialReferenceFrame(const std::string& name, TReferenceEllipsoid* ell , TReal& epoch, std::string& solution)
	: TGeodeticRefFrame(name, ell)
{	// constructor taking the name of the reference frame, the associated ellipsoid, the epoch of the coordinates and the specific solution
		fEpoch = epoch;
		fSolution = solution;
}

TTerrestrialReferenceFrame::~TTerrestrialReferenceFrame()
{
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////

bool	TTerrestrialReferenceFrame::setEpoch(TReal epoch)
{	// set the epoch of the coordinates

	this->fEpoch = epoch;


	return true;
}

bool TTerrestrialReferenceFrame::setSolution(std::string solution)
{  // set the specific solution
	this->fSolution = solution;

	return true;
}
