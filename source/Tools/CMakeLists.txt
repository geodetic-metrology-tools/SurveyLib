# set include directories needed by this library
include_directories(
	${CMAKE_CURRENT_LIST_DIR}/headers
	${SURVEYLIB_ROOT}/source/Logs
)

# Create a variable containing all .cpp files:
set(Tools_SOURCES 
	${CMAKE_CURRENT_LIST_DIR}/sources/Behavior.cpp
	${CMAKE_CURRENT_LIST_DIR}/sources/FileUtils.cpp
	${CMAKE_CURRENT_LIST_DIR}/sources/NumericUtils.cpp
	${CMAKE_CURRENT_LIST_DIR}/sources/ProjectPath.cpp
	${CMAKE_CURRENT_LIST_DIR}/sources/Timer.cpp
	${CMAKE_CURRENT_LIST_DIR}/sources/StringManager.cpp
)

# Create a variable containing all .h files:
set(Tools_HEADERS 
	${CMAKE_CURRENT_LIST_DIR}/headers/Behavior.h
	${CMAKE_CURRENT_LIST_DIR}/headers/FileUtils.h
	${CMAKE_CURRENT_LIST_DIR}/headers/NumericUtils.h
	${CMAKE_CURRENT_LIST_DIR}/headers/ProjectPath.h
	${CMAKE_CURRENT_LIST_DIR}/headers/SimpleTimer.h
	${CMAKE_CURRENT_LIST_DIR}/headers/StringManager.h
	${CMAKE_CURRENT_LIST_DIR}/headers/TStatusObject.h
)

# Create a static library from sources:
add_library(Tools STATIC ${Tools_SOURCES} ${Tools_HEADERS})

# Link static libraries to the current one
target_link_libraries(Tools Logs)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(Tools stdc++fs)
endif()

# needed for linux compilation
set_target_properties(Tools PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Define IDE folders:
set_target_properties(Tools PROPERTIES FOLDER "SurveyLib")
