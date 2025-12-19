/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

// TLocal2CCSTransformation.h

#ifndef SU_LOCAL_2_CCS
#define SU_LOCAL_2_CCS

#if _MSC_VER >= 1000
#	pragma once
#endif

#include "THelmertRefFrameTransform.h"
#include "TSpatialPosition.h"
#include "TLocalRFWithTransformationMatrix.h"
#include <TScaleFactor.h>
#include <TRotation.h>
#include <TTranslation.h>


/*!\ingroup spatialobjects
	@{*/

//! The definition of the transformation between a local (usually CAD) system and the CCS
class TLocal2CCSTransformation : public THelmertRefFrameTransform //: public TObject
{
public:
	/**@name Constructors and Destructors */
	//@{
	/// Default Constructor
	TLocal2CCSTransformation(TAReferenceFrame *from, TAReferenceFrame *to, const TScaleFactor &, const TRotation &, const TTranslation &);

	/// Constructor taking the path to the transformation matrix
	TLocal2CCSTransformation(TAReferenceFrame *from, TAReferenceFrame *to, std::string pathToTransformationMatrix, TLength::EUnits translationUnit);

	THelmertTransformation setMatrixFromFile(std::string pathToTransformationMatrix, TLength::EUnits translationUnit) const;

	std::string getPathToTransformationMatrix() { return fPathToTransformationMatrix; };

	/// transform a position vector
	virtual bool transform(TPositionVector &pv) const;

private:
	void checkAfterReadingInputFile(const std::vector<std::vector<double>> &rows, const std::string &pathToTransformationMatrix) const;

	TLength::EUnits fTranslationUnit = TLength::kMillimetres; // Default value is millimetres since translation in TRSF files is usually in mm
	std::string fPathToTransformationMatrix = "";
};
/*@}*/

#endif // SU_LOCAL_2_CCS
