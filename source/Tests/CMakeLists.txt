include_directories (${TUT_INCLUDE_PATH}
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/MathematicalConcepts
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/SpatialSystems
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/ShortestPath
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/SpatialObj
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/ReferenceSurfaces
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/AffineTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/RefFrameTransformations
					${SURVEYLIB_ROOT}/source/ProjectFramework/headers/Converters
					${SURVEYLIB_ROOT}/source/ProjectFramework/headers/StreamFormatters
					${SURVEYLIB_ROOT}/source/SpatialObjDLL/headers
					${SURVEYLIB_ROOT}/source/Plugins
)

set(SurveyMain_Tests
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

set(SpatialObjects_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/SpatialObjects/UnitTests/testTAngle.cpp
	${CMAKE_CURRENT_LIST_DIR}/SpatialObjects/UnitTests/testTMatrix.cpp
	${CMAKE_CURRENT_LIST_DIR}/SpatialObjects/UnitTests/testQuadSupport.cpp
	${CMAKE_CURRENT_LIST_DIR}/SpatialObjects/UnitTests/testTransformations.cpp
	${CMAKE_CURRENT_LIST_DIR}/SpatialObjects/UnitTests/testTLV95Transformation.cpp
	${CMAKE_CURRENT_LIST_DIR}/SpatialObjects/UnitTests/testTLV03Transformation.cpp
	${CMAKE_CURRENT_LIST_DIR}/SpatialObjects/UnitTests/testTRGF93Transformation.cpp
	${CMAKE_CURRENT_LIST_DIR}/SpatialObjects/UnitTests/testTLambert93Transformation.cpp
	${CMAKE_CURRENT_LIST_DIR}/SpatialObjects/UnitTests/testTRefFrameInfo.cpp
	${CMAKE_CURRENT_LIST_DIR}/SpatialObjects/UnitTests/testTCernGridGeoid.cpp
	${CMAKE_CURRENT_LIST_DIR}/SpatialObjects/UnitTests/testAllTransformations.cpp
	${CMAKE_CURRENT_LIST_DIR}/SpatialObjects/UnitTests/testTCoordSysInfo.cpp
	${CMAKE_CURRENT_LIST_DIR}/SpatialObjects/UnitTests/testLocalSystems.cpp
)

set(SurveyLibDLLTests_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/SpatialObjects/SurveyLibDllTest/testSurveyLibDLL.cpp
)

set(ProjectFrameworkTests_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/ProjectFramework/UnitTests/testTPointFormat.cpp
)

set(PluginsTests_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/Plugins/testLogs.cpp
)

add_executable(UnitTests ${SurveyMain_Tests} ${SpatialObjects_SOURCES} ${SurveyLibDLLTests_SOURCES} ${ProjectFrameworkTests_SOURCES} ${PluginsTests_SOURCES})
# Specify the libraries to link against
target_link_libraries (UnitTests SpatialObjects SpatialObjDLL ProjectFramework ProjectFramework Plugins)

source_group("SpatialObjects" FILES ${SpatialObjects_SOURCES})
source_group("SurveyLibDLL" FILES ${SurveyLibDLLTests_SOURCES})
source_group("ProjectFramework" FILES ${ProjectFrameworkTests_SOURCES})
source_group("Plugins" FILES ${PluginsTests_SOURCES})
