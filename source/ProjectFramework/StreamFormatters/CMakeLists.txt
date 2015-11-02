CMAKE_POLICY(SET CMP0022 NEW)
CMAKE_POLICY(SET CMP0038 NEW)

# set include directories needed by this library
include_directories(${SURVEYLIB_ROOT}/source/SpatialObjects/ReferenceSurfaces
					${SURVEYLIB_ROOT}/source/SpatialObjects/MathematicalConcepts
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialObj
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialSystems
					${SURVEYLIB_ROOT}/source/SpatialObjects/ShortestPath
					${SURVEYLIB_ROOT}/source/SpatialObjects/AffineTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/RefFrameTransformations
					${SURVEYLIB_ROOT}/source/ProjectFramework/Converters
					${SURVEYLIB_ROOT}/source/ProjectFramework/FiltersAndFormats
					${SURVEYLIB_ROOT}/source/ProjectFramework/ProjectData)
					

# Create a variable containing all .cpp files:
set(StreamFormatters_SOURCES
	TAStreamFormatter.cpp
	TFixedColFormatTStream.cpp
	TSeparatedFormatTStream.cpp
	TStreamFormatterFactory.cpp
)

# Create a variable containing all .h files:
set(StreamFormatters_HEADERS 
	TAStreamFormatter.h
	TFixedColFormatTStream.h
	TSeparatedFormatTStream.h
	TStreamFormatterFactory.h
)

# Create a static library from sources:
add_library(StreamFormatters STATIC ${StreamFormatters_SOURCES} ${StreamFormatters_HEADERS})

#link used libraries
target_link_libraries(StreamFormatters ${PROJECTFRAMEWORK_LIBRARIES} ${SPATIAL_LIBRARIES})