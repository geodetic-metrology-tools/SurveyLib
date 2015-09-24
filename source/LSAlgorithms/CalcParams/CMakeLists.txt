# Create a variable containing all .cpp files:
SET(CalcParams_SOURCES 
	TLSCalcFreeVectorParam.cpp
	TLSCalcLengthParam.cpp
	TLSCalcOrientationParam.cpp
	TLSCalcPosVectorParam.cpp
	TLSCalcScalarParam.cpp
	TLSCalcWorkingPosVec.cpp
)

# Create a variable containing all .h files:
SET(CalcParams_HEADERS 
	TLSCalcFreeVectorParam.h
	TLSCalcLengthParam.h
	TLSCalcOrientationParam.h
	TLSCalcPosVectorParam.h
	TLSCalcScalarParam.h
	TLSCalcWorkingPosVec.h
)

#Create a static library from the object files
ADD_LIBRARY(CalcParams STATIC ${CalcParams_SOURCES} ${CalcParams_HEADERS})