# Create a variable containing all .cpp files:
set(ReferenceSurfaces_SOURCES 
	T3DLocalRefFrame.cpp
	TA2DPlus1MapProjection.cpp
	#TA2DXYRefFrame.cpp
	TA3DEuclideanRefFrame.cpp
	TAGeoidModel.cpp
	TAModifiedLocalAstronomicalRF.cpp
	TAReferenceFrame.cpp
	TCernGridGeoid.cpp
	TCernParabolicGeoid.cpp
	TCernSphereGeoid.cpp
	#TCoordinateSystem.cpp
	#TEuclideanRefFrame.cpp
	#TEuclidianReferenceFrame.cpp
	TGeodeticRefFrame.cpp
	TGeoid.cpp
	TGeoidValues.cpp
	TGraphLocalAstronomicalRF.cpp
	TGraphMLARF.cpp
	#TLocalGeodeticRefFrame.cpp
	TModifiedLocalAstronomicalRF.cpp
	TModifiedLocalGeodeticRF.cpp
	TReferenceEllipsoid.cpp
	#TReferenceFrameServer.cpp
	TX0Y0HeProjection.cpp
	TXYHeProjection.cpp
	TXYHgProjection.cpp
)

# Create a variable containing all .h files:
set(ReferenceSurfaces_HEADERS 
	T3DLocalRefFrame.h
	TA2DPlus1MapProjection.h
	TA2DXYRefFrame.h
	TA3DEuclideanRefFrame.h
	TAGeoidModel.h
	TAModifiedLocalAstronomicalRF.h
	TAReferenceFrame.h
	TCernGridGeoid.h
	TCernParabolicGeoid.h
	TCernSphereGeoid.h
	#TCoordinateSystem.h
	#TEuclidianReferenceFrame.h
	TGeodeticRefFrame.h
	TGeoid.h
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