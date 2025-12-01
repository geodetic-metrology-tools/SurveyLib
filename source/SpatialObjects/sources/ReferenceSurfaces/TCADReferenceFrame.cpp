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
