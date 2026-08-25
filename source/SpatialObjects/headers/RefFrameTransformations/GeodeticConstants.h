/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef GeodeticConstants_H
#define GeodeticConstants_H
/*!
   \ingroup ConstantsDefaults
   @{

/*!@name P0 false coordinates*/
//@{
	/// in [m]
	static const double XP0 = 00.00000;
	/// in [m]
	static const double YP0 = 0.0;
	/// in [m]
	static const double ZP0 = 0.000;
	/// in [m]
	static const double Zoffset = 0.0;
	//@}

/*!@name Geodetic ellipsoidal coordinates of P0 and azimuth. */
//@{
	/// in [gon]
	static const double PHIP0 = 51.3999292503;
	/// in [gon]
	static const double LambdaP0 = 6.7285948569;
	/// in [m]
	static const double HP0 = 509.58316;
	/// in [gon]
	static const double AzimuthCCSYaxis = 0.0; 
//@}

/*!@name GRS80 ellipsoid definition. */
//@{
	/// in [m]
	static const double SemiMajorAxisGRS80 = 6378137.0;
	/// in [m]
	static const double SemiMinorAxisGRS80 = 6356752.314140;
	static const double eccentrGRS80 = 0.0066943800229;
//@}

/*!@name Sphere definition. */
//@{
	static const double sphereRadius = 6371000.0;

//@}
/*! @} End of Doxygen Groups*/
#endif
