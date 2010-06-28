# declare a project
PROJECT(ProjectFramework)

# minimum version of CMake
cmake_minimum_required(VERSION 2.6)

# enable languages
enable_language("CXX")

# default build type
SET(CMAKE_BUILD_TYPE DEBUG)

#######################################################################
# Whether to use Intel Compiler specific flags
SET(USE_INTEL_COMPILER TRUE)

# Set the paths to the libraries
SET(SURVEYLIB_INCLUDE_PATH "C:/SVN/SVN_SurveyLib/SurveyLib/include")
SET(NAGC_INCLUDE_PATH "G:/Support/SurveyingEng/software/nagc/include")

# Where to look for the libraries to link against
SET(NAGC_LIBRARY_DIR "G:/Support/SurveyingEng/software/nagc/dll")

#######################################################################

# installation path prefix
SET(INSTALL_PREFIX "C:/lib/SurveyLib" CACHE PATH "Installation path prefix.")

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

# add subdirectories
SET(PROJECTFRAMEWORK_LIB_SUBPROJECTS
	Converters
	FiltersAndFormats
	ProjectData
	StreamFormatters
)

FOREACH(subproject ${PROJECTFRAMEWORK_LIB_SUBPROJECTS})
    ADD_SUBDIRECTORY(${subproject})
ENDFOREACH(subproject) 


ADD_SUBDIRECTORY(ProjectFrameworkLibraryStatic)
install(FILES ProjectFramework-config.cmake DESTINATION ${INSTALL_PREFIX})