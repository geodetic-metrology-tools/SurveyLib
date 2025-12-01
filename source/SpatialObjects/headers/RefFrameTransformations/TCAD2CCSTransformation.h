/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

// TCAD2CCSTransformation.h

#ifndef SU_CAD_2_CCS
#define SU_CAD_2_CCS

#if _MSC_VER >= 1000
#	pragma once
#endif

#include "THelmertRefFrameTransform.h"
#include "TSpatialPosition.h"
#include "TCADReferenceFrame.h"
#include <TScaleFactor.h>
#include <TRotation.h>
#include <TTranslation.h>


/*!\ingroup spatialobjects
	@{*/

//! The definition of the transformation between a CAD system and the CCS
class TCAD2CCSTransformation : public THelmertRefFrameTransform //: public TObject
{
public:
	/**@name Constructors and Destructors */
	//@{
	/// Default Constructor
	TCAD2CCSTransformation(TAReferenceFrame *from, TAReferenceFrame *to, const TScaleFactor &, const TRotation &, const TTranslation &);

	/// Constructor taking the path to the transformation matrix
	TCAD2CCSTransformation(TAReferenceFrame *from, TAReferenceFrame *to, std::string pathToTransformationMatrix);

	THelmertTransformation setMatrixFromTRSFfile(std::string pathToTransformationMatrix) const;

	std::string getPathToTransformationMatrix() { return fPathToTransformationMatrix; };

	/// transform a position vector
	virtual bool transform(TPositionVector &pv) const;

private:
	void checkAfterReadingInputFile(const std::vector<std::vector<double>> &rows, const std::string &pathToTransformationMatrix) const;

	std::string fPathToTransformationMatrix = "";
};
/*@}*/

#endif // SU_CAD_2_CCS
