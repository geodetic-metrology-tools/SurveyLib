# set include directories needed by this library
include_directories(${SURVEYLIB_ROOT}/source/SpatialObjects/headers/AffineTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/MathematicalConcepts
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/ReferenceSurfaces
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/RefFrameTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/ShortestPath
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/SpatialObj
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/SpatialSystems
					${SURVEYLIB_ROOT}/source/SpatialObjDLL/headers)

# Create a variable containing all .cpp files:
set(SpatialObjDLL_SOURCES 
	sources/SpatialObjCFns.cpp
)

# Create a variable containing all .h files:
set(SpatialObjDLL_HEADERS 
	headers/SpatialObjCFns.h
	headers/TGlobalDefs.h
)

# Create a dynamic library from sources:
add_library(SpatialObjDLL SHARED ${SpatialObjDLL_SOURCES} ${SpatialObjDLL_HEADERS})

# Specify the libraries to link against
target_link_libraries (SpatialObjDLL
	ProjectFramework
	SpatialObjects
)

# needed for linux compilation
set_target_properties(SpatialObjDLL PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Define IDE folders:
set_target_properties(SpatialObjDLL PROPERTIES FOLDER "SurveyLib")
