include_directories(
	${CMAKE_CURRENT_LIST_DIR}
)

set(LOGS_HEADERS
	${CMAKE_CURRENT_LIST_DIR}/ConsoleLogHandler.hpp
	${CMAKE_CURRENT_LIST_DIR}/FileLogHandler.hpp
	${CMAKE_CURRENT_LIST_DIR}/ILogHandler.hpp
	${CMAKE_CURRENT_LIST_DIR}/Logger.hpp
	${CMAKE_CURRENT_LIST_DIR}/LogLibGlobals.hpp
	${CMAKE_CURRENT_LIST_DIR}/LogMessage.hpp
)

set(LOGS_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/ConsoleLogHandler.cpp
	${CMAKE_CURRENT_LIST_DIR}/FileLogHandler.cpp
	${CMAKE_CURRENT_LIST_DIR}/Logger.cpp
	${CMAKE_CURRENT_LIST_DIR}/LogMessage.cpp
)

#Create a static library from the object files
add_library(Logs STATIC ${LOGS_HEADERS} ${LOGS_SOURCES})
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(Logs stdc++fs)
endif()

# Define VS folders:
file(GLOB LOGS_LOGS ${CMAKE_CURRENT_LIST_DIR}/*)
source_group("Logs" FILES ${LOGS_LOGS})
set_target_properties(Logs PROPERTIES FOLDER "SurveyLib")
