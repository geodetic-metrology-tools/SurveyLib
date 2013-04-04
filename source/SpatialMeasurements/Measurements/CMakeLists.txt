# Create a variable containing all .cpp files:
set(Measurements_SOURCES 
	T2DOffsetMeasurement.cpp
	TALineMeasurement.cpp
	TAMeasurement.cpp
	TAMeasurementListener.cpp
	TAObjectMeasurement.cpp
	TAPlaneMeasurement.cpp	
	TAPointMeasurement.cpp
	TATargetlessMeas.cpp
	THorAngleMeasurement.cpp
	THorizontalDistMeas.cpp
	TOffsetToSpaLineMeasurement.cpp
	TOffsetToTheoPlaneMeasurement.cpp
	TOffsetToVerLineMeasurement.cpp
	TOffsetToVerPlaneMeasurement.cpp
	TSpatialDistMeasurement.cpp
	TVerticalDistMeasurement.cpp
	TVMeasurementListener.cpp
	TWireToWireDistMeas.cpp
	TWPSMeasurement.cpp
	TZenithDistMeasurement.cpp
)

# Create a variable containing all .h files:
set(Measurements_HEADERS 
	${SURVEYLIB_INCLUDE_PATH}/T2DOffsetMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/TALineMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/TAMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/TAMeasurementListener.h
	${SURVEYLIB_INCLUDE_PATH}/TAObjectMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/TAPlaneMeasurement.h	
	${SURVEYLIB_INCLUDE_PATH}/TAPointMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/TATargetlessMeas.h
	${SURVEYLIB_INCLUDE_PATH}/THorAngleMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/THorizontalDistMeas.h
	${SURVEYLIB_INCLUDE_PATH}/TOffsetToSpaLineMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/TOffsetToTheoPlaneMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/TOffsetToVerLineMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/TOffsetToVerPlaneMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/TSpatialDistMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/TVerticalDistMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/TVMeasurementListener.h
	${SURVEYLIB_INCLUDE_PATH}/TWireToWireDistMeas.h
	${SURVEYLIB_INCLUDE_PATH}/TWPSMeasurement.h
	${SURVEYLIB_INCLUDE_PATH}/TZenithDistMeasurement.h
)

# Create a static library from sources:
add_library(Measurements STATIC ${Measurements_SOURCES} ${Measurements_HEADERS})
install(FILES ${Measurements_HEADERS} DESTINATION ${INSTALL_PREFIX}/include)