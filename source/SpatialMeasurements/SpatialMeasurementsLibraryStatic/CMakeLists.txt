# This is responsible for generating the combined library

set(COMBINED_LIBRARY_FILES)
set(STATIC_LIBS)
FOREACH(subproject ${SPATIALMEASUREMENTS_LIB_SUBPROJECTS})
    list(APPEND COMBINED_LIBRARY_FILES "${STAGING_DIRECTORY}/${subproject}.lib")
	set(STATIC_LIBS "${STATIC_LIBS} ${STAGING_DIRECTORY}/${subproject}.lib" )
ENDFOREACH(subproject) 


add_library(SpatialMeasurementsLibrary STATIC  ${COMBINED_LIBRARY_FILES} dummy.c)
#add_dependencies(SpatialMeasurementsLibrary ${SPATIALMEASUREMENTS_LIB_SUBPROJECTS})
target_link_libraries(SpatialMeasurementsLibrary ${COMBINED_LIBRARY_FILES})

SET_SOURCE_FILES_PROPERTIES(
  ${COMBINED_LIBRARY_FILES}
  PROPERTIES
  EXTERNAL_OBJECT true
  GENERATED true
)

SET_TARGET_PROPERTIES(
  SpatialMeasurementsLibrary
  PROPERTIES
  LINKER_LANGUAGE CXX
)

SET_TARGET_PROPERTIES(
  SpatialMeasurementsLibrary
  PROPERTIES
  STATIC_LIBRARY_FLAGS "${STATIC_LIBS}"
)

install(TARGETS SpatialMeasurementsLibrary DESTINATION ${INSTALL_PREFIX})
