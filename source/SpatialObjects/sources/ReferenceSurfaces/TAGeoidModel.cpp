// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TAGeoidModel.h"

/////////////////////////////////////////////////////////////////////////////////////////////
//CONSTRUCTOR / DESTRUCTOR
/////////////////////////////////////////////////////////////////////////////////////////////
TAGeoidModel::TAGeoidModel() : fName(""), fDefRFPtr(nullptr), fDefEllPtr(nullptr), fCalcRFPtr(nullptr), fGeoidId(TRefSystemFactory::EGeoid::kNoGeoid)
{//Default constructor
}

TAGeoidModel::TAGeoidModel(const std::string &name, const TRefSystemFactory::EGeoid &geoidId, TAReferenceFrame *def, TReferenceEllipsoid *ell, TAReferenceFrame *calc):
	fName(name), fDefRFPtr(def), fDefEllPtr(ell), fCalcRFPtr(calc), fGeoidId(geoidId)
{
}

TAGeoidModel::~TAGeoidModel()
{//Destructor
}

TAngle TAGeoidModel::getDAlpha(const TSpatialPosition& sp) const
{
	// deep copy of TSpatialPosition and ensure the reference frame is the same as the geoid DefinitionRF
	TSpatialPosition position = getSpatialPositionInRefFrame(sp, fDefRFPtr);
	TAngle latitude = position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid();

	return getDAlpha(position, latitude);

}

TSpatialPosition TAGeoidModel::getSpatialPositionInRefFrame(const TSpatialPosition &sp, TAReferenceFrame* refFrame) const
{
	// deep copy of TSpatialPosition
	TSpatialPosition position(sp);

	// RF of TSpatialPosition must be the same as the given reference frame
	if (position.getRefFrame() != refFrame)
	{
		position.transform(refFrame);
	}

	return position;
}

TAngle TAGeoidModel::computeLaplaceCorrection(const TSpatialPosition &position, const TAngle &latitude) const
{
	TReal phi = latitude.getRadiansValue();
	TAngle eta, fDAlphaValue;
	eta = getEta(position);
	fDAlphaValue = eta * tanq(phi);
	return fDAlphaValue;
}
////////////////////////////////////////////////////////////////////////////////////////////
//END
////////////////////////////////////////////////////////////////////////////////////////////
