cmake_minimum_required(VERSION 3.10)

# Create a variable containing all .hpp files:
set(tests_HEADERS
)
# Create a variable containing all .cpp files:
set(tests_SOURCES
	main.cpp
	test_Serializer_json.cpp
)

# Create an executable from sources:
add_executable(Serialization_Test
	${tests_HEADERS}
	${tests_SOURCES}
)
target_include_directories(Serialization_Test PRIVATE
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_SOURCE_DIR}
	# TUT
	${TUT_INCLUDE_PATH}
)
target_link_libraries(Serialization_Test
	Serialization
)

set(TEST_DIR "$<TARGET_FILE_DIR:Serialization_Test>")
if (MSVC)
	set(TEST_DIR "$<TARGET_FILE_DIR:Serialization_Test>/..")
endif()
add_test(
	NAME Serialization_Test
	COMMAND Serialization_Test
	WORKING_DIRECTORY "${TEST_DIR}"
)

source_group("Serialization_Test" FILES ${tests_HEADERS} ${tests_SOURCES})
