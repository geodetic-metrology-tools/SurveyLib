# set include directories needed by this library
include_directories(${SURVEYLIB_ROOT}/source/Tools/headers)

# Create a variable containing all .cpp files:
set(Tools_SOURCES 
	sources/Behavior.cpp
)

# Create a variable containing all .h files:
set(Tools_HEADERS 
	headers/Behavior.h
	headers/StringManager.h
)

# Create a static library from sources:
add_library(Tools STATIC ${Tools_SOURCES} ${Tools_HEADERS})

# Link static libraries to the current one
# (No libraries to link)

# needed for linux compilation
set_target_properties(Tools PROPERTIES POSITION_INDEPENDENT_CODE ON)
