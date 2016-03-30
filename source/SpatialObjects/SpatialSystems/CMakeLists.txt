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
	TSpatialOrientation.cpp
	TSpatialPosition.cpp
	TSpatialStatus.cpp
	TSpatialVector.cpp
)

# Create a variable containing all .h files:
set(SpatialSystems_HEADERS
	counted_ptr.h
	TASpatialAttribute.h
	TSpatialOrientation.h
	TSpatialPosition.h
	TSpatialStatus.h
	TSpatialVector.h
)

# Create a static library from sources:
add_library(SpatialSystems STATIC ${SpatialSystems_SOURCES} ${SpatialSystems_HEADERS})

# needed for linux compilation
set_target_properties(SpatialSystems PROPERTIES POSITION_INDEPENDENT_CODE ON)
