# Setting the include path - to include a given directory
include_directories (
	.
	${SURVEYLIB_INCLUDE_PATH}
)




##### This will correspond to one VS project!

# Create a variable containing all .cpp files:
set(InstrumentStations_SOURCES 
	EDM.cpp
	Level.cpp
	Scale.cpp
	TAFreeInstrument.cpp
	TAInstrument.cpp
	TTheodolite.cpp
)

# Create a variable containing all .h files:
set(InstrumentStations_HEADERS 
	${SURVEYLIB_INCLUDE_PATH}/EDM.h
	${SURVEYLIB_INCLUDE_PATH}/EDMStation.h
	${SURVEYLIB_INCLUDE_PATH}/EDMTarget.h
	${SURVEYLIB_INCLUDE_PATH}/Gyroscope.h
	${SURVEYLIB_INCLUDE_PATH}/GyroscopeStation.h
	${SURVEYLIB_INCLUDE_PATH}/Level.h
	${SURVEYLIB_INCLUDE_PATH}/LevelStation.h
	${SURVEYLIB_INCLUDE_PATH}/Scale.h
	${SURVEYLIB_INCLUDE_PATH}/Staff.h
	${SURVEYLIB_INCLUDE_PATH}/Station.h
	${SURVEYLIB_INCLUDE_PATH}/TAFreeInstrument.h
	${SURVEYLIB_INCLUDE_PATH}/TAInstrument.h
	${SURVEYLIB_INCLUDE_PATH}/Target.h
	${SURVEYLIB_INCLUDE_PATH}/TheodoliteStation.h
	${SURVEYLIB_INCLUDE_PATH}/TheodoliteTarget.h
	${SURVEYLIB_INCLUDE_PATH}/TTheodolite.h
)

# Create a static library from sources:
add_library(InstrumentStations STATIC ${InstrumentStations_SOURCES} ${InstrumentStations_HEADERS})
install(FILES ${InstrumentStations_HEADERS} DESTINATION ${INSTALL_PREFIX}/include)
#####