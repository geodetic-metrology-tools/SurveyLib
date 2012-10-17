# Project name - (corresponds to solution name in visual studio)
PROJECT(SurveyLib_V3)

# Minimum version of CMake needed to process the configuration files
cmake_minimum_required(VERSION 2.8.4)
CMAKE_POLICY(SET CMP0015 OLD)

# We need some CMake macros
INCLUDE(CheckIncludeFileCXX)

# Programming languages used within the solution
enable_language("CXX")

# Type of the build:
IF(NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE DEBUG)
	#SET(CMAKE_BUILD_TYPE RELEASE)
ENDIF (NOT CMAKE_BUILD_TYPE)

# Are we going to use Intel Compiler
SET(USE_INTEL_COMPILER TRUE)
IF(USE_INTEL_COMPILER)
	MESSAGE(STATUS "[ENABLED] - Intel compiler specific options")
ELSE()
    MESSAGE(STATUS "[DISABLED] - Intel compiler specific options")
ENDIF()

# Paths to external libraries (headers and libraries):
SET(TUT_INCLUDE_PATH "C:/lib/tut-2009-08-30")
SET(REFRAME_INCLUDE_PATH "C:/Lib/reframe")
#SET(EIGEN_INCLUDE_PATH "C:/lib/eigen/eigen-2.0.15")
SET(EIGEN_INCLUDE_PATH "C:/lib/eigen/eigen-eigen-43d9075b23ef")

# Installation path prefix
# All the header and library files will be copied to that location
SET(INSTALL_PREFIX "C:/lib/${PROJECT_NAME}")
MESSAGE(STATUS "[INFO] - Install task configured to use ${INSTALL_PREFIX}")

# Surveylib specific setting - needed as all the headers are in one dir
SET(SURVEYLIB_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/../include")

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

SET(STAGING_DIRECTORY ${CMAKE_BINARY_DIR}/staging)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${STAGING_DIRECTORY})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${STAGING_DIRECTORY})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${STAGING_DIRECTORY})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${STAGING_DIRECTORY})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${STAGING_DIRECTORY})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${STAGING_DIRECTORY})

# Check that we have the files we need
SET(CMAKE_REQUIRED_INCLUDES ${TUT_INCLUDE_PATH})
CHECK_INCLUDE_FILE_CXX("tut.h" HAVE_TUT_H)
SET(CMAKE_REQUIRED_INCLUDES "")
SET(CMAKE_REQUIRED_INCLUDES ${EIGEN_INCLUDE_PATH})
CHECK_INCLUDE_FILE_CXX("eigen/Core" HAVE_EIGEN_H)
SET(CMAKE_REQUIRED_INCLUDES "")

IF(NOT HAVE_TUT_H)
    MESSAGE(FATAL_ERROR "[ERROR] Cannot find tut.h. Set TUT_INCLUDE_PATH")
ELSE()
    MESSAGE(STATUS "[STATUS] Found tut.h")
ENDIF()

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

include_directories (${EIGEN_INCLUDE_PATH})

ADD_SUBDIRECTORY(LSAlgorithms)
ADD_SUBDIRECTORY(SpatialMeasurements)
ADD_SUBDIRECTORY(SpatialObjects)
ADD_SUBDIRECTORY(ProjectFramework)
