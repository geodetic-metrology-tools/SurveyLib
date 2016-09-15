# Project name - (corresponds to solution name in visual studio)
PROJECT(SurveyLib)

# Set version number and provide a header file with corresponding defines
set (SurveyLib_VERSION_MAJOR 3)
set (SurveyLib_VERSION_MINOR 5)
set (SurveyLib_VERSION_PATCH 0)

configure_file (
  "${CMAKE_SOURCE_DIR}/SurveryLibVersion.in"
  "${CMAKE_SOURCE_DIR}/SurveryLibVersion.h"
  )

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
SET(USE_INTEL_COMPILER FALSE)
IF(USE_INTEL_COMPILER)
	MESSAGE(STATUS "[ENABLED] - Intel compiler specific options")
ELSE()
    MESSAGE(STATUS "[DISABLED] - Intel compiler specific options")
ENDIF()

# Paths to external libraries to keep them out of svn (headers and libraries):
# Must set the variables TUT_INCLUDE_PATH REFRAME_INCLUDE_PATH and EIGEN_INCLUDE_PATH
INCLUDE(../../ext_libs.txt)

# Installation path prefix
# All the header and library files will be copied to that location
SET(INSTALL_PREFIX "C:/lib/${PROJECT_NAME}")
MESSAGE(STATUS "[INFO] - Install task configured to use ${INSTALL_PREFIX}")

SET(STAGING_DIRECTORY ${CMAKE_BINARY_DIR}/staging)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${STAGING_DIRECTORY})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${STAGING_DIRECTORY})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${STAGING_DIRECTORY})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${STAGING_DIRECTORY})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${STAGING_DIRECTORY})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${STAGING_DIRECTORY})

# Check for TUT testing framework
SET(CMAKE_REQUIRED_INCLUDES ${TUT_INCLUDE_PATH})
CHECK_INCLUDE_FILE_CXX("tut.h" HAVE_TUT_H)

IF(NOT HAVE_TUT_H)
    MESSAGE(FATAL_ERROR "[ERROR] Cannot find tut.h. Set TUT_INCLUDE_PATH")
ELSE()
    MESSAGE(STATUS "[STATUS] Found tut.h")
ENDIF()

#Enable swisstopo transformations when compiling surveylib on its own.
SET(USE_SWISSTOPO true)

INCLUDE("${CMAKE_SOURCE_DIR}/SourceSurveyLib.cmake")

ADD_SUBDIRECTORY(Tests/SpatialObjects/UnitTests)
