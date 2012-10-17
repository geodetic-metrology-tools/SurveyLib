# Setting the include path - to include a given directory (our library)
include_directories (
	${TUT_INCLUDE_PATH}
	${SURVEYLIB_INCLUDE_PATH}
	)


##### This will correspond to one VS project!

set(SurveyLibDllTest_SOURCES
	testSurveyLibDLL.cpp
	main.cpp
)

add_executable(SurveyLibDllTest ${SurveyLibDllTest_SOURCES}) 
target_link_libraries(SurveyLibDllTest 
	SurveyLib
)
