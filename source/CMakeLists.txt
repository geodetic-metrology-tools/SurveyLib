#
# CMake file for LGC2UI
#
# To create a solution with this CMake file, you need to first define the following variables in a CMake style file.
# The path to this file can be setup in the below variable `EXT_LIBS_TXT_PATH`
#
# - `BOOST_ROOT`: The path to Boost folder
# - `EIGEN_INCLUDE_PATH`: The path to Eigen folder
# - `REFRAME_LIBRARY_DIR`: The path to Reframe folder
# - `TUT_INCLUDE_PATH`: The path to Tut folder
# - `VCREDIST_INSTALLER_PATH`: The path to the folder holding the VCRedist installer

cmake_minimum_required(VERSION 3.6)

#############################################################
#
# PROJECT NAME
#

set(PROJECT_NAME SurveyLib)

#############################################################
#
# GLOBAL CONFIGURATION
#

set(CREATE_DOC ON)
set(DOXYGEN_CONF_PATH ".")
set(ENABLE_CONSOLE ON)

include("../../SUSoftCMakeCommon/CMakeLists.txt")

# Set version number and provide a header file with corresponding defines
set (SurveyLib_VERSION_MAJOR 3)
set (SurveyLib_VERSION_MINOR 5)
set (SurveyLib_VERSION_PATCH 01)

configure_file (
  "${CMAKE_SOURCE_DIR}/SurveryLibVersion.in"
  "${CMAKE_SOURCE_DIR}/SurveryLibVersion.h"
  )

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

#Enable swisstopo transformations when compiling surveylib on its own.
SET(USE_SWISSTOPO true)

INCLUDE("${CMAKE_SOURCE_DIR}/SourceSurveyLib.cmake")

ADD_SUBDIRECTORY(Tests)
