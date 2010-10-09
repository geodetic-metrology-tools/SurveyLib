# declare a project
PROJECT(SurveyLib_V3)

# minimum version of CMake
cmake_minimum_required(VERSION 2.8)

# enable languages
enable_language("CXX")

# default build type
SET(CMAKE_BUILD_TYPE DEBUG)

#######################################################################
# Whether to use Intel Compiler specific flags
SET(USE_INTEL_COMPILER TRUE)

# installation path prefix (where to copy the lib and include files)
SET(INSTALL_PREFIX "C:/lib/${PROJECT_NAME}" CACHE PATH "Installation path prefix.")


# This will not be needed as soon as we put includes along the source files.
# These are our includes. 
#SET(SURVEYLIB_INCLUDE_PATH "C:/SVN/SVN_SurveyLib/SurveyLib/include")
SET(SURVEYLIB_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/../include")

# Set the paths to the libraries
SET(NAGC_INCLUDE_PATH "G:/Support/SurveyingEng/software/nagc/include")
SET(TUT_INCLUDE_PATH "C:/lib/tut-2009-08-30")
SET(REFRAME_INCLUDE_PATH "C:/TestProject/DLLfile")

# Where to look for the libraries to link against
SET(NAGC_LIBRARY_DIR "G:/Support/SurveyingEng/software/nagc/dll")
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

#######################################################################


# Specific options will go here
IF(WIN32)
    IF(MSVC)
        # turn off various warnings
        # foreach(warning 4244 4251 4267 4275 4290 4786 4305 4996)
        #     SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd${warning}")
        # endforeach(warning)

        # More MSVC specific compilation flags
        ADD_DEFINITIONS(-D_SCL_SECURE_NO_WARNINGS)
        ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE)
    ENDIF(MSVC)
	IF(USE_INTEL_COMPILER)
		# Support for the quadruple precision:
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Qoption,cpp,--extended_float_type")
		# Maximum level (5) of warnings produces too many warnings
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
	ENDIF(USE_INTEL_COMPILER)
ENDIF(WIN32)

ADD_SUBDIRECTORY(LSAlgorithms)
ADD_SUBDIRECTORY(SpatialMeasurements)
ADD_SUBDIRECTORY(SpatialObjects)
ADD_SUBDIRECTORY(ProjectFramework)
