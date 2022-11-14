configure_file (
	${CMAKE_CURRENT_SOURCE_DIR}/SurveryLibVersion.in
	${CMAKE_CURRENT_SOURCE_DIR}/SurveryLibVersion.h
)

INCLUDE(SourceSurveyLib.cmake)

ADD_SUBDIRECTORY(Tests)