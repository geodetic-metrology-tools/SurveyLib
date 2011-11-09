# Setting the include path - to include a given directory (our library)
include_directories (
	${TUT_INCLUDE_PATH}
	${SURVEYLIB_INCLUDE_PATH}
	)



##### This will correspond to one VS project!

set(UnitTests_SOURCES

    testTAngle.cpp
	testTMatrix.cpp
	testQuadSupport.cpp

	testTransformations.cpp
	
	testTLV95Transformation.cpp
	
	testTLV03Transformation.cpp
	
	testTRGF93Transformation.cpp
	
	testTLambert93Transformation.cpp
	
	testTRefFrameInfo.cpp
	
	testTCernGridGeoid.cpp
	
	testAllTransformations.cpp
	
	testTCoordSysInfo.cpp

	main.cpp
)

add_executable(UnitTests ${UnitTests_SOURCES}) 
# Specify the libraries to link against
target_link_libraries (UnitTests SpatialObjectsLibrary)

# Copy the test files to the right path
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test_files
	DESTINATION ${STAGING_DIRECTORY}
)
#####