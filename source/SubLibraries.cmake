# This variables are referenced in other projects, too!
SET(SURVEYLIB_LIBRARIES
	LSAlgorithms
	ProjectFramework
	SpatialObjects
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
	${SPATIAL_LIBRARIES}
	${PROJECTFRAMEWORK_LIBRARIES}
	${LSALGO_LIBRARIES}
)