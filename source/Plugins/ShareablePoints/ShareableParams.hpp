// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿

#ifndef SHAREABLEPARAMS_HPP
#define SHAREABLEPARAMS_HPP

#include "ShareableExtraInfos.hpp"

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
	/**
	 * Different values for the used coordinate system.
	 *
	 * This enum is compatible with TCoordSysFactory::ECoordSys.
	 */
	enum ECoordSys
	{
		k3DCartesian = 1,
		kGeodetic = 2,
		k2DPlusH = 4,
		k2DCartesian = 8,
		kGeodeticSphere = 16,
		unknown = -1
	};

	/**
	 * @return a string representing the given ECoordSys.
	 * @throw std::ios_base::failure in case of error.
	 * @see coordsysFromString()
	 */
	static std::string coordsysToString(ECoordSys s)
	{
		switch (s)
		{
		case k3DCartesian:
			return "k3DCartesian";
		case kGeodetic:
			return "kGeodetic";
		case k2DPlusH:
			return "k2DPlusH";
		case k2DCartesian:
			return "k2DCartesian";
		case kGeodeticSphere:
			return "kGeodeticSphere";
		}
		return "unknown";
	}

	/**
	 * @return a ECoordSys from its string representation.
	 * @throw std::ios_base::failure in case of error.
	 * @see coordsysToString()
	 */
	static ECoordSys coordsysFromString(const std::string &s)
	{
		if (s == "k3DCartesian")
			return ECoordSys::k3DCartesian;
		if (s == "kGeodetic")
			return ECoordSys::kGeodetic;
		if (s == "k2DPlusH")
			return ECoordSys::k2DPlusH;
		if (s == "k2DCartesian")
			return ECoordSys::k2DCartesian;
		if (s == "kGeodeticSphere")
			return ECoordSys::kGeodeticSphere;
		return ECoordSys::unknown;
	}

	/** The precision of the floating values (by default 6 floating digits). */
	int precision = 6;
	/**
	 * The coordinate system used (by default 3D cartesian).
	 * @see TCoordSysFactory::ECoordSys
	 */
	ECoordSys coordsys = ECoordSys::k3DCartesian;
	/** Some optional extra information. */
	ShareableExtraInfos extraInfos;

	bool operator==(const ShareableParams &a) const noexcept { return precision == a.precision && coordsys == a.coordsys && extraInfos == a.extraInfos; }
	bool operator!=(const ShareableParams &a) const noexcept { return !(*this == a); }
};

#endif // SHAREABLEPARAMS_HPP
