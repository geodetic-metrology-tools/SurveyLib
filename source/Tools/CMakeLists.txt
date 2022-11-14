# Create a variable containing all .cpp files:
set(Tools_SOURCES 
	sources/Behavior.cpp
	sources/StringManager.cpp
	sources/FileUtils.cpp
)

# Create a variable containing all .h files:
set(Tools_HEADERS 
	headers/TStatusObject.h
	headers/Behavior.h
	headers/StringManager.h
	headers/FileUtils.h
)

# Create a static library from sources:
add_library(Tools STATIC ${Tools_SOURCES} ${Tools_HEADERS})
target_include_directories(Tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)

# Link static libraries to the current one
target_link_libraries(Tools Logs)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(Tools stdc++fs)
endif()

# needed for linux compilation
set_target_properties(Tools PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Define IDE folders:
set_target_properties(Tools PROPERTIES FOLDER "SurveyLib")
