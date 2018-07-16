# set include directories needed by this library
include_directories(${SURVEYLIB_ROOT}/source/Tools/headers
                    ${SURVEYLIB_ROOT}/source/Logs)

# Create a variable containing all .cpp files:
set(Tools_SOURCES 
    sources/Behavior.cpp
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

# Link static libraries to the current one
target_link_libraries(Tools Logs)

# needed for linux compilation
set_target_properties(Tools PROPERTIES POSITION_INDEPENDENT_CODE ON)
