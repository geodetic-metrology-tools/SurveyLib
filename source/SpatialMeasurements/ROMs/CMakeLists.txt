# Setting the include path - to include a given directory
include_directories (
	.
	${SURVEYLIB_INCLUDE_PATH}
)




##### This will correspond to one VS project!

# Create a variable containing all .cpp files:
set(ROMs_SOURCES 
	OffsetToSpatialLineROM.cpp
)

# Create a variable containing all .h files:
set(ROMs_HEADERS 
	${SURVEYLIB_INCLUDE_PATH}/ObservationROM.h
	${SURVEYLIB_INCLUDE_PATH}/OffsetToSpatialLineROM.h
	${SURVEYLIB_INCLUDE_PATH}/OffsetToTheodolitePlaneROM.h
	${SURVEYLIB_INCLUDE_PATH}/OffsetToVerticalLineROM.h
	${SURVEYLIB_INCLUDE_PATH}/TheodoliteStationROM.h
	${SURVEYLIB_INCLUDE_PATH}/VerticalDistanceROM.h
)

# Create a static library from sources:
add_library(ROMs STATIC ${ROMs_SOURCES} ${ROMs_HEADERS})
install(FILES ${ROMs_HEADERS} DESTINATION ${INSTALL_PREFIX}/include)
#####