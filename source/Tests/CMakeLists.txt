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
	${CMAKE_CURRENT_LIST_DIR}/SpatialObjects/UnitTests/testTrfTransformation.cpp
	${CMAKE_CURRENT_LIST_DIR}/SpatialObjects/UnitTests/testTCernGridGeoid.cpp
	${CMAKE_CURRENT_LIST_DIR}/SpatialObjects/UnitTests/testAllTransformations.cpp
	${CMAKE_CURRENT_LIST_DIR}/SpatialObjects/UnitTests/testTCoordSysInfo.cpp
	${CMAKE_CURRENT_LIST_DIR}/SpatialObjects/UnitTests/testLocalSystems.cpp
	${CMAKE_CURRENT_LIST_DIR}/SpatialObjects/UnitTests/testTGeodetic2Mercator.cpp
)

set(SurveyLibDLLTests_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/SpatialObjects/SurveyLibDllTest/testSurveyLibDLL.cpp
)

set(ProjectFrameworkTests_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/ProjectFramework/UnitTests/testTPointFormat.cpp
)

set(PluginsTests_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/Plugins/testLogs.cpp
	${CMAKE_CURRENT_LIST_DIR}/Plugins/testShareablePoints.cpp
)

set(ToolsTests_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/Tools/testFileUtils.cpp
	${CMAKE_CURRENT_LIST_DIR}/Tools/testStringManager.cpp
)

add_executable(UnitTests
	${SurveyMain_Tests}
	${SpatialObjects_SOURCES}
	${SurveyLibDLLTests_SOURCES}
	${ProjectFrameworkTests_SOURCES}
	${PluginsTests_SOURCES}
	${ToolsTests_SOURCES}
)
target_include_directories(UnitTests PRIVATE
	# TUT
	${TUT_INCLUDE_PATH}
)
target_link_libraries (UnitTests
	SpatialObjects
	SpatialObjDLL
	ProjectFramework
	Plugins
	Logs
	Tools
)

add_test(
	NAME UnitTests
	COMMAND $<TARGET_FILE_NAME:UnitTests>
	WORKING_DIRECTORY $<TARGET_FILE_DIR:UnitTests>
)

source_group("SpatialObjects" FILES ${SpatialObjects_SOURCES})
source_group("SurveyLibDLL" FILES ${SurveyLibDLLTests_SOURCES})
source_group("ProjectFramework" FILES ${ProjectFrameworkTests_SOURCES})
source_group("Plugins" FILES ${PluginsTests_SOURCES})
source_group("Tools" FILES ${ToolsTests_SOURCES})

if(USE_SWISSTOPO)
	copyReframeDLL(UnitTests)
endif()
