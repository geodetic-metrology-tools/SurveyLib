# To create a solution with this CMake file, you need to first define the following variables in a CMake style file.
#
# - `EIGEN_INCLUDE_PATH`: The path to Eigen folder
# - `REFRAME2016_LIBRARY_DIR`: The path to Reframe 2016 folder 
# - `TUT_INCLUDE_PATH`: The path to Tut folder

cmake_minimum_required(VERSION 3.6)

#############################################################
#
# PROJECT NAME
#

project(SurveyLib)

# Set version number and provide a header file with corresponding defines
set (SurveyLib_VERSION_MAJOR 4)
set (SurveyLib_VERSION_MINOR 03)
set (SurveyLib_VERSION_PATCH 01)

configure_file (
  "${CMAKE_SOURCE_DIR}/SurveyLibVersion.in"
  "${CMAKE_SOURCE_DIR}/SurveyLibVersion.h"
  )

#############################################################
#
# GLOBAL CONFIGURATION
#

set(CREATE_DOC ON)
set(DOXYGEN_CONF_PATH ".")
set(ENABLE_CONSOLE ON)
### SUBMODULES
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
	message("Buidling SurveyLib as a standalone project")
	include("../lib/SUSoftCMakeCommon/CMakeLists.txt")
endif(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)

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

# Enable swisstopo transformations when compiling surveylib on its own.
# Only for Windows as SwissTopo needs a DLL not available on the other platforms
if(WIN32)
	SET(USE_SWISSTOPO true)
endif()

INCLUDE("${CMAKE_SOURCE_DIR}/SourceSurveyLib.cmake")

############################
# MSVC:
if(MSVC)
	set_vs_default_startup_project(UnitTests)
endif()

ADD_SUBDIRECTORY(Tests)
