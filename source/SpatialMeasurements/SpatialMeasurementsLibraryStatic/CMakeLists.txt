# This is responsible for generating the combined library

set(COMBINED_LIBRARY_FILES)
FOREACH(subproject ${SPATIALMEASUREMENTS_LIB_SUBPROJECTS})
    list(APPEND COMBINED_LIBRARY_FILES "${STAGING_DIRECTORY}/${subproject}.lib")
ENDFOREACH(subproject) 


add_library(SpatialMeasurementsLibrary STATIC  ${COMBINED_LIBRARY_FILES})
add_dependencies(SpatialMeasurementsLibrary ${SPATIALMEASUREMENTS_LIB_SUBPROJECTS})

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

install(TARGETS SpatialMeasurementsLibrary DESTINATION ${INSTALL_PREFIX})
