// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TLocalRFWithTransformationMatrix.h"
#include <filesystem>

///////////////////////////////////////
// constructor
////////////////////////////////////////
TLocalRFWithTransformationMatrix::TLocalRFWithTransformationMatrix(const std::string &name, const std::string &pathToTransformationMatrix) :
	T3DLocalRefFrame(name), fPathToTransformationMatrix(pathToTransformationMatrix)
{
}

///////////////////////////////////////
// destructor
////////////////////////////////////////
TLocalRFWithTransformationMatrix::~TLocalRFWithTransformationMatrix()
{
}

void TLocalRFWithTransformationMatrix::setPathToTransformationMatrix(const std::string &pathToTransformationMatrix)
{
	std::filesystem::path p(pathToTransformationMatrix);
	fPathToTransformationMatrix = p.generic_string();
}
