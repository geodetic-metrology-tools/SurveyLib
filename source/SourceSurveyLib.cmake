IF(CMAKE_PROJECT_NAME STREQUAL "SurveyLib")
	SET(SURVEYLIB_ROOT "${CMAKE_SOURCE_DIR}/..")
	message("-- Building Surveylib in tree.")
ENDIF()

# Inlcude sublibraries
INCLUDE(${SURVEYLIB_ROOT}/source/SubLibraries.cmake)

# Compiler options
IF(MSVC)
	ADD_DEFINITIONS(-D_SCL_SECURE_NO_WARNINGS)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE)
ENDIF()

INCLUDE_DIRECTORIES(${EIGEN_INCLUDE_PATH} ${SURVEYLIB_INCLUDE_PATH})

IF(CMAKE_PROJECT_NAME STREQUAL "SurveyLib")
	# Includes for all subprojects
	# In-tree build
	FOREACH(lib ${SURVEYLIB_LIBRARIES})
		# A sublibrary may already have been added by one that depends on it:
		# SpatialObjects supplies Serialization, appended to the list after it.
		IF(NOT TARGET ${lib})
			ADD_SUBDIRECTORY(${lib})
		ENDIF()
	ENDFOREACH(lib)
ELSE()
	# out of tree build, needs seperate bin directories
	FOREACH(sublib ${SURVEYLIB_LIBRARIES})
		SET(add_bindir "${CMAKE_CURRENT_BINARY_DIR}/svl${sublib}")
		SET(add_srcdir "${SURVEYLIB_ROOT}/source/${sublib}")
		IF(NOT TARGET ${sublib})
			ADD_SUBDIRECTORY("${add_srcdir}" "${add_bindir}")
		ENDIF()
		LINK_DIRECTORIES ("${add_bindir}")
	ENDFOREACH(sublib)
ENDIF()
