IF(CMAKE_PROJECT_NAME STREQUAL "SurveyLib")
	SET(SURVEYLIB_ROOT "${CMAKE_SOURCE_DIR}/..")
	message("-- Building Surveylib in tree.")
ENDIF()

# Inlcude sublibraries
INCLUDE(${SURVEYLIB_ROOT}/source/SubLibraries.cmake)

# Compiler options
IF(WIN32)
    IF(MSVC)
        ADD_DEFINITIONS(-D_SCL_SECURE_NO_WARNINGS)
        ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE)
    ENDIF(MSVC)
ENDIF(WIN32)

IF(USE_SWISSTOPO)
	MESSAGE(STATUS "[STATUS] Swisstopo transformations enabled.")
	IF(NOT EXISTS "${REFRAME_LIBRARY_DIR}/swisstopoReframeLib.tlb")
		# Try a different name
		IF(NOT EXISTS "${REFRAME_LIBRARY_DIR}/swisstopoReframeLib.tlb")
			MESSAGE(FATAL_ERROR "[ERROR] Cannot find swisstopoReframeLib.tlb in ${REFRAME_LIBRARY_DIR}")
		ELSE()
			MESSAGE(STATUS "[STATUS] Found swisstopoReframeLib.tlb in ${REFRAME_LIBRARY_DIR}")
			LINK_DIRECTORIES(${REFRAME_LIBRARY_DIR})
			INCLUDE_DIRECTORIES(${REFRAME_LIBRARY_DIR})
		ENDIF()
	ELSE()
		MESSAGE(STATUS "[STATUS] Found swisstopoReframeLib.tlb in ${REFRAME_LIBRARY_DIR}")
		LINK_DIRECTORIES(${REFRAME_LIBRARY_DIR})
		INCLUDE_DIRECTORIES(${REFRAME_LIBRARY_DIR})
	ENDIF()
	IF(NOT EXISTS "${REFRAME_LIBRARY_DIR}/swisstopoReframeLib.dll")
		# Try a different name
		IF(NOT EXISTS "${REFRAME_LIBRARY_DIR}/swisstopoReframeLib.dll")
			MESSAGE(FATAL_ERROR "[ERROR] Cannot find swisstopoReframeLib.tlb in ${REFRAME_LIBRARY_DIR}")
		ELSE()
			MESSAGE(STATUS "[STATUS] Found swisstopoReframeLib.tlb in ${REFRAME_LIBRARY_DIR}")
		ENDIF()
	ELSE()
		MESSAGE(STATUS "[STATUS] Found swisstopoReframeLib.dll in ${REFRAME_LIBRARY_DIR}")
	ENDIF()
	ADD_DEFINITIONS(-DUSE_SWISSTOPO)
ELSE(USE_SWISSTOPO)
	MESSAGE(STATUS "[STATUS] Swisstopo transformations disabled.")
ENDIF(USE_SWISSTOPO)

INCLUDE_DIRECTORIES(${EIGEN_INCLUDE_PATH} ${SURVEYLIB_INCLUDE_PATH})
	
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
