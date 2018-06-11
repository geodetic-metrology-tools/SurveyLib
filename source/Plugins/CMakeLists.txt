include_directories(${CMAKE_SOURCE_DIR}
	${SURVEYLIB_ROOT}/source/SpatialObjects/headers/MathematicalConcepts
	${SURVEYLIB_ROOT}/source/Plugins
)

set(PLUG_HEADERS
	Logs/ConsoleLogHandler.hpp
	Logs/FileLogHandler.hpp
	Logs/ILogHandler.hpp
	Logs/Logger.hpp
	Logs/LogMessage.hpp
	ShareablePoints/ShareablePosition.hpp
	ShareablePoints/ShareableFrame.hpp
	ShareablePoints/ShareableParams.hpp
	ShareablePoints/ShareableExtraInfo.hpp
	ShareablePoints/ShareablePoint.hpp
	ShareablePoints/ShareablePointsList.hpp
)

set(PLUG_SOURCES
	Logs/ConsoleLogHandler.cpp
	Logs/FileLogHandler.cpp
	Logs/Logger.cpp
	Logs/LogMessage.cpp
	ShareablePoints/ShareablePosition.cpp
	ShareablePoints/ShareableFrame.cpp
	ShareablePoints/ShareablePointsList.cpp
)

if (MSVC)
	# Define VS folders:
	file(GLOB PLUGINS_LOGS	Logs/*)
	source_group("Plugins\\Logs"	FILES ${PLUGINS_LOGS})
	file(GLOB PLUGINS_SHAREPOINTS	ShareablePoints/*)
	source_group("Plugins\\ShareablePoints"	FILES ${PLUGINS_SHAREPOINTS})
endif()

#Create a static library from the object files
ADD_LIBRARY(Plugins STATIC ${PLUG_HEADERS} ${PLUG_SOURCES})
