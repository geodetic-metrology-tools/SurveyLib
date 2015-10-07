# set include directories needed by this library
include_directories(${SURVEYLIB_ROOT}/source/SpatialObjects/MathematicalConcepts
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialSystems
					${SURVEYLIB_ROOT}/source/SpatialObjects/ShortestPath
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialObj
					${SURVEYLIB_ROOT}/source/SpatialObjects/ReferenceSurfaces
					${SURVEYLIB_ROOT}/source/SpatialObjects/AffineTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/RefFrameTransformations
					${SURVEYLIB_ROOT}/source/ProjectFramework/Converters
					${SURVEYLIB_ROOT}/source/ProjectFramework/StreamFormatters)

# Create a variable containing all .cpp files:
set(FiltersAndFormats_SOURCES 
	T100MicroGonsFilter.cpp
	T2DPlusHFilter.cpp
	T3DCartesianFilter.cpp
	TCCsFilter.cpp
	TDMSFilter.cpp
	TGeodeticFilter.cpp
	TGonsFilter.cpp
	TKilometresFilter.cpp
	TLengthFilter.cpp
	TMetresFilter.cpp
	TMillimetresFilter.cpp
	TRadiansFilter.cpp
	# TWPS2DFilter.cpp
	# TWPSTFilter.cpp
	# TWPSVFilter.cpp
	# TWTW2DFilter.cpp
	# TWTWHFilter.cpp
	# TWTWVFilter.cpp
)

# Create a variable containing all .h files:
set(FiltersAndFormats_HEADERS 
	#setformat.h
	T100MicroGonsFilter.h
	T2DPlusHFilter.h
	T3DCartesianFilter.h
	TAngleFilter.h
	TCCsFilter.h
	TDMSFilter.h
	TGeodeticFilter.h
	TGonsFilter.h
	TKilometresFilter.h
	TLengthFilter.h
	TMetresFilter.h
	TMillimetresFilter.h
	TRadiansFilter.h
	TSpatialPositionFilter.h
	# TWPS2DFilter.h
	# TWPSTFilter.h
	# TWPSVFilter.h
	# TWTW2DFilter.h
	# TWTWHFilter.h
	# TWTWVFilter.h
)

# Create a static library from sources:
add_library(FiltersAndFormats STATIC ${FiltersAndFormats_SOURCES} ${FiltersAndFormats_HEADERS})

#link used libraries
target_link_libraries(FiltersAndFormats  ${SPATIAL_LIBRARIES})