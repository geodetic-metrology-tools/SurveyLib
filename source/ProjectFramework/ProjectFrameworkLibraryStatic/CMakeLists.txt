# This is responsible for generating the combined library

set(COMBINED_LIBRARY_FILES)
FOREACH(subproject ${PROJECTFRAMEWORK_LIB_SUBPROJECTS})
    list(APPEND COMBINED_LIBRARY_FILES "${STAGING_DIRECTORY}/${subproject}.lib")
ENDFOREACH(subproject) 

add_library(ProjectFrameworkLibrary STATIC ${COMBINED_LIBRARY_FILES})
add_dependencies(ProjectFrameworkLibrary ${PROJECTFRAMEWORK_LIB_SUBPROJECTS})

SET_SOURCE_FILES_PROPERTIES(
  ${COMBINED_LIBRARY_FILES}
  PROPERTIES
  EXTERNAL_OBJECT true
  GENERATED true
)

SET_TARGET_PROPERTIES(
  ProjectFrameworkLibrary
  PROPERTIES
  LINKER_LANGUAGE CXX
)


install(TARGETS ProjectFrameworkLibrary DESTINATION ${INSTALL_PREFIX})
