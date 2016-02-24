# set include directories needed by this library
include_directories(${SURVEYLIB_ROOT}/source/SpatialObjects/AffineTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/MathematicalConcepts
					${SURVEYLIB_ROOT}/source/SpatialObjects/ReferenceSurfaces
					${SURVEYLIB_ROOT}/source/SpatialObjects/RefFrameTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/ShortestPath
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialObj
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialSystems
					${SURVEYLIB_ROOT}/source/SpatialObjDLL)

# Create a variable containing all .cpp files:
set(SpatialObjDLL_SOURCES 
	SpatialObjCFns.cpp
)

# Create a variable containing all .h files:
set(SpatialObjDLL_HEADERS 
	SpatialObjCFns.h
	TGlobalDefs.h
)

# Create a dynamic library from sources:
add_library(SpatialObjDLL SHARED ${SpatialObjDLL_SOURCES} ${SpatialObjDLL_HEADERS})

# Specify the libraries to link against
target_link_libraries (SpatialObjDLL
	${PROJECTFRAMEWORK_LIBRARIES}
	${SPATIAL_LIBRARIES}
)