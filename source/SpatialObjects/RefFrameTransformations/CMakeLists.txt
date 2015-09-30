# set include directories needed by this library
include_directories(${SURVEYLIB_ROOT}/source/SpatialObjects/MathematicalConcepts
					${SURVEYLIB_ROOT}/source/SpatialObjects/ShortestPath
					${SURVEYLIB_ROOT}/source/SpatialObjects/AffineTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialSystems
					${SURVEYLIB_ROOT}/source/SpatialObjects/ReferenceSurfaces
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialObj) 

# Create a variable containing all .cpp files:
set(RefFrameTransformations_SOURCES 
	TARefFrameTransformation.cpp
	TGC2LGTransformation.cpp
	TGC2MLATransformation.cpp
	THelmertRefFrameTransform.cpp
	TLA2LGTransformation.cpp
	TLambert93Transformation.cpp
	TLG2GCTransformation.cpp
	TLG2LATransformation.cpp
	TMLA2GCTransformation.cpp
	TMLA2XYHeTransformation.cpp
	TMLA2XYHsTransformation.cpp
	TRGF93CC46Transformation.cpp
	TX0Y0He2XYHeTransformation.cpp
	TXYHe2MLATransformation.cpp
	TXYHe2X0Y0HeTransformation.cpp
	TXYHe2XYHgTransformation.cpp
	TXYHg2XYHeTransformation.cpp
	TXYHs2MLATransformation.cpp
)

# Create a variable containing all .h files:
set(RefFrameTransformations_HEADERS 
	TARefFrameTransformation.h
	TGC2LGTransformation.h
	TGC2MLATransformation.h
	THelmertRefFrameTransform.h
	TLA2LGTransformation.h
	TLambert93Transformation.h
	TLG2GCTransformation.h
	TLG2LATransformation.h
	TMLA2GCTransformation.h
	TMLA2XYHeTransformation.h
	TMLA2XYHsTransformation.h
	TRGF93CC46Transformation.h
	TVRefFrameTransformation.h
	TVTransformation.h
	TX0Y0He2XYHeTransformation.h
	TXYHe2MLATransformation.h
	TXYHe2X0Y0HeTransformation.h
	TXYHe2XYHgTransformation.h
	TXYHg2XYHeTransformation.h
	TXYHs2MLATransformation.h
)

#Add transformations if Swisstopo is used
IF(USE_SWISSTOPO)
	set(RefFrameTransformations_SOURCES 
		${RefFrameTransformations_SOURCES}
		TLV03Transformation.cpp
		TLV03TransformationStub.cpp
		TLV95Transformation.cpp
	)
	set(RefFrameTransformations_HEADERS 
		${RefFrameTransformations_HEADERS}
		TLV03Transformation.h
		TLV95Transformation.h
	)
ENDIF(USE_SWISSTOPO)

# Create a static library from sources:
add_library(RefFrameTransformations STATIC ${RefFrameTransformations_SOURCES} ${RefFrameTransformations_HEADERS})
