# To create a solution with this CMake file, you need to first define the following variables in a CMake style file.
# The path to this file can be setup in the below variable `EXT_LIBS_TXT_PATH`
#
# - `BOOST_ROOT`: The path to Boost folder
# - `EIGEN_INCLUDE_PATH`: The path to Eigen folder
# - `REFRAME2016_LIBRARY_DIR`: The path to Reframe 2016 folder 
# - `TUT_INCLUDE_PATH`: The path to Tut folder
# - `VCREDIST_INSTALLER_PATH`: The path to the folder holding the VCRedist installer

cmake_minimum_required(VERSION 3.6)

#############################################################
#
# PROJECT NAME
#

project(SurveyLib)

#############################################################
#
# GLOBAL CONFIGURATION
#

set(CREATE_DOC ON)
set(DOXYGEN_CONF_PATH ".")
set(ENABLE_CONSOLE ON)

include(Init.cmake)

# Set version number and provide a header file with corresponding defines
set (SurveyLib_VERSION_MAJOR 4)
set (SurveyLib_VERSION_MINOR 03)
set (SurveyLib_VERSION_PATCH 01)

# Installation path prefix
# All the header and library files will be copied to that location
SET(INSTALL_PREFIX "C:/lib/${CMAKE_PROJECT_NAME}")
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


add_subdirectory(source)

############################
# MSVC:
if(MSVC)
	set_vs_default_startup_project(UnitTests)
endif()
