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

	testTMatrix.cpp

	testTransformations.cpp
	
	testTLV95Transformation.cpp
	
	testTLV03Transformation.cpp
	
	testTRefFrameInfo.cpp

	main.cpp
)

add_executable(UnitTests ${UnitTests_SOURCES}) 
# Specify the libraries to link against
target_link_libraries (UnitTests
	SpatialObjectsLibrary
	nagc
)

# Copy the needed DLLs to the runtime directory
install(FILES ${NAGC_LIBRARY_DIR}/nagc.dll
	DESTINATION ${STAGING_DIRECTORY}
)
# Copy the test files to the right path
#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test_files
#	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}
#)
#####