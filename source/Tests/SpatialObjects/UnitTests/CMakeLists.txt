include_directories (${TUT_INCLUDE_PATH}
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/MathematicalConcepts
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/SpatialSystems
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/ShortestPath
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/SpatialObj
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/ReferenceSurfaces
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/AffineTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/RefFrameTransformations
					${SURVEYLIB_ROOT}/source/ProjectFramework/headers/Converters
					${SURVEYLIB_ROOT}/source/ProjectFramework/headers/StreamFormatters)

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
	testLocalSystems.cpp
	main.cpp
)

add_executable(UnitTests ${UnitTests_SOURCES}) 
# Specify the libraries to link against
target_link_libraries (UnitTests SpatialObjects SpatialObjDLL ProjectFramework)

# Copy the test files to the right path
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test_files
		DESTINATION ${STAGING_DIRECTORY}
)