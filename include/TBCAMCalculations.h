#ifndef _TBCAMCALCULATIONS_H_
#define _TBCAMCALCULATIONS_H_

#include "TPositionVector.h"
#include "TRotationMatrix.h"
#include "TBCAMCalibrationDB.h"

class TBCAMCalculations {
	public:
		/* constructs a BCAM transformation object
		   based on three sphere coordinates that define
		   the BCAM mount system. All ext-transformations
		   lead from or to the system in which the spheres are defined.
		 */
		explicit TBCAMCalculations(const TPositionVector& cone,
								   const TPositionVector& slot,
								   const TPositionVector& plane);
		
		TPositionVector& extToBCAM(TPositionVector& p);
		TPositionVector& BCAMToExt(TPositionVector& p);	

		void BCAMToImage(TReal dst[2], const TPositionVector& p, 
			             const TBCAMCalibrationDB::DBEntry& cam);
		TPositionVector imageToBCAM(TReal img[2], const TBCAMCalibrationDB::DBEntry& cam);

		// The point must be given in the system of the mounting balls that define this object
		TPositionVector& projectPoint(TReal dst[2], const TPositionVector& p, 
			                          const TBCAMCalibrationDB::DBEntry& cam);

	private:
		TRotationMatrix mm; // Mount Matrix
		TFreeVector mv; // Mount Vector
};

#endif