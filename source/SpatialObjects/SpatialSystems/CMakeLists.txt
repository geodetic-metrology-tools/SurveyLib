# set include directories needed by this library
include_directories(${SURVEYLIB_ROOT}/source/SpatialObjects/AffineTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/MathematicalConcepts
					${SURVEYLIB_ROOT}/source/SpatialObjects/ReferenceSurfaces
					${SURVEYLIB_ROOT}/source/SpatialObjects/RefFrameTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/ShortestPath
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialObj
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialSystems)

# Create a variable containing all .cpp files:
set(SpatialSystems_SOURCES 
	TASpatialAttribute.cpp
	#TPositionStatus.cpp
	TSpatialOrientation.cpp
	#TSpatialOrientationError.cpp
	TSpatialPosition.cpp
	#TSpatialPositionError.cpp
	TSpatialStatus.cpp
	TSpatialVector.cpp
	#TSpatialVectorError.cpp
	#TSpatialVectorStatus.cpp
)

# Create a variable containing all .h files:
set(SpatialSystems_HEADERS
	counted_ptr.h
	TASpatialAttribute.h
	#TPositionStatus.h
	TSpatialOrientation.h
	TSpatialPosition.h
	#TSpatialPositionError.h
	TSpatialStatus.h
	TSpatialVector.h
	#TSpatialVectorError.h
	#TSpatialVectorStatus.h
)

# Create a static library from sources:
add_library(SpatialSystems STATIC ${SpatialSystems_SOURCES} ${SpatialSystems_HEADERS})