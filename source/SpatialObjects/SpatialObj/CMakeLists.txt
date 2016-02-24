# set include directories needed by this library
include_directories(${SURVEYLIB_ROOT}/source/SpatialObjects/AffineTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/MathematicalConcepts
					${SURVEYLIB_ROOT}/source/SpatialObjects/ReferenceSurfaces
					${SURVEYLIB_ROOT}/source/SpatialObjects/RefFrameTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/ShortestPath
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialObj
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialSystems)

# Create a variable containing all .cpp files:
set(SpatialObj_SOURCES 
	#SpatialObjCFns.cpp
	SpatialObjFns.cpp
	TASpatialPtListener.cpp
	TSpatialLine.cpp
	TSpatialLineName.cpp
	TSpatialPlane.cpp
	TSpatialPlaneName.cpp
	TSpatialPoint.cpp
	TSpatialPointName.cpp
	TVSpatialPtListener.cpp
)

# Create a variable containing all .h files:
set(SpatialObj_HEADERS 
	#SpatialObjCFns.h
	SpatialObjFns.h
	TASpatialPtListener.h
	#TGlobalDefs.h
	TPtrWrapper.h
	TSpatialLine.h
	TSpatialLineName.h
	TSpatialPlane.h
	TSpatialPlaneName.h
	TSpatialPoint.h
	TSpatialPointName.h
	TVSpatialPtListener.h
)

# Create a static library from sources:
add_library(SpatialObj STATIC ${SpatialObj_SOURCES} ${SpatialObj_HEADERS})