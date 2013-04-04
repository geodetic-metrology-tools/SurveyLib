# Create a variable containing all .cpp files:
set(SpatialSystems_SOURCES 
	TASpatialAttribute.cpp
	TSpatialOrientation.cpp
	TSpatialPosition.cpp
	TSpatialStatus.cpp
	TSpatialVector.cpp
	
	# TSpatialOrientationError.cpp
	# TSpatialPositionError.cpp
	# TSpatialVectorError.cpp
)

# Create a variable containing all .h files:
set(SpatialSystems_HEADERS 
	${SURVEYLIB_INCLUDE_PATH}/counted_ptr.h
	${SURVEYLIB_INCLUDE_PATH}/TASpatialAttribute.h
	${SURVEYLIB_INCLUDE_PATH}/TSpatialOrientation.h
	${SURVEYLIB_INCLUDE_PATH}/TSpatialPosition.h
	${SURVEYLIB_INCLUDE_PATH}/TSpatialStatus.h
	${SURVEYLIB_INCLUDE_PATH}/TSpatialVector.h
	
	# ${SURVEYLIB_INCLUDE_PATH}/TSpatialOrientationError.h
	# ${SURVEYLIB_INCLUDE_PATH}/TSpatialPositionError.h
	# ${SURVEYLIB_INCLUDE_PATH}/TSpatialVectorError.h
)

# Create a static library from sources:
add_library(SpatialSystems STATIC ${SpatialSystems_SOURCES} ${SpatialSystems_HEADERS})
install(FILES ${SpatialSystems_HEADERS} DESTINATION ${INSTALL_PREFIX}/include)
#####