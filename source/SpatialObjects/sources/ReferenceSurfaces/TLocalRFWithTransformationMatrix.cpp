// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TLocalRFWithTransformationMatrix.h"

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
