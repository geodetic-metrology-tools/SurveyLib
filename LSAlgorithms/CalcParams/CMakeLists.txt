# Setting the include path - to include a given directory
include_directories (
	.
	${SURVEYLIB_INCLUDE_PATH}
	${NAGC_INCLUDE_PATH}
)




##### This will correspond to one VS project!

# Create a variable containing all .cpp files:
set(CalcParams_SOURCES 
	TLSCalcFreeVectorParam.cpp
	TLSCalcLengthParam.cpp
	TLSCalcOrientationParam.cpp
	TLSCalcPosVectorParam.cpp
	TLSCalcScalarParam.cpp
	TLSCalcWorkingPosVec.cpp
)

# Create a variable containing all .h files:
set(CalcParams_HEADERS 
	${SURVEYLIB_INCLUDE_PATH}/TLSCalcFreeVectorParam.h
	${SURVEYLIB_INCLUDE_PATH}/TLSCalcLengthParam.h
	${SURVEYLIB_INCLUDE_PATH}/TLSCalcOrientationParam.h
	${SURVEYLIB_INCLUDE_PATH}/TLSCalcPosVectorParam.h
	${SURVEYLIB_INCLUDE_PATH}/TLSCalcScalarParam.h
	${SURVEYLIB_INCLUDE_PATH}/TLSCalcWorkingPosVec.h
	${SURVEYLIB_INCLUDE_PATH}/TLSCalcWorkingUnknown.h
)

# Create a static library from sources:
add_library(CalcParams STATIC ${CalcParams_SOURCES} ${CalcParams_HEADERS})
install(FILES ${CalcParams_HEADERS} DESTINATION ${INSTALL_PREFIX}/include)
#####