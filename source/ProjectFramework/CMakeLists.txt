# Create a variable containing all .cpp files:
set(ProjectFramework_SOURCES 
	sources/Converters/TAConverter.cpp
	sources/Converters/TObservationFormat.cpp
	sources/Converters/TPointConverter.cpp
	sources/Converters/TPointFormat.cpp
	sources/FiltersAndFormats/T100MicroGonsFilter.cpp
	sources/FiltersAndFormats/T2DPlusHFilter.cpp
	sources/FiltersAndFormats/T3DCartesianFilter.cpp
	sources/FiltersAndFormats/TCCsFilter.cpp
	sources/FiltersAndFormats/TDeciDegsFilter.cpp
	sources/FiltersAndFormats/TDMSFilter.cpp
	sources/FiltersAndFormats/TGeodeticFilter.cpp
	sources/FiltersAndFormats/TGonsFilter.cpp
	sources/FiltersAndFormats/TKilometresFilter.cpp
	sources/FiltersAndFormats/TLengthFilter.cpp
	sources/FiltersAndFormats/TMetresFilter.cpp
	sources/FiltersAndFormats/TMillimetresFilter.cpp
	sources/FiltersAndFormats/TRadiansFilter.cpp
	sources/ProjectData/TADataSet.cpp
	sources/ProjectData/TDataParameters.cpp
	sources/ProjectData/TFileParameters.cpp
	sources/ProjectData/TPtListBroadcaster.cpp
	sources/ProjectData/TWorkingPoints.cpp
	sources/StreamFormatters/TAStreamFormatter.cpp
	sources/StreamFormatters/TFixedColFormatTStream.cpp
	sources/StreamFormatters/TSeparatedFormatTStream.cpp
	sources/StreamFormatters/TStreamFormatterFactory.cpp
)

# Create a variable containing all .h files:
set(ProjectFramework_HEADERS 
	headers/Converters/TAConverter.h
	headers/Converters/TObservationFormat.h
	headers/Converters/TPointConverter.h
	headers/Converters/TPointFormat.h
	headers/FiltersAndFormats/T100MicroGonsFilter.h
	headers/FiltersAndFormats/T2DPlusHFilter.h
	headers/FiltersAndFormats/T3DCartesianFilter.h
	headers/FiltersAndFormats/TAngleFilter.h
	headers/FiltersAndFormats/TCCsFilter.h
	headers/FiltersAndFormats/TDeciDegsFilter.h
	headers/FiltersAndFormats/TDMSFilter.h
	headers/FiltersAndFormats/TGeodeticFilter.h
	headers/FiltersAndFormats/TGonsFilter.h
	headers/FiltersAndFormats/TKilometresFilter.h
	headers/FiltersAndFormats/TLengthFilter.h
	headers/FiltersAndFormats/TMetresFilter.h
	headers/FiltersAndFormats/TMillimetresFilter.h
	headers/FiltersAndFormats/TRadiansFilter.h
	headers/FiltersAndFormats/TSpatialPositionFilter.h
	headers/ProjectData/TADataSet.h
	headers/ProjectData/TDataParameters.h
	headers/ProjectData/TFileParameters.h
	headers/ProjectData/TPtListBroadcaster.h
	headers/ProjectData/TVPtListListener.h
	headers/ProjectData/TWorkingPoints.h
	headers/StreamFormatters/TAStreamFormatter.h
	headers/StreamFormatters/TFixedColFormatTStream.h
	headers/StreamFormatters/TSeparatedFormatTStream.h
	headers/StreamFormatters/TStreamFormatterFactory.h
)

# Define VS folders:
file(GLOB CONVERTERS_H					headers/Converters/*.*)
file(GLOB CONVERTERS_CPP				sources/Converters/*.*)
file(GLOB FILTERS_H					headers/FiltersAndFormats/*.*)
file(GLOB FILTERS_CPP					sources/FiltersAndFormats/*.*)
file(GLOB PROJECTDATA_H					headers/ProjectData/*.*)
file(GLOB PROJECTDATA_CPP				sources/ProjectData/*.*)
file(GLOB STREAMFORMATTERS_H				headers/StreamFormatters/*.*)
file(GLOB STREAMFORMATTERS_CPP				sources/StreamFormatters/*.*)
source_group("Converters\\Headers"			FILES	${CONVERTERS_H})
source_group("Converters\\Sources"			FILES	${CONVERTERS_CPP})
source_group("FiltersAndFormats\\Headers"		FILES	${FILTERS_H})
source_group("FiltersAndFormats\\Sources"		FILES	${FILTERS_CPP})
source_group("ProjectData\\Headers"				FILES	${PROJECTDATA_H})
source_group("ProjectData\\Sources"			FILES	${PROJECTDATA_CPP})
source_group("StreamFormatters\\Headers"	FILES	${STREAMFORMATTERS_H})
source_group("StreamFormatters\\Sources"		FILES	${STREAMFORMATTERS_CPP})

# Create a static library from sources:
add_library(ProjectFramework STATIC
	${ProjectFramework_SOURCES}
	${ProjectFramework_HEADERS}
)
target_include_directories(ProjectFramework PUBLIC
	# SurveyLib
	headers/Converters
	headers/FiltersAndFormats
	headers/ProjectData
	headers/StreamFormatters
)
target_link_libraries(ProjectFramework
	# SurveyLib
	Tools
	SpatialObjects
	LSAlgorithms
)

# needed for linux compilation
set_target_properties(ProjectFramework PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Define IDE folders:
set_target_properties(ProjectFramework PROPERTIES FOLDER "SurveyLib")
