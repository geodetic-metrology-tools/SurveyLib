
# We need some CMake macros
INCLUDE(CheckIncludeFileCXX)

INCLUDE(${SURVEYLIB_ROOT}/source/SubLibraries.cmake)

IF(CMAKE_PROJECT_NAME STREQUAL "SurveyLib")
	SET(SURVEYLIB_ROOT "${CMAKE_SOURCE_DIR}/..")
	message("Building Surveylib in tree.")
ENDIF()

SET(SURVEYLIB_INCLUDE_PATH "${SURVEYLIB_ROOT}/include")

# Compiler options
IF(WIN32)
	# Maximum level (5) of warnings produces too many warnings
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
    IF(MSVC)
        ADD_DEFINITIONS(-D_SCL_SECURE_NO_WARNINGS)
        ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE)
    ENDIF(MSVC)
	IF(USE_INTEL_COMPILER)
		# Support for the quadruple precision:
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Qoption,cpp,--extended_float_type")
	ENDIF(USE_INTEL_COMPILER)
ENDIF(WIN32)

# Check that we have the files we need
SET(CMAKE_REQUIRED_INCLUDES ${EIGEN_INCLUDE_PATH})
CHECK_INCLUDE_FILE_CXX("eigen/Core" HAVE_EIGEN_H)
SET(CMAKE_REQUIRED_INCLUDES "")

IF(NOT HAVE_EIGEN_H)
    MESSAGE(FATAL_ERROR "[ERROR] Cannot find eigen/Core. Set EIGEN_INCLUDE_PATH")
ELSE()
    MESSAGE(STATUS "[STATUS] Found eigen/Core")
ENDIF()

IF(NOT EXISTS "${REFRAME_INCLUDE_PATH}/reframeLib.tlb")
    MESSAGE(FATAL_ERROR "[ERROR] Cannot find reframeLib.tlb in ${REFRAME_INCLUDE_PATH}")
ELSE()
    MESSAGE(STATUS "[STATUS] Found reframeLib.tlb in ${REFRAME_INCLUDE_PATH}")
ENDIF()

IF(NOT EXISTS "${VCREDIST_INSTALLER_PATH}")
    MESSAGE(FATAL_ERROR "[ERROR] Cannot find VS redistribuable installer at ${VCREDIST_INSTALLER_PATH}")
ELSE()
    MESSAGE(STATUS "[STATUS] Found VS redistribuable installer at ${VCREDIST_INSTALLER_PATH}")
ENDIF()

IF(NOT EXISTS "${REFRAME_LIBRARY_DIR}/reframeLib.dll")
    MESSAGE(FATAL_ERROR "[ERROR] Cannot find reframeLib.dll in ${REFRAME_LIBRARY_DIR}")
ELSE()
    MESSAGE(STATUS "[STATUS] Found reframeLib.dll in ${REFRAME_LIBRARY_DIR}")
ENDIF()


INCLUDE_DIRECTORIES(${EIGEN_INCLUDE_PATH} ${SURVEYLIB_INCLUDE_PATH})
	
INCLUDE("${SURVEYLIB_ROOT}/source/SubLibraries.cmake")

IF(CMAKE_PROJECT_NAME STREQUAL "SurveyLib")
	# Includes for all subprojects
	# In-tree build
	FOREACH(lib ${SURVEYLIB_LIBRARIES})
		ADD_SUBDIRECTORY(${lib})
	ENDFOREACH(lib)
ELSE()
	# out of tree build, needs seperate bin directories
	FOREACH(sublib ${SURVEYLIB_LIBRARIES})
		SET(add_bindir "${CMAKE_CURRENT_BINARY_DIR}/svl${sublib}")
		SET(add_srcdir "${SURVEYLIB_ROOT}/source/${sublib}")
		ADD_SUBDIRECTORY("${add_srcdir}" "${add_bindir}")
		LINK_DIRECTORIES ("${add_bindir}")
	ENDFOREACH(sublib) 
ENDIF()


########################################################################
# Macro to merge libraries (Obsolete ATM)
########################################################################
# MACRO(MERGE_STATIC_LIBS MERGE_ARGS)
# # create a library from the sub-projects
# ADD_LIBRARY(${ARGV0} STATIC "${CMAKE_SOURCE_DIR}/empty.cpp")

# SET(OTHERLIBS)
# FOREACH(newlib ${ARGN})
	# # Add the sub-library to the list of libraries
    # SET(OTHERLIBS "${OTHERLIBS}" " ${STAGING_DIRECTORY}/${newlib}.lib" )
# ENDFOREACH(newlib)
# # Remove the semicolons from the list
# STRING(REPLACE ";" " " STR_OTHERLIBS "${OTHERLIBS}")
# # add the additional lib-files manually to the linker
# SET_TARGET_PROPERTIES(LSAlgorithmsLibrary PROPERTIES STATIC_LIBRARY_FLAGS ${STR_OTHERLIBS})
# # let it manually depend on the sub-projects
# ADD_DEPENDENCIES(${ARGV0} ${ARGN})
# ENDMACRO(MERGE_STATIC_LIBS)
########################################################################