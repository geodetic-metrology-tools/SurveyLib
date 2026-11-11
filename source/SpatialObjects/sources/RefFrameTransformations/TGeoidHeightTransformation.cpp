// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

//  TGeoidHeightTransformation.cpp

#include "TGeoidHeightTransformation.h"

#include <stdexcept>

#include "TAGeoidModel.h"
#include "TGeoidHeightRefFrame.h"
#include "TPositionVector.h"
#include "TSpatialPosition.h"

namespace
{
/*! Express a spatial position in the given frame.
	\throw std::runtime_error if the transformation fails */
void transformOrThrow(TSpatialPosition &position, TAReferenceFrame *to)
{
	if (!position.transform(to))
		throw std::runtime_error("TGeoidHeightTransformation: unable to transform position from " + position.getRefFrame()->getName() + " to " + to->getName());
}
} // namespace

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TGeoidHeightTransformation::TGeoidHeightTransformation(TGeoidHeightRefFrame *frame, EDirection direction) : fFrame(frame), fDirection(direction)
{
	if (fFrame == nullptr)
		throw std::invalid_argument("TGeoidHeightTransformation: the geoid height reference frame must not be null");
}

TGeoidHeightTransformation::~TGeoidHeightTransformation()
{
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////

TGeoidHeightTransformation *TGeoidHeightTransformation::clone() const
{
	return new TGeoidHeightTransformation(fFrame, fDirection);
}

TARefFrameTransformation *TGeoidHeightTransformation::inverse() const
{
	return new TGeoidHeightTransformation(fFrame, fDirection == kHeightToEllipsoidal ? kEllipsoidalToHeight : kHeightToEllipsoidal);
}

TAReferenceFrame *TGeoidHeightTransformation::getSourceFrame() const
{
	return fDirection == kHeightToEllipsoidal ? static_cast<TAReferenceFrame *>(fFrame) : fFrame->getBaseRF();
}

TAReferenceFrame *TGeoidHeightTransformation::getDestinationFrame() const
{
	return fDirection == kHeightToEllipsoidal ? fFrame->getBaseRF() : static_cast<TAReferenceFrame *>(fFrame);
}

bool TGeoidHeightTransformation::transform(TPositionVector &pv) const
{
	TAReferenceFrame *base = fFrame->getBaseRF();
	TAGeoidModel *geoid = fFrame->getGeoid();
	TAReferenceFrame *geoidRF = geoid->getDefRefFrame(); // N is given w.r.t. this frame and its ellipsoid
	const TCoordSysFactory::ECoordSys heightCoordSys = fFrame->getHeightCoordSys();

	if (fDirection == kHeightToEllipsoidal)
	{
		// pv is given in the geoid height frame: (horizontal, H)
		const TLength H = pv.getH();

		// Horizontal position of the point, using H as an approximation of h.
		// The influence of the height on the horizontal position is negligible for N computation.
		TSpatialPosition position(base);
		position.setCoordinates(pv);
		transformOrThrow(position, geoidRF);

		const TLength N = geoid->getN(position);

		if (geoidRF == base)
		{
			pv.setH(TLength(H + N));
			return true;
		}

		// h = H + N in the geoid definition frame, then back to the base frame to get the base ellipsoidal height
		TPositionVector geodetic = position.getCoordinates(TCoordSysFactory::kGeodetic);
		geodetic.setH(TLength(H + N));
		position.setCoordinates(geodetic);
		transformOrThrow(position, base);

		// keep the horizontal coordinates given by the user, only the height is changed
		pv.setH(position.getCoordinates(heightCoordSys).getH());
		return true;
	}
	else
	{
		// pv is given in the base frame, in any coordinate system supported by the base frame
		TSpatialPosition position(base);
		position.setCoordinates(pv);
		TPositionVector result = position.getCoordinates(heightCoordSys);

		transformOrThrow(position, geoidRF);
		const TLength N = geoid->getN(position);

		// ellipsoidal height with respect to the geoid definition ellipsoid
		const TLength h = (geoidRF == base) ? result.getH() : position.getCoordinates(TCoordSysFactory::kGeodetic).getH();

		result.setH(TLength(h - N));
		pv = result;
		return true;
	}
}

//////////////////////////////////////////////////////////////////////
//END
//////////////////////////////////////////////////////////////////////
