# Setting the include path - to include a given directory
include_directories (
	.
	${SURVEYLIB_INCLUDE_PATH}
)

ADD_DEFINITIONS("-DSU_MAKEDLL")
ADD_DEFINITIONS("-D_USRDLL")
ADD_DEFINITIONS("-DSPATIALOBJECTS_EXPORTS")

##### This will correspond to one VS project!

set(SurveyLibDLL_SOURCES
	SpatialObjCFns.cpp
	SpatialObjFns.cpp
	test.def
)
#SpatialObjJFns.cpp

set(SurveyLibDLL_HEADERS
	${SURVEYLIB_INCLUDE_PATH}/SpatialObjCFns.h
	${SURVEYLIB_INCLUDE_PATH}/SpatialObjFns.h
)
#${SURVEYLIB_INCLUDE_PATH}/SpatialObjJFns.h

# Create a SHARED library from sources:
add_library(SurveyLib SHARED ${SurveyLibDLL_SOURCES} ${SurveyLibDLL_HEADERS})

# Specify the libraries to link against
target_link_libraries (SurveyLib SpatialObjectsLibrary)

#####