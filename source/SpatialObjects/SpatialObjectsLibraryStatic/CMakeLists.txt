# This is responsible for generating the combined library

set(COMBINED_LIBRARY_FILES)
FOREACH(subproject ${SPATIALOBJECTS_LIB_SUBPROJECTS})
    list(APPEND COMBINED_LIBRARY_FILES "${CMAKE_BINARY_DIR}/${subproject}/${CMAKE_BUILD_TYPE}/${subproject}.lib")
ENDFOREACH(subproject) 


add_library(SpatialObjects STATIC  ${COMBINED_LIBRARY_FILES})
add_dependencies(SpatialObjects ${SPATIALOBJECTS_LIB_SUBPROJECTS})

SET_SOURCE_FILES_PROPERTIES(
  ${COMBINED_LIBRARY_FILES}
  PROPERTIES
  EXTERNAL_OBJECT true
  GENERATED true
)

SET_TARGET_PROPERTIES(
  SpatialObjects
  PROPERTIES
  LINKER_LANGUAGE CXX
)

install(TARGETS SpatialObjects 
	DESTINATION ${INSTALL_PREFIX}
	EXPORT SpatialObjects-targets)
install(EXPORT SpatialObjects-targets 
	DESTINATION ${INSTALL_PREFIX})
