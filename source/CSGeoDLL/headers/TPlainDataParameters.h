/*
© Copyright CERN 2000-2022. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef CSGEODLL_T_PLAIN_DATA_PARAMETERS_H_b34c08fd435f4e4596bbdace8a678014
#define CSGEODLL_T_PLAIN_DATA_PARAMETERS_H_b34c08fd435f4e4596bbdace8a678014

#include <string>
#include <TConstants.h>

/**
 * POD version of TDataParameters
 *
 * This is a simplified variant of the TDataParameters that uses only
 * the POD (Plain-Old-Data) types. This is needed to pass the parameters
 * from other programming languages like C, Fortran or Java.
 */

/**
 * POD variant of the data about the local system origin.
 */
struct TPlainLocalSystemOrigin
{
    double fX;
    double fY;
    double fZ;
    double fGisement; /*!< in gons */
    double fSlope; /*!< in radians */
};

/**
 * POD structure for passing the information about the point needed for the
 * transformation.
 */
struct TPlainDataParameters
{
	int fRefFrame; /*!< Check TRefSystemFactory::ERefFrame for valid values */
	int fCoordSys; /*!< Check TCoordSysFactory::ECoordSys for valid values */
    int fAngUnits; /*!< Check TAngle::EUnits for valid values */
    double fEpoch = NO_VALf; /*!< Epoch of the coordinates in decimal years */
	const char *fSolution = ""; /*!< Specific solution for terrestrial reference frame */
};

#endif
