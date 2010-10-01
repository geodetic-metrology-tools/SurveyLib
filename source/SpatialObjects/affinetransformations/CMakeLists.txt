# Setting the include path - to include a given directory
include_directories (
	.
	${SURVEYLIB_INCLUDE_PATH}
	${NAGC_INCLUDE_PATH}
)




##### This will correspond to one VS project!

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
	${SURVEYLIB_INCLUDE_PATH}/TAAffineTransformation.h
	${SURVEYLIB_INCLUDE_PATH}/TAffineTransformWrapper.h
	${SURVEYLIB_INCLUDE_PATH}/TCompositeAffTransform.h
	${SURVEYLIB_INCLUDE_PATH}/THelmertTransformation.h
	${SURVEYLIB_INCLUDE_PATH}/TReflection.h
	${SURVEYLIB_INCLUDE_PATH}/TRotation.h
	${SURVEYLIB_INCLUDE_PATH}/TScaleFactor.h
	${SURVEYLIB_INCLUDE_PATH}/TTranslation.h
	${SURVEYLIB_INCLUDE_PATH}/TVAffineTransformation.h
)

# Create a static library from sources:
add_library(AffineTransformations STATIC ${AffineTransformations_SOURCES} ${AffineTransformations_HEADERS})
install(FILES ${AffineTransformations_HEADERS} DESTINATION ${INSTALL_PREFIX}/include)
#####