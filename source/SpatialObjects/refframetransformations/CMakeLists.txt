# Setting the include path - to include a given directory
include_directories (
	.
	${SURVEYLIB_INCLUDE_PATH}
	${NAGC_INCLUDE_PATH}
        ${REFRAME_INCLUDE_PATH}
)




##### This will correspond to one VS project!

# Create a variable containing all .cpp files:
set(RefFrameTransformations_SOURCES 
	TARefFrameTransformation.cpp
	TGC2LGTransformation.cpp
	TGC2MLATransformation.cpp
	THelmertRefFrameTransform.cpp
	TLA2LGTransformation.cpp
	TLG2GCTransformation.cpp
	TLG2LATransformation.cpp
	TMLA2GCTransformation.cpp
	TMLA2XYHeTransformation.cpp
	TMLA2XYHsTransformation.cpp
	TX0Y0He2XYHeTransformation.cpp
	TXYHe2MLATransformation.cpp
	TXYHe2X0Y0HeTransformation.cpp
	TXYHe2XYHgTransformation.cpp
	TXYHg2XYHeTransformation.cpp
	TXYHs2MLATransformation.cpp
	
	TLV95Transformation.cpp
	TLV03Transformation.cpp
	TRGF93ZoneTransformation.cpp
	TLambert93Transformation.cpp
)

# Create a variable containing all .h files:
set(RefFrameTransformations_HEADERS 
	${SURVEYLIB_INCLUDE_PATH}/TARefFrameTransformation.h
	${SURVEYLIB_INCLUDE_PATH}/TGC2LGTransformation.h
	${SURVEYLIB_INCLUDE_PATH}/TGC2MLATransformation.h
	${SURVEYLIB_INCLUDE_PATH}/THelmertRefFrameTransform.h
	${SURVEYLIB_INCLUDE_PATH}/TLA2LGTransformation.h
	${SURVEYLIB_INCLUDE_PATH}/TLG2GCTransformation.h
	${SURVEYLIB_INCLUDE_PATH}/TLG2LATransformation.h
	${SURVEYLIB_INCLUDE_PATH}/TMLA2GCTransformation.h
	${SURVEYLIB_INCLUDE_PATH}/TMLA2XYHeTransformation.h
	${SURVEYLIB_INCLUDE_PATH}/TMLA2XYHsTransformation.h
	${SURVEYLIB_INCLUDE_PATH}/TVRefFrameTransformation.h
	${SURVEYLIB_INCLUDE_PATH}/TVTransformation.h
	${SURVEYLIB_INCLUDE_PATH}/TX0Y0He2XYHeTransformation.h
	${SURVEYLIB_INCLUDE_PATH}/TXYHe2MLATransformation.h
	${SURVEYLIB_INCLUDE_PATH}/TXYHe2X0Y0HeTransformation.h
	${SURVEYLIB_INCLUDE_PATH}/TXYHe2XYHgTransformation.h
	${SURVEYLIB_INCLUDE_PATH}/TXYHg2XYHeTransformation.h
	${SURVEYLIB_INCLUDE_PATH}/TXYHs2MLATransformation.h
	
	${SURVEYLIB_INCLUDE_PATH}/TLV95Transformation.h
	${SURVEYLIB_INCLUDE_PATH}/TLV03Transformation.h
	${SURVEYLIB_INCLUDE_PATH}/TRGF93ZoneTransformation.h
	${SURVEYLIB_INCLUDE_PATH}/TLambert93Transformation.h
)

# Create a static library from sources:
add_library(RefFrameTransformations STATIC ${RefFrameTransformations_SOURCES} ${RefFrameTransformations_HEADERS})
install(FILES ${RefFrameTransformations_HEADERS} DESTINATION ${INSTALL_PREFIX}/include)
#####