# set include directories needed by this library
include_directories(${SURVEYLIB_ROOT}/source/SpatialObjects/MathematicalConcepts
					${SURVEYLIB_ROOT}/source/SpatialObjects/ReferenceSurfaces
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialSystems
					${SURVEYLIB_ROOT}/source/SpatialObjects/RefFrameTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialObj
					${SURVEYLIB_ROOT}/source/SpatialObjects/AffineTransformations)

# Create a variable containing all .cpp files:
set(ShortestPath_SOURCES 
	TGraph.cpp
	TLocalSystemOrigin.cpp
	TRefFrameInfo.cpp
	TRefFrameWrapper.cpp
	TRefSystemFactory.cpp
	TTransformWrapper.cpp
	TCoordSysInfo.cpp
	TAngularUnitsInfo.cpp
)

# Create a variable containing all .h files:
set(ShortestPath_HEADERS 
	DynamicPriorityQueue.h
	PtrGreater.h
	TGraph.h
	TLocalSystemOrigin.h
	TRefFrameInfo.h
	TRefFrameWrapper.h
	TRefSystemFactory.h
	TTransformWrapper.h
	TNotInGraphException.h
	TCoordSysInfo.h
	TAngularUnitsInfo.h
)

# Create a static library from sources:
add_library(ShortestPath STATIC ${ShortestPath_SOURCES} ${ShortestPath_HEADERS})