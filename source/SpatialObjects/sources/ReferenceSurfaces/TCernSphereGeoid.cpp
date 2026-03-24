// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TSpatialPosition.h"
#include "TGraph.h"
#include "TAReferenceFrame.h"


#include "TCernSphereGeoid.h"

#include <vector>
#include <math.h>





//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TCernSphereGeoid::TCernSphereGeoid() : fName("")
{//Default constructor
	fDefRFPtr = 0;
	fDefEllPtr = 0;
	fCalcRFPtr = 0;
}


TCernSphereGeoid::TCernSphereGeoid(const std::string &name, const TRefSystemFactory::EGeoid &geoidId, TAReferenceFrame *def, TReferenceEllipsoid *ell, TAReferenceFrame *calc) :
	fName(name), fGeoidId(geoidId)

{ // Constructor
	fDefRFPtr = def;
	fDefEllPtr = ell;
	fCalcRFPtr = calc;
}



TCernSphereGeoid::~TCernSphereGeoid()
{//Destructor
}



//////////////////////////////////////////////////////////////////////
//MEMBER FUNCTIONS
//////////////////////////////////////////////////////////////////////
TLength TCernSphereGeoid::getN ( const TSpatialPosition& sp) const
{
	ignoring(sp);
	TLength NValue (LITERAL(0.0));
	return NValue;

}


TAngle TCernSphereGeoid::getEta ( const TSpatialPosition& sp) const
{
	ignoring(sp);
	TAngle eta(LITERAL(0.0));
	return eta;
}


TAngle TCernSphereGeoid::getXi ( const TSpatialPosition& sp) const
{
	ignoring(sp);
	TAngle xsi(LITERAL(0.0));
	return xsi;
}


TAngle	TCernSphereGeoid::getDAlpha ( const TSpatialPosition& sp ) const
{
	ignoring(sp);
	TAngle alpha (LITERAL(0.0));
	return alpha;
}


TAngle	TCernSphereGeoid::getDAlpha ( const TSpatialPosition& sp, const TAngle& latitude ) const
{
	ignoring(sp);
	ignoring(latitude);
	TAngle alpha (LITERAL(0.0));
	return alpha;
}

////////////////////////////////////////////////////
//END
////////////////////////////////////////////////////
