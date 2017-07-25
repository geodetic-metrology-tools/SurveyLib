# This variables are referenced in other projects, too!
SET(SURVEYLIB_LIBRARIES
	Tools
	LSAlgorithms
	ProjectFramework
	SpatialObjects
	SpatialObjDLL
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
	AdjustableObjects
)

SET(ALL_SURVEYLIB_LIBS
	${SPATIAL_LIBRARIES}
	${PROJECTFRAMEWORK_LIBRARIES}
)