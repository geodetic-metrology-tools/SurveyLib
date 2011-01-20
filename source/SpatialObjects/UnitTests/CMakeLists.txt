# Setting the include path - to include a given directory (our library)
include_directories (
	${TUT_INCLUDE_PATH}
	${SURVEYLIB_INCLUDE_PATH}
	${NAGC_INCLUDE_PATH}
	)


# Where to look for the libraries to link against
link_directories (
	${NAGC_LIBRARY_DIR}
)


##### This will correspond to one VS project!

set(UnitTests_SOURCES

    testTSparseMatrix.cpp

	main.cpp
)

add_executable(UnitTests ${UnitTests_SOURCES}) 
# Specify the libraries to link against
target_link_libraries (UnitTests
	SpatialObjectsLibrary
	nagc
)

install(FILES ${NAGC_LIBRARY_DIR}/nagc.dll
	DESTINATION ${STAGING_DIRECTORY}
)
# Copy the test files to the right path
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test_files
	DESTINATION ${STAGING_DIRECTORY}
)
