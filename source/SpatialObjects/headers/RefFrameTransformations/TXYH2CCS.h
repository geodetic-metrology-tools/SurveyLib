/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

//  TXYHs2CCS.h

#ifndef SU_XYHs_2_CCS
#define SU_XYHs_2_CCS

#include "TRefSystemFactory.h"
#include "TReferenceEllipsoid.h"

// TRefSystemFactory is used for transformation between XYHg and XYHe systems, using Geoid model defined in it.

/*!
	\ingroup RefFrameTransformations
	\brief This class provide static methods for transformations between XYH systems and the CCS.

	\note For the transformation between XYHg and XYHe systems a Geoid model is used, which is defined in TRefSystemFactory.
*/
class TXYH2CCS
{
public:
	static bool XYH2CCS(TPositionVector &pv, const TRefSystemFactory::EGeoid &geoid);

	static bool CCS2XYH(TPositionVector &pv, const TRefSystemFactory::EGeoid &geoid);

private:
	static bool XYHs2CCS(TPositionVector &pv);

	static bool CCS2XYHs(TPositionVector &pv);

	static bool XYHe2CCS(TPositionVector &pv, const	TReferenceEllipsoid* refEllipsoid);

	static bool CCS2XYHe(TPositionVector &pv, const TReferenceEllipsoid* refEllipsoid);

	static bool XYHg2XYHe(TPositionVector &pv, TRefSystemFactory::EGeoid geoid);

	static bool XYHe2XYHg(TPositionVector &pv, TRefSystemFactory::EGeoid geoid);

	static TReal calculateRhoAlpha(const TReal &dx, const TReal &dy, const TReferenceEllipsoid *refEllipsoid);

	static TLength getN(TPositionVector &pv, const TRefSystemFactory::EGeoid &geoid);
};

#endif // TXYHs2CCS.h
