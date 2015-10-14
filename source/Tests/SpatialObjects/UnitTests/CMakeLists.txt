include_directories (${TUT_INCLUDE_PATH}
					${SURVEYLIB_ROOT}/source/SpatialObjects/MathematicalConcepts
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialSystems
					${SURVEYLIB_ROOT}/source/SpatialObjects/ShortestPath
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialObj
					${SURVEYLIB_ROOT}/source/SpatialObjects/ReferenceSurfaces
					${SURVEYLIB_ROOT}/source/SpatialObjects/AffineTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/RefFrameTransformations
					${SURVEYLIB_ROOT}/source/ProjectFramework/Converters
					${SURVEYLIB_ROOT}/source/ProjectFramework/StreamFormatters)

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
target_link_libraries (UnitTests ${SPATIAL_LIBRARIES})

# Copy the test files to the right path
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test_files
		DESTINATION ${STAGING_DIRECTORY}
)