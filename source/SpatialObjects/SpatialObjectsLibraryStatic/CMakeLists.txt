# This is responsible for generating the combined library

set(COMBINED_LIBRARY_FILES)
set(STATIC_LIBS)
FOREACH(subproject ${SPATIALOBJECTS_LIB_SUBPROJECTS})
    list(APPEND COMBINED_LIBRARY_FILES "${STAGING_DIRECTORY}/${subproject}.lib")
	set(STATIC_LIBS "${STATIC_LIBS} ${STAGING_DIRECTORY}/${subproject}.lib" )
ENDFOREACH(subproject) 


add_library(SpatialObjectsLibrary STATIC ${COMBINED_LIBRARY_FILES} dummy.c)
#add_dependencies(SpatialObjectsLibrary ${SPATIALOBJECTS_LIB_SUBPROJECTS})
target_link_libraries(SpatialObjectsLibrary ${COMBINED_LIBRARY_FILES})

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

SET_TARGET_PROPERTIES(
  SpatialObjectsLibrary
  PROPERTIES
  STATIC_LIBRARY_FLAGS "${STATIC_LIBS}"
)

install(TARGETS SpatialObjectsLibrary DESTINATION ${INSTALL_PREFIX})
