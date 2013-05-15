# This variables are referenced in other projects, too!
SET(SURVEYLIB_LIBRARIES
	LSAlgorithms
	ProjectFramework
	SpatialMeasurements
	SpatialObjects
)

SET(MEASUREMENT_LIBRARIES 
	ConstraintMeasurements 
	InstrumentStations 
	MeasurementConstants 
	Measurements 
	ROMs
	BCAM
)

SET(SPATIAL_LIBRARIES 
	AffineTransformations 
	MathematicalConcepts 
	ReferenceSurfaces 
	RefFrameTransformations 
	ShortestPath 
	SpatialObj 
	SpatialSystems
)

SET(PROJECTFRAMEWORK_LIBRARIES
	Converters 
	FiltersAndFormats 
	ProjectData 
	StreamFormatters 
)

SET(LSALGO_LIBRARIES
	CalcElements
	CalcParams
)

SET(ALL_SURVEYLIB_LIBS
	${MEASUREMENT_LIBRARIES}
	${SPATIAL_LIBRARIES}
	${PROJECTFRAMEWORK_LIBRARIES}
	${LSALGO_LIBRARIES}
)