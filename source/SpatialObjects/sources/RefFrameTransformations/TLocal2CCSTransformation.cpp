// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TLocal2CCSTransformation.h"
#include "THelmertTransformation.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <string>

TLocal2CCSTransformation::TLocal2CCSTransformation(TAReferenceFrame *from, TAReferenceFrame *to, const TScaleFactor &scaleFactor, const TRotation &rotation, const TTranslation &translation):
	THelmertRefFrameTransform(from, to, scaleFactor, rotation, translation)
{
}

TLocal2CCSTransformation::TLocal2CCSTransformation(TAReferenceFrame *from, TAReferenceFrame *to, std::string pathToTransformationMatrix, TLength::EUnits translationUnit) :
	fPathToTransformationMatrix(pathToTransformationMatrix), fTranslationUnit(translationUnit)
{
	// Initialize the transformation from file
	setSourceFrame(from);
	setDestinationFrame(to);
	setMatrixFromFile(pathToTransformationMatrix, translationUnit);
}

THelmertTransformation TLocal2CCSTransformation::setMatrixFromFile(std::string pathToTransformationMatrix, TLength::EUnits translationUnit) const
{
	std::ifstream ifs(pathToTransformationMatrix);
	if (!ifs.is_open()) {
		throw std::runtime_error("Cannot open TRSF file: " + pathToTransformationMatrix);
	}

	std::string line;
	std::vector<std::vector<double>> rows;
	while (std::getline(ifs, line)) {
		// trim leading/trailing whitespace simple check
		bool allSpace = true;
		for (char ch : line) { if (!std::isspace(static_cast<unsigned char>(ch))) { allSpace = false; break; } }
		if (allSpace) continue;

		std::istringstream iss(line);
		std::vector<double> vals;
		double v;
		while (iss >> v) vals.push_back(v);
		if (!vals.empty()) rows.push_back(std::move(vals));
	}

	checkAfterReadingInputFile(rows, pathToTransformationMatrix);

	// Fill rotation matrix row-major
	TRotationMatrix rotMat;
	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			rotMat.setC(r, c, rows[r][c]);
		}
	}

	// Create rotation
	TRotation rotation(rotMat);

	// Create translation from the 4th line values
	TLength tx((rows[3][0]), translationUnit);
	TLength ty((rows[3][1]), translationUnit);
	TLength tz((rows[3][2]), translationUnit);
	TTranslation translation(tx, ty, tz);

	// Use unit scale of 1.0
	TScaleFactor scale(1.0);

	// Return the helmert transform using the parsed components
	return THelmertTransformation(scale, rotation, translation);
}

void TLocal2CCSTransformation::checkAfterReadingInputFile(const std::vector<std::vector<double>> &rows, const std::string &pathToTransformationMatrix) const
{

	if (rows.size() < 4)
	{
		throw std::runtime_error("TRSF file must contain at least 4 non-empty lines (3 rotation rows + 1 translation row): " + pathToTransformationMatrix);
	}

	// Validate first 3 rows have at least 3 values, and the 4th has at least 3 values
	for (size_t r = 0; r < 3; ++r)
	{
		if (rows[r].size() < 3)
		{
			throw std::runtime_error("Rotation row " + std::to_string(r) + " does not contain 3 values in file: " + pathToTransformationMatrix);
		}
	}
	if (rows[3].size() < 3)
	{
		throw std::runtime_error("Translation row does not contain 3 values in file: " + pathToTransformationMatrix);
	}
}

bool TLocal2CCSTransformation::transform(TPositionVector &pv) const
{ // transform a position vector
	bool result = false;

	if (isInitialised())

		if (fFrom->getRefFrameId() == TRefSystemFactory::ERefFrame::kLocalRFin && fTo->getRefFrameId() == TRefSystemFactory::ERefFrame::kCCS)
		{
			auto *cad = dynamic_cast<TLocalRFWithTransformationMatrix *>(fFrom);
			result = setMatrixFromFile(cad->getPathToTransformationMatrix(), fTranslationUnit).transform(pv);
		}
		else if (fFrom->getRefFrameId() == TRefSystemFactory::ERefFrame::kCCS && fTo->getRefFrameId() == TRefSystemFactory::ERefFrame::kLocalRFout)
		{
			auto *cad = dynamic_cast<TLocalRFWithTransformationMatrix *>(fTo);
			result = setMatrixFromFile(cad->getPathToTransformationMatrix(), fTranslationUnit).transform(pv);
		}
		else
		{
			throw std::runtime_error("TLocal2CCSTransformation can only transform between CAD and CCS reference frames.");
		}

	return result;
}
