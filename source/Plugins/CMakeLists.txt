set(PLUG_HEADERS
	ShareablePoints/IShareablePointsListIO.hpp
	ShareablePoints/ShareableExtraInfos.hpp
	ShareablePoints/ShareableFrame.hpp
	ShareablePoints/ShareableParams.hpp
	ShareablePoints/ShareablePoint.hpp
	ShareablePoints/ShareablePointsList.hpp
	ShareablePoints/ShareablePosition.hpp
	ShareablePoints/SPIOException.hpp
)

set(PLUG_SOURCES
	ShareablePoints/IShareablePointsListIO.cpp
	ShareablePoints/ShareableFrame.cpp
	ShareablePoints/ShareablePointsList.cpp
	ShareablePoints/ShareablePosition.cpp
)

#Create a static library from the object files
add_library(Plugins STATIC ${PLUG_HEADERS} ${PLUG_SOURCES})
target_include_directories(Plugins PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Define IDE folders:
file(GLOB PLUGINS_SHAREPOINTS ${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/*)
source_group("ShareablePoints" FILES ${PLUGINS_SHAREPOINTS})
set_target_properties(Plugins PROPERTIES FOLDER "SurveyLib")
