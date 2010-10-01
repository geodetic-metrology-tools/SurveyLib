# Setting the include path - to include a given directory
include_directories (
	.
	${SURVEYLIB_INCLUDE_PATH}
	${NAGC_INCLUDE_PATH}
)




##### This will correspond to one VS project!

# Create a variable containing all .cpp files:
set(ConstraintMeasurements_SOURCES 
	TOrientationCnstr.cpp
	TRadialOffsetCnstr.cpp
)

# Create a variable containing all .h files:
set(ConstraintMeasurements_HEADERS 
	${SURVEYLIB_INCLUDE_PATH}/TOrientationCnstr.h
	${SURVEYLIB_INCLUDE_PATH}/TRadialOffsetCnstr.h
)

# Create a static library from sources:
add_library(ConstraintMeasurements STATIC ${ConstraintMeasurements_SOURCES} ${ConstraintMeasurements_HEADERS})
install(FILES ${ConstraintMeasurements_HEADERS} DESTINATION ${INSTALL_PREFIX}/include)
#####