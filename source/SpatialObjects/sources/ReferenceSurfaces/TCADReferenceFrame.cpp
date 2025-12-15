// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TCADReferenceFrame.h"

///////////////////////////////////////
// constructor
////////////////////////////////////////
TCADReferenceFrame::TCADReferenceFrame(const std::string &name, const std::string &pathToTransformationMatrix) :
	T3DLocalRefFrame(name), fPathToTransformationMatrix(pathToTransformationMatrix)
{
}

///////////////////////////////////////
// destructor
////////////////////////////////////////
TCADReferenceFrame::~TCADReferenceFrame()
{
}
