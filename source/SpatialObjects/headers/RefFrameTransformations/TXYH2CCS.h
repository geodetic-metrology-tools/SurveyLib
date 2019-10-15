//  TXYHs2CCS.h
/*
© Copyright CERN 2000-2019. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/


#ifndef SU_XYHs_2_CCS
#define SU_XYHs_2_CCS

#include "TRefSystemFactory.h"

// TRefSystemFactory is used for transformation between XYHg and XYHe systems, using Geoid model defined in it. 

/*!
	\ingroup RefFrameTransformations
	\brief This class provide static methods for transformations between XYH systems and the CCS.

	\note For the transformation between XYHg and XYHe systems a Geoif model is used, which is defined in TRefSystemFactory.
*/
class  TXYH2CCS
{
public:
		static bool						XYHs2CCS( TPositionVector& pv );

		static bool						CCS2XYHs(TPositionVector& pv);

		static bool						XYHg2000Machine2CCS( TPositionVector& pv );

		static bool						CCS2XYHg2000Machine( TPositionVector& pv );

		static bool						XYHg1985Machine2CCS(TPositionVector& pv);

		static bool						CCS2XYHg1985Machine(TPositionVector& pv);



private:
		static bool						XYHe2CCS( TPositionVector& pv );

		static bool						CCS2XYHe( TPositionVector& pv );

		static bool						XYHg2XYHe( TPositionVector& pv, TRefSystemFactory::EGeoid geoid);

		static bool						XYHe2XYHg( TPositionVector& pv , TRefSystemFactory::EGeoid geoid);

};

#endif // TXYHs2CCS.h
