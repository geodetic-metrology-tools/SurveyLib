configure_file (
  SurveryLibVersion.in
  SurveryLibVersion.h
)

INCLUDE(SourceSurveyLib.cmake)

ADD_SUBDIRECTORY(Tests)