# This is responsible for generating the combined library

set(COMBINED_LIBRARY_FILES)
FOREACH(subproject ${PROJECTFRAMEWORK_LIB_SUBPROJECTS})
    list(APPEND COMBINED_LIBRARY_FILES "${CMAKE_BINARY_DIR}/${subproject}/${CMAKE_BUILD_TYPE}/${subproject}.lib")
ENDFOREACH(subproject) 

add_library(ProjectFramework STATIC ${COMBINED_LIBRARY_FILES})
add_dependencies(ProjectFramework ${PROJECTFRAMEWORK_LIB_SUBPROJECTS})

SET_SOURCE_FILES_PROPERTIES(
  ${COMBINED_LIBRARY_FILES}
  PROPERTIES
  EXTERNAL_OBJECT true
  GENERATED true
)

SET_TARGET_PROPERTIES(
  ProjectFramework
  PROPERTIES
  LINKER_LANGUAGE CXX
)


install(TARGETS ProjectFramework 
	DESTINATION ${INSTALL_PREFIX}
	EXPORT ProjectFramework-targets)
install(EXPORT ProjectFramework-targets 
	DESTINATION ${INSTALL_PREFIX})
