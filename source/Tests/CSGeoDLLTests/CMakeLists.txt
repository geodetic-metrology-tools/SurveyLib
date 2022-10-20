set(TEST_NAME "CSGeoDLLTests")

set(CSGEODLL_UNIT_TEST "${CMAKE_SOURCE_DIR}/CSGeoDLLTests")
set(CSGEODLL_UNIT_TEST_SOURCES "${CSGEODLL_UNIT_TEST}/sources")

set(CSGEO_DLL "${CMAKE_SOURCE_DIR}/${DLL_NAME}")
set(CSGEO_DLL_HEADER "${CSGEO_DLL}/headers")

# Create a variable containing all .cpp files:
file(GLOB testDLL_SOURCES
		"${CSGEODLL_UNIT_TEST_SOURCES}/*.cpp"
)

add_executable(${TEST_NAME} ${testDLL_SOURCES})

# Specify the libraries to link against
target_link_libraries (${TEST_NAME} 
	${DLL_NAME}
)

target_include_directories(${TEST_NAME} PRIVATE
	${CSGEO_DLL_HEADER}
	# TUT
	${TUT_INCLUDE_PATH}
)

if(USE_SWISSTOPO)
	copyReframeDLL("${TEST_NAME}")
endif()

add_test(
	NAME ${TEST_NAME}
	COMMAND $<TARGET_FILE_NAME:${TEST_NAME}>
	WORKING_DIRECTORY $<TARGET_FILE_DIR:${TEST_NAME}>
)

## Copy test files to the build directory
file(GLOB COPY_TESTFILES LIST_DIRECTORIES false "${CSGEODLL_UNIT_TEST}/test_files/*")
foreach (test_file ${COPY_TESTFILES})
	post_build_copy_dlls(${TEST_NAME} "${test_file}" "${test_file}" "test_files")
	file(COPY "${test_file}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/test_files")
endforeach()

if (WIN32)
## Copy the needed DLLs to the runtime directory

set (debug_files_str "${CSGEO_ROOT}/build/${DLL_NAME}/Debug/${DLL_NAME}.dll")
set (release_files_str "${CSGEO_ROOT}/build/${DLL_NAME}/Release/${DLL_NAME}.dll")
add_custom_command(TARGET ${TEST_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	$<$<CONFIG:debug>:"${debug_files_str}">$<$<CONFIG:release>:"${release_files_str}">
	$<TARGET_FILE_DIR:${TEST_NAME}>
)

endif()
##
