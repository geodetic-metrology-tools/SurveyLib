# This is responsible for generating the combined library

set(COMBINED_LIBRARY_FILES)
FOREACH(subproject ${SPATIALOBJECTS_LIB_SUBPROJECTS})
    list(APPEND COMBINED_LIBRARY_FILES "${CMAKE_BINARY_DIR}/SpatialObjects/${subproject}/${CMAKE_BUILD_TYPE}/${subproject}.lib")
ENDFOREACH(subproject) 


add_library(SpatialObjectsLibrary STATIC  ${COMBINED_LIBRARY_FILES})
add_dependencies(SpatialObjectsLibrary ${SPATIALOBJECTS_LIB_SUBPROJECTS})

SET_SOURCE_FILES_PROPERTIES(
  ${COMBINED_LIBRARY_FILES}
  PROPERTIES
  EXTERNAL_OBJECT true
  GENERATED true
)

SET_TARGET_PROPERTIES(
  SpatialObjectsLibrary
  PROPERTIES
  LINKER_LANGUAGE CXX
)

install(TARGETS SpatialObjectsLibrary 
	DESTINATION ${INSTALL_PREFIX}
	EXPORT SpatialObjectsLibrary-targets)
install(EXPORT SpatialObjectsLibrary-targets 
	DESTINATION ${INSTALL_PREFIX})
