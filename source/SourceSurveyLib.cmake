IF(CMAKE_PROJECT_NAME STREQUAL "SurveyLib")
	message("-- Building Surveylib in tree.")
ENDIF()

# Inlcude sublibraries
INCLUDE(SubLibraries.cmake)

# Compiler options
IF(MSVC)
	ADD_DEFINITIONS(-D_SCL_SECURE_NO_WARNINGS)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE)
ENDIF()

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
		SET(add_srcdir "${sublib}")
		ADD_SUBDIRECTORY("${add_srcdir}" "${add_bindir}")
		LINK_DIRECTORIES ("${add_bindir}")
	ENDFOREACH(sublib) 
ENDIF()
