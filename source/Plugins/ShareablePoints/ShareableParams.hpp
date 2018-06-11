/*
© Copyright CERN 2000-2018. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SHAREABLEPARAMS_HPP
#define SHAREABLEPARAMS_HPP

#include "ShareableExtraInfo.hpp"
#include "TCoordSysFactory.h"

struct ShareableParams
{
	int _precision = 6;
	TCoordSysFactory::ECoordSys _coordsys = TCoordSysFactory::ECoordSys::k3DCartesian;
	ShareableExtraInfos _extraInfos;
};

#endif // SHAREABLEPARAMS_HPP
