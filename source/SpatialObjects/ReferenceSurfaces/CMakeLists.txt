# set include directories needed by this library
include_directories(${SURVEYLIB_ROOT}/source/SpatialObjects/AffineTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/MathematicalConcepts
					${SURVEYLIB_ROOT}/source/SpatialObjects/ReferenceSurfaces
					${SURVEYLIB_ROOT}/source/SpatialObjects/RefFrameTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/ShortestPath
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialObj
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialSystems)

# Create a variable containing all .cpp files:
set(ReferenceSurfaces_SOURCES 
	T3DLocalRefFrame.cpp
	TA2DPlus1MapProjection.cpp
	TA3DEuclideanRefFrame.cpp
	TAGeoidModel.cpp
	TAModifiedLocalAstronomicalRF.cpp
	TAReferenceFrame.cpp
	TCernGridGeoid.cpp
	TCernParabolicGeoid.cpp
	TCernSphereGeoid.cpp
	TGeodeticRefFrame.cpp
	TGeoidValues.cpp
	TGraphLocalAstronomicalRF.cpp
	TGraphMLARF.cpp
	TModifiedLocalAstronomicalRF.cpp
	TModifiedLocalGeodeticRF.cpp
	TReferenceEllipsoid.cpp
	TX0Y0HeProjection.cpp
	TXYHeProjection.cpp
	TXYHgProjection.cpp
)

# Create a variable containing all .h files:
set(ReferenceSurfaces_HEADERS 
	T3DLocalRefFrame.h
	TA2DPlus1MapProjection.h
	TA3DEuclideanRefFrame.h
	TAGeoidModel.h
	TAModifiedLocalAstronomicalRF.h
	TAReferenceFrame.h
	TCernGridGeoid.h
	TCernParabolicGeoid.h
	TCernSphereGeoid.h
	TGeodeticRefFrame.h
	TGeoidValues.h
	TGraphLocalAstronomicalRF.h
	TGraphMLARF.h
	TLambert93Projection.h
	TLV03Projection.h
	TLV95Projection.h
	TModifiedLocalAstronomicalRF.h
	TModifiedLocalGeodeticRF.h
	TNotInLepGridException.h
	TReferenceEllipsoid.h
	TReferenceFrameServer.h
	TRGF93CC46Projection.h
	TVGeoidModel.h
	TVReferenceFrame.h
	TX0Y0HeProjection.h
	TXYHeProjection.h
	TXYHgProjection.h
)

# Create a static library from sources:
add_library(ReferenceSurfaces STATIC ${ReferenceSurfaces_SOURCES} ${ReferenceSurfaces_HEADERS})