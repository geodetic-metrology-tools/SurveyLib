# set include directories needed by this library
include_directories(${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialObj)

# Create a variable containing all .cpp files:
set(SpatialMeasurments_SOURCES 
	TAInstrumentStation.cpp
)

# Create a variable containing all .h files:
set(SpatialMeasurments_HEADERS 
	TAInstrumentStation.h
	TAngleConstants.h
	TDistConstants.h
)

# Create a static library from sources:
add_library(SpatialMeasurments STATIC ${SpatialMeasurments_SOURCES} ${SpatialMeasurments_HEADERS})