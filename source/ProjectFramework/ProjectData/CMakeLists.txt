CMAKE_POLICY(SET CMP0038 NEW)

# set include directories needed by this library
include_directories(${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialObj
					${SURVEYLIB_ROOT}/source/SpatialObjects/ReferenceSurfaces
					${SURVEYLIB_ROOT}/source/SpatialObjects/MathematicalConcepts
					${SURVEYLIB_ROOT}/source/SpatialObjects/ShortestPath
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialSystems
					${SURVEYLIB_ROOT}/source/SpatialObjects/AffineTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/RefFrameTransformations
					${SURVEYLIB_ROOT}/source/ProjectFramework/StreamFormatters
					${SURVEYLIB_ROOT}/source/ProjectFramework/Converters)

# Create a variable containing all .cpp files:
set(ProjectData_SOURCES 
	TADataSet.cpp
	TDataParameters.cpp
	TFileParameters.cpp
	TPtListBroadcaster.cpp
	TWorkingPoints.cpp
)

# Create a variable containing all .h files:
set(ProjectData_HEADERS 
	TADataSet.h
	TDataParameters.h
	TFileParameters.h
	TPtListBroadcaster.h
	TVPtListListener.h
	TWorkingPoints.h
)

# Create a static library from sources:
add_library(ProjectData STATIC ${ProjectData_SOURCES} ${ProjectData_HEADERS})

#link used libraries
#target_link_libraries(ProjectData ${PROJECTFRAMEWORK_LIBRARIES} ${SPATIAL_LIBRARIES})