# set include directories needed by this library
include_directories(${SURVEYLIB_ROOT}/source/SpatialObjects/AffineTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/MathematicalConcepts
					${SURVEYLIB_ROOT}/source/SpatialObjects/ReferenceSurfaces
					${SURVEYLIB_ROOT}/source/SpatialObjects/RefFrameTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/ShortestPath
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialObj
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialSystems)

# Create a variable containing all .cpp files:
set(AffineTransformations_SOURCES 
	TAAffineTransformation.cpp
	TAffineTransformWrapper.cpp
	TCompositeAffTransform.cpp
	THelmertTransformation.cpp
	TReflection.cpp
	TRotation.cpp
	TScaleFactor.cpp
	TTranslation.cpp
)

# Create a variable containing all .h files:
set(AffineTransformations_HEADERS 
	TAAffineTransformation.h
	TAffineTransformWrapper.h
	TCompositeAffTransform.h
	THelmertTransformation.h
	TReflection.h
	TRotation.h
	TScaleFactor.h
	TTranslation.h
	TVAffineTransformation.h
)

# Create a static library from sources:
add_library(AffineTransformations STATIC ${AffineTransformations_SOURCES} ${AffineTransformations_HEADERS})