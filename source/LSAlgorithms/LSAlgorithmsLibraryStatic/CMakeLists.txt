# This is responsible for generating the combined library

set(COMBINED_LIBRARY_FILES)
FOREACH(subproject ${LSALGORITHMS_LIB_SUBPROJECTS})
    list(APPEND COMBINED_LIBRARY_FILES "${STAGING_DIRECTORY}/${subproject}.lib")
ENDFOREACH(subproject) 


add_library(LSAlgorithmsLibrary STATIC ${COMBINED_LIBRARY_FILES})
add_dependencies(LSAlgorithmsLibrary ${LSALGORITHMS_LIB_SUBPROJECTS})

SET_SOURCE_FILES_PROPERTIES(
  ${COMBINED_LIBRARY_FILES}
  PROPERTIES
  EXTERNAL_OBJECT true
  GENERATED true
)

SET_TARGET_PROPERTIES(
  LSAlgorithmsLibrary
  PROPERTIES
  LINKER_LANGUAGE CXX
)

install(TARGETS LSAlgorithmsLibrary DESTINATION ${INSTALL_PREFIX})
