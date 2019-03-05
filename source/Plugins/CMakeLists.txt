include_directories(
	${CMAKE_CURRENT_LIST_DIR}
)

set(PLUG_HEADERS
	${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/IShareablePointsListIO.hpp
	${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/ShareableExtraInfos.hpp
	${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/ShareableFrame.hpp
	${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/ShareableParams.hpp
	${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/ShareablePoint.hpp
	${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/ShareablePointsList.hpp
	${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/ShareablePosition.hpp
	${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/SPIOException.hpp
)

set(PLUG_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/IShareablePointsListIO.cpp
	${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/ShareableFrame.cpp
	${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/ShareablePointsList.cpp
	${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/ShareablePosition.cpp
)

#Create a static library from the object files
add_library(Plugins STATIC ${PLUG_HEADERS} ${PLUG_SOURCES})

# Define IDE folders:
file(GLOB PLUGINS_SHAREPOINTS ${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/*)
source_group("ShareablePoints" FILES ${PLUGINS_SHAREPOINTS})
set_target_properties(Plugins PROPERTIES FOLDER "SurveyLib")
