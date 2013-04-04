# Create a variable containing all .cpp files:
set(ROMs_SOURCES 
	T2DOffsetROM.cpp
	TARoundOfMeas.cpp
	TARoundOfMeasListener.cpp
	TAUnreferencedROM.cpp
	TGyroOrientationROM.cpp
	THorAngleROM.cpp
	THorizontalDistROM.cpp
	TSpatialDistROM.cpp
	TVerticalDistROM.cpp
	TVRoundOfMeasListener.cpp
	TZenithDistROM.cpp
)

# Create a variable containing all .h files:
set(ROMs_HEADERS 
	${SURVEYLIB_INCLUDE_PATH}/T2DOffsetROM.h
	${SURVEYLIB_INCLUDE_PATH}/TARoundOfMeas.h
	${SURVEYLIB_INCLUDE_PATH}/TARoundOfMeasListener.h
	${SURVEYLIB_INCLUDE_PATH}/TAUnreferencedROM.h
	${SURVEYLIB_INCLUDE_PATH}/TGyroOrientationROM.h
	${SURVEYLIB_INCLUDE_PATH}/THorAngleROM.h
	${SURVEYLIB_INCLUDE_PATH}/THorizontalDistROM.h
	${SURVEYLIB_INCLUDE_PATH}/TSpatialDistROM.h
	${SURVEYLIB_INCLUDE_PATH}/TVerticalDistROM.h
	${SURVEYLIB_INCLUDE_PATH}/TVRoundOfMeasListener.h
	${SURVEYLIB_INCLUDE_PATH}/TZenithDistROM.h
)

# Create a static library from sources:
add_library(ROMs STATIC ${ROMs_SOURCES} ${ROMs_HEADERS})
install(FILES ${ROMs_HEADERS} DESTINATION ${INSTALL_PREFIX}/include)
#####