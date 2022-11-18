project(CSGeoDLL)

set(CSGEO_DLL_NAME ${PROJECT_NAME} PARENT_SCOPE)

# needed for linux compilation
set(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

# set include directories needed by this library
set(CSGEO_DLL "${SURVEYLIB_ROOT}/source/CSGeoDLL")
set(CSGEO_DLL_SOURCES "${CSGEO_DLL}/sources")
set(CSGEO_DLL_HEADERS "${CSGEO_DLL}/headers")

include_directories(${CSGEO_DLL_HEADERS})

# Create a variable containing all .cpp files:
set(csgeoDLL_SOURCESfiles
	${CSGEO_DLL_SOURCES}/utils/PositionVectorUtils.cpp

	${CSGEO_DLL_SOURCES}/PlainTransform.cpp
	${CSGEO_DLL_SOURCES}/TOptionsCheck.cpp
	${CSGEO_DLL}/csgeoDLL.def
)

# Create a variable containing all .h files:
set(csgeoDLL_HEADERSfiles 
	${CSGEO_DLL_HEADERS}/utils/PositionVectorUtils.h
	${CSGEO_DLL_HEADERS}/utils/TGlobalDefs.h

	${CSGEO_DLL_HEADERS}/PlainTransform.h
	${CSGEO_DLL_HEADERS}/TPlainDataParameters.h
	${CSGEO_DLL_HEADERS}/TOptionsCheck.h
)

# Create a SHARED library from sources:
add_library(${PROJECT_NAME} SHARED ${csgeoDLL_SOURCESfiles} ${csgeoDLL_HEADERSfiles})

# Specify the libraries to link against
target_link_libraries (${PROJECT_NAME}
	ProjectFramework
	SpatialObjects
)

#Compile using Common language Runtime Support
#Required to call transformations involving Reframe DLL from Python code
if(USE_SWISSTOPO AND MSVC)
	set(CMAKE_VS_SDK_REFERENCE_DIRECTORIES ${REFRAME2016_LIBRARY_DIR})
	set_target_properties(${PROJECT_NAME} PROPERTIES COMMON_LANGUAGE_RUNTIME "")
	target_compile_options(${PROJECT_NAME} PRIVATE /AI"${REFRAME2016_LIBRARY_DIR}")
endif()

if(USE_SWISSTOPO)
	copyReframeDLL(${PROJECT_NAME})
endif()

# Define IDE folders:
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "SurveyLib")
#####
