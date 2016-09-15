# Setting the include path - to include a given directory (our library)
include_directories (${TUT_INCLUDE_PATH})

set(UnitTestsProjectFramework_SOURCES
	testTPointFormat.cpp
	main.cpp)

add_executable(UnitTestsProjectFramework ${UnitTestsProjectFramework_SOURCES}) 
# Specify the libraries to link against
target_link_libraries(UnitTestsProjectFramework ProjectFramework)