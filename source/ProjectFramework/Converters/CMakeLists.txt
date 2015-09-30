# set include directories needed by this library
include_directories(${SURVEYLIB_ROOT}/source/SpatialObjects/MathematicalConcepts
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialObj
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialSystems
					${SURVEYLIB_ROOT}/source/SpatialObjects/ShortestPath
					${SURVEYLIB_ROOT}/source/SpatialObjects/ReferenceSurfaces
					${SURVEYLIB_ROOT}/source/SpatialObjects/AffineTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/RefFrameTransformations
					${SURVEYLIB_ROOT}/source/ProjectFramework/StreamFormatters
					${SURVEYLIB_ROOT}/source/LSAlgorithms/CalcParams
					${SURVEYLIB_ROOT}/source/LSAlgorithms/CalcElements)

# Create a variable containing all .cpp files:
set(Converters_SOURCES 
	TAConverter.cpp
	TObservationFormat.cpp
	TPointConverter.cpp
	TPointFormat.cpp
)

# Create a variable containing all .h files:
set(Converters_HEADERS 
	TAConverter.h
	TObservationFormat.h
	TPointConverter.h
	TPointFormat.h
)

# Create a static library from sources:
add_library(Converters STATIC ${Converters_SOURCES} ${Converters_HEADERS})