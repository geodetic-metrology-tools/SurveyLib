# Setting the include path - to include a given directory
include_directories (
	.
	${SURVEYLIB_INCLUDE_PATH}
)




##### This will correspond to one VS project!

# Create a variable containing all .cpp files:
set(Measurements_SOURCES 
	TAMeasurement.cpp
	TAPointMeasurement.cpp
	THorAngleMeasurement.cpp
	TOffsetToLineOrPlaneMeasurement.cpp
	TOffsetToTheoPlaneMeasurement.cpp
	TSpatialDistMeasurement.cpp
	TVerticalDistMeasurement.cpp
	TZenithDistMeasurement.cpp
)

# Create a variable containing all .h files:
set(Measurements_HEADERS 
	${SURVEYLIB_INCLUDE_PATH}/LevelMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/PolarMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/TAMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/TAPointMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/THorAngleMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/THorizontalDistMeas.h
	${SURVEYLIB_INCLUDE_PATH}/TOffsetToLineOrPlaneMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/TOffsetToTheoPlaneMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/TSpatialDistMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/TVerticalDistMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/TZenithDistMeasurement.h
)

# Create a static library from sources:
add_library(Measurements STATIC ${Measurements_SOURCES} ${Measurements_HEADERS})
install(FILES ${Measurements_HEADERS} DESTINATION ${INSTALL_PREFIX}/include)
#####