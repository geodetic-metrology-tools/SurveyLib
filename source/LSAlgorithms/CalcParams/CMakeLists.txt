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
	${SURVEYLIB_INCLUDE_PATH}/lsalgo/TLSCalcFreeVectorParam.h
	${SURVEYLIB_INCLUDE_PATH}/lsalgo/TLSCalcLengthParam.h
	${SURVEYLIB_INCLUDE_PATH}/lsalgo/TLSCalcOrientationParam.h
	${SURVEYLIB_INCLUDE_PATH}/lsalgo/TLSCalcPosVectorParam.h
	${SURVEYLIB_INCLUDE_PATH}/lsalgo/TLSCalcScalarParam.h
	${SURVEYLIB_INCLUDE_PATH}/lsalgo/TLSCalcWorkingPosVec.h
	${SURVEYLIB_INCLUDE_PATH}/lsalgo/TLSCalcWorkingUnknown.h
)

#Create a static library from the object files
ADD_LIBRARY(CalcParams STATIC ${CalcParams_SOURCES} ${CalcParams_HEADERS})
#####