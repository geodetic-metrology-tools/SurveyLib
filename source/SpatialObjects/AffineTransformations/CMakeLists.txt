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