# Setting the include path - to include a given directory
include_directories (
	.
	${SURVEYLIB_INCLUDE_PATH}
	${NAGC_INCLUDE_PATH}
)




##### This will correspond to one VS project!

# Create a variable containing all .cpp files:
set(InstrumentStations_SOURCES 
	TAFreeInstrumentStation.cpp
	TAInstrumentStation.cpp
	TDistMeasStation.cpp
	TLevelStation.cpp
	TTheodoliteStation.cpp
	TWPSStation.cpp
	TWTWDistStation.cpp
)

# Create a variable containing all .h files:
set(InstrumentStations_HEADERS 
	${SURVEYLIB_INCLUDE_PATH}/TAFreeInstrumentStation.h
	${SURVEYLIB_INCLUDE_PATH}/TAInstrumentStation.h
	${SURVEYLIB_INCLUDE_PATH}/TDistMeasStation.h
	${SURVEYLIB_INCLUDE_PATH}/TLevelStation.h
	${SURVEYLIB_INCLUDE_PATH}/TTheodoliteStation.h
	${SURVEYLIB_INCLUDE_PATH}/TWPSStation.h
	${SURVEYLIB_INCLUDE_PATH}/TWTWDistStation.h
)

# Create a static library from sources:
add_library(InstrumentStations STATIC ${InstrumentStations_SOURCES} ${InstrumentStations_HEADERS})
install(FILES ${InstrumentStations_HEADERS} DESTINATION ${INSTALL_PREFIX}/include)
#####