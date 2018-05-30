include_directories(${CMAKE_SOURCE_DIR}
	${SURVEYLIB_ROOT}/source/Plugins
)

set(PLUG_HEADERS
	Logs/ConsoleLogHandler.hpp
	Logs/FileLogHandler.hpp
	Logs/ILogHandler.hpp
	Logs/Logger.hpp
	Logs/LogMessage.hpp
)

set(PLUG_SOURCES
	Logs/ConsoleLogHandler.cpp
	Logs/FileLogHandler.cpp
	Logs/Logger.cpp
	Logs/LogMessage.cpp
)

if (MSVC)
	# Define VS folders:
	file(GLOB PLUGINS_MSVC	Logs/*)
	source_group("Plugins\\Logs"	FILES ${PLUGINS_MSVC})
endif()

#Create a static library from the object files
ADD_LIBRARY(Plugins STATIC ${PLUG_HEADERS} ${PLUG_SOURCES})
