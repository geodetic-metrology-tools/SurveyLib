/*
© Copyright CERN 2000-2018. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SHAREABLEPARAMS_HPP
#define SHAREABLEPARAMS_HPP

#include "ShareableExtraInfo.hpp"
#include "TCoordSysFactory.h"

/**
 * Parameters for the shareable list of points.
 *
 * ShareableParams is part of the @ref shpoints module.
 * @ingroup shpoints
 *
 * This stores the parameters for the ShareablePointsList tree. Basic parameters are the precision and the coordinate system used.
 *
 * If any other parameters are available, they can be added in the `extraInfos` ShareableExtraInfos.
 *
 * @see shpoints, ShareablePointsList
 */
struct ShareableParams
{
	/** The precision of the floating values (by default 6 floating digits). */
	int precision = 6;
	/**
	 * The coordinate system used (by default 3D cartesian).
	 * @see TCoordSysFactory::ECoordSys
	 */
	TCoordSysFactory::ECoordSys coordsys = TCoordSysFactory::ECoordSys::k3DCartesian;
	/** Some optional extra information. */
	ShareableExtraInfos extraInfos;
};

#endif // SHAREABLEPARAMS_HPP
