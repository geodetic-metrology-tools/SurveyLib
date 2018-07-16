include_directories(${CMAKE_SOURCE_DIR}
	${SURVEYLIB_ROOT}/source/Logs
)

set(LOGS_HEADERS
	${CMAKE_CURRENT_LIST_DIR}/ConsoleLogHandler.hpp
	${CMAKE_CURRENT_LIST_DIR}/FileLogHandler.hpp
	${CMAKE_CURRENT_LIST_DIR}/ILogHandler.hpp
	${CMAKE_CURRENT_LIST_DIR}/Logger.hpp
	${CMAKE_CURRENT_LIST_DIR}/LogMessage.hpp
)

set(LOGS_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/ConsoleLogHandler.cpp
	${CMAKE_CURRENT_LIST_DIR}/FileLogHandler.cpp
	${CMAKE_CURRENT_LIST_DIR}/Logger.cpp
	${CMAKE_CURRENT_LIST_DIR}/LogMessage.cpp
)

# Define VS folders:
file(GLOB LOGS_LOGS	Logs/*)
source_group("Logs"	FILES ${LOGS_LOGS})

#Create a static library from the object files
add_library(Logs STATIC ${LOGS_HEADERS} ${LOGS_SOURCES})
