# add subdirectories that are a part of the library
SET(SPATIALOBJECTS_LIB_SUBPROJECTS
	AffineTransformations
	MathematicalConcepts
	ReferenceSurfaces
	RefFrameTransformations
	ShortestPath
	SpatialObj
	SpatialSystems
)

FOREACH(subproject ${SPATIALOBJECTS_LIB_SUBPROJECTS})
    ADD_SUBDIRECTORY(${subproject})
	SET_PROPERTY(TARGET ${subproject} PROPERTY FOLDER "SpatialObjects")
ENDFOREACH(subproject) 

ADD_SUBDIRECTORY(SpatialObjectsLibraryStatic)
SET_PROPERTY(TARGET SpatialObjectsLibrary PROPERTY FOLDER "SpatialObjects")

ADD_SUBDIRECTORY(SpatialObjects)

ADD_SUBDIRECTORY(UnitTests)
SET_PROPERTY(TARGET UnitTests PROPERTY FOLDER "SpatialObjects")