# Create a variable containing all .cpp files:
set(ProjectData_SOURCES 
	TADataSet.cpp
	TDataParameters.cpp
	TFileParameters.cpp
	TPtListBroadcaster.cpp
	TWorkingConstants.cpp
	TWorkingConstraints.cpp
	TWorkingInstruments.cpp
	TWorkingLines.cpp
	TWorkingPlanes.cpp
	TWorkingPoints.cpp
	TWorkingStations.cpp
	
	# TWorkingTargetObjects.cpp
)

# Create a variable containing all .h files:
set(ProjectData_HEADERS 
	${SURVEYLIB_INCLUDE_PATH}/TADataSet.h
	${SURVEYLIB_INCLUDE_PATH}/TDataParameters.h
	${SURVEYLIB_INCLUDE_PATH}/TFileParameters.h
	${SURVEYLIB_INCLUDE_PATH}/TPtListBroadcaster.h
	${SURVEYLIB_INCLUDE_PATH}/TVPtListListener.h
	${SURVEYLIB_INCLUDE_PATH}/TWorkingConstants.h
	${SURVEYLIB_INCLUDE_PATH}/TWorkingConstraints.h
	${SURVEYLIB_INCLUDE_PATH}/TWorkingInstruments.h
	${SURVEYLIB_INCLUDE_PATH}/TWorkingLines.h
	${SURVEYLIB_INCLUDE_PATH}/TWorkingPlanes.h
	${SURVEYLIB_INCLUDE_PATH}/TWorkingPoints.h
	${SURVEYLIB_INCLUDE_PATH}/TWorkingROMs.h
	${SURVEYLIB_INCLUDE_PATH}/TWorkingStations.h
	
	# ${SURVEYLIB_INCLUDE_PATH}/TWorkingTargetObjects.h
)

# Create a static library from sources:
add_library(ProjectData STATIC ${ProjectData_SOURCES} ${ProjectData_HEADERS})
install(FILES ${ProjectData_HEADERS} DESTINATION ${INSTALL_PREFIX}/include)
#####