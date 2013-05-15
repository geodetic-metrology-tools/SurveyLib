# Create a variable containing all .cpp files:
set(BCAM_SOURCES
	TBCAMCalibrationDB.cpp
	TBCAMConfig.cpp
	TBCAMData.cpp
	TBCAMCalculations.cpp
)

# Create a variable containing all .h files:
set(BCAM_HEADERS 
	${SURVEYLIB_INCLUDE_PATH}/TBCAMCalibrationDB.h
	${SURVEYLIB_INCLUDE_PATH}/TBCAMConfig.h
	${SURVEYLIB_INCLUDE_PATH}/TBCAMData.h
	${SURVEYLIB_INCLUDE_PATH}/TBCAMCalculations.h
	${SURVEYLIB_INCLUDE_PATH}/BCAM.h # Facade class for BCAM access
)

# Create a static library from sources:
add_library(BCAM STATIC ${BCAM_SOURCES} ${BCAM_HEADERS})