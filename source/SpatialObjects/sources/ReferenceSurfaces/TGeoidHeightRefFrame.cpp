// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

//  TGeoidHeightRefFrame.cpp

#include "TGeoidHeightRefFrame.h"

#include <stdexcept>

#include "TA2DPlus1MapProjection.h"
#include "TAGeoidModel.h"
#include "TGeodeticRefFrame.h"
#include "TGeoidHeightTransformation.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TGeoidHeightRefFrame::TGeoidHeightRefFrame(TAReferenceFrame *base, TAGeoidModel *geoid) :
	TAReferenceFrame(buildName(base, geoid)), fBase(base), fGeoid(geoid), fHeightCoordSys(TCoordSysFactory::kGeodetic)
{
	if (!fBase->isInGraph())
		throw std::invalid_argument("TGeoidHeightRefFrame: the base reference frame " + fBase->getName() + " must be in the graph");

	if (dynamic_cast<TGeodeticRefFrame *>(fBase) != nullptr)
		fHeightCoordSys = TCoordSysFactory::kGeodetic;
	else if (dynamic_cast<TA2DPlus1MapProjection *>(fBase) != nullptr)
		fHeightCoordSys = TCoordSysFactory::k2DPlusH;
	else
		throw std::invalid_argument("TGeoidHeightRefFrame: the base reference frame " + fBase->getName()
			+ " must be a geodetic reference frame or a 2D+1 projection");

	if (dynamic_cast<TGeodeticRefFrame *>(fGeoid->getDefRefFrame()) == nullptr)
		throw std::invalid_argument("TGeoidHeightRefFrame: the definition reference frame of geoid " + fGeoid->getName() + " must be geodetic");
}

TGeoidHeightRefFrame::~TGeoidHeightRefFrame()
{
}

std::string TGeoidHeightRefFrame::buildName(TAReferenceFrame *base, TAGeoidModel *geoid)
{
	if (base == nullptr || geoid == nullptr)
		throw std::invalid_argument("TGeoidHeightRefFrame: base reference frame and geoid must not be null");

	// The name must be unique: TRefFrameWrapper compares the frames by name
	return base->getName() + " / " + geoid->getName();
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////

TGeodeticRefFrame *TGeoidHeightRefFrame::getGeodeticRF() const
{
	return fBase->getGeodeticRF();
}

TARefFrameTransformation *TGeoidHeightRefFrame::getRFTransfo2CGRF()
{
	if (!fToBase)
		fToBase.reset(new TGeoidHeightTransformation(this, TGeoidHeightTransformation::kHeightToEllipsoidal));

	return fToBase.get();
}

//////////////////////////////////////////////////////////////////////
// Data extraction methods
//////////////////////////////////////////////////////////////////////

TPositionVector TGeoidHeightRefFrame::getCoordinates(const TSpatialPosition *sp, TCoordSysFactory::ECoordSys coordsys) const
{
	if (coordsys != fHeightCoordSys)
		throw std::invalid_argument("Reference frame " + getName() + " only supports coordinates with heights above the geoid ("
			+ (fHeightCoordSys == TCoordSysFactory::kGeodetic ? "kGeodetic" : "k2DPlusH") + ")");

	return getPositionVector(sp);
}

TFreeVector TGeoidHeightRefFrame::getElements(const TSpatialVector *sv, TCoordSysFactory::ECoordSys coordsys) const
{
	TFreeVector fv(fHeightCoordSys);
	if (coordsys == fHeightCoordSys)
		fv = getVector(sv);
	return fv;
}

TRotationMatrix TGeoidHeightRefFrame::getElements(const TSpatialOrientation *so, TCoordSysFactory::ECoordSys coordsys) const
{
	TRotationMatrix rm;
	if (coordsys == fHeightCoordSys)
		rm = getOrientation(so);
	return rm;
}

//////////////////////////////////////////////////////////////////////
// Settings methods
//////////////////////////////////////////////////////////////////////

bool TGeoidHeightRefFrame::setCoordinates(TSpatialPosition *sp, const TPositionVector &pv)
{
	if (pv.getCoordSys() != fHeightCoordSys)
		return false;

	return setPositionVector(sp, pv);
}

bool TGeoidHeightRefFrame::setElements(TSpatialVector *sv, const TFreeVector &fv)
{
	return setVector(sv, fv);
}

bool TGeoidHeightRefFrame::setElements(TSpatialOrientation *so, const TRotationMatrix &rm)
{
	return setOrientation(so, rm);
}

//////////////////////////////////////////////////////////////////////
//END
//////////////////////////////////////////////////////////////////////
