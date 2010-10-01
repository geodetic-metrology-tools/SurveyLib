# add subdirectories that are a part of the library
SET(SPATIALMEASUREMENTS_LIB_SUBPROJECTS
	ConstraintMeasurements
	InstrumentStations
	MeasurementConstants
	Measurements
	ROMs
)

FOREACH(subproject ${SPATIALMEASUREMENTS_LIB_SUBPROJECTS})
    ADD_SUBDIRECTORY(${subproject})
	SET_PROPERTY(TARGET ${subproject} PROPERTY FOLDER "SpatialMeasurements")
ENDFOREACH(subproject) 

ADD_SUBDIRECTORY(SpatialMeasurementsLibraryStatic)
SET_PROPERTY(TARGET SpatialMeasurementsLibrary PROPERTY FOLDER "SpatialMeasurements")
install(FILES SpatialMeasurements-config.cmake DESTINATION ${INSTALL_PREFIX})
