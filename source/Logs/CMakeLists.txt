set(LOGS_HEADERS
	ConsoleLogHandler.hpp
	FileLogHandler.hpp
	ILogHandler.hpp
	Logger.hpp
	LogLibGlobals.hpp
	LogMessage.hpp
)

set(LOGS_SOURCES
	ConsoleLogHandler.cpp
	FileLogHandler.cpp
	Logger.cpp
	LogMessage.cpp
)

#Create a static library from the object files
add_library(Logs STATIC ${LOGS_HEADERS} ${LOGS_SOURCES})
target_include_directories(Logs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(Logs stdc++fs)
endif()
# Define VS folders:
file(GLOB LOGS_LOGS ${CMAKE_CURRENT_SOURCE_DIR}/*)
source_group("Logs" FILES ${LOGS_LOGS})
set_target_properties(Logs PROPERTIES FOLDER "SurveyLib")


install(TARGETS Logs
  RUNTIME
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/logs"
)
