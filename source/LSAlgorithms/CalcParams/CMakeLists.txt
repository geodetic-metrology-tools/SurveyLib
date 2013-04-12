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
	${SURVEYLIB_INCLUDE_PATH}/TLSCalcFreeVectorParam.h
	${SURVEYLIB_INCLUDE_PATH}/TLSCalcLengthParam.h
	${SURVEYLIB_INCLUDE_PATH}/TLSCalcOrientationParam.h
	${SURVEYLIB_INCLUDE_PATH}/TLSCalcPosVectorParam.h
	${SURVEYLIB_INCLUDE_PATH}/TLSCalcScalarParam.h
	${SURVEYLIB_INCLUDE_PATH}/TLSCalcWorkingPosVec.h
	${SURVEYLIB_INCLUDE_PATH}/TLSCalcWorkingUnknown.h
)

#Create a static library from the object files
ADD_LIBRARY(CalcParams STATIC ${CalcParams_SOURCES} ${CalcParams_HEADERS})

# Install the header files to the given destination
#install(FILES ${CalcParams_HEADERS} DESTINATION ${INSTALL_PREFIX}/include)
#####