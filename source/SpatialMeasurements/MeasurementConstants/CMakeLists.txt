# Create a variable containing all .cpp files:
set(MeasurementConstants_SOURCES 
	TAngleConstants.cpp
	TDistConstants.cpp
)

# Create a variable containing all .h files:
set(MeasurementConstants_HEADERS 
	${SURVEYLIB_INCLUDE_PATH}/TAngleConstants.h
	${SURVEYLIB_INCLUDE_PATH}/TDistConstants.h
)

# Create a static library from sources:
add_library(MeasurementConstants STATIC ${MeasurementConstants_SOURCES} ${MeasurementConstants_HEADERS})
#install(FILES ${MeasurementConstants_HEADERS} DESTINATION ${INSTALL_PREFIX}/include)
#####