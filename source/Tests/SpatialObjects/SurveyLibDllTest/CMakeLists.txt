include_directories (${TUT_INCLUDE_PATH})

set(SurveyLibDllTest_SOURCES
	testSurveyLibDLL.cpp
	main.cpp
)

add_executable(SurveyLibDllTest ${SurveyLibDllTest_SOURCES}) 
target_link_libraries(SurveyLibDllTest SurveyLib)
