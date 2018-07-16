include_directories(${CMAKE_SOURCE_DIR}
	${SURVEYLIB_ROOT}/source/Plugins
)

set(PLUG_HEADERS
	${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/ShareablePosition.hpp
	${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/ShareableFrame.hpp
	${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/ShareableParams.hpp
	${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/ShareableExtraInfo.hpp
	${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/ShareablePoint.hpp
	${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/ShareablePointsList.hpp
)

set(PLUG_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/ShareablePosition.cpp
	${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/ShareableFrame.cpp
	${CMAKE_CURRENT_LIST_DIR}/ShareablePoints/ShareablePointsList.cpp
)

# Define IDE folders:
file(GLOB PLUGINS_SHAREPOINTS	ShareablePoints/*)
source_group("Plugins\\ShareablePoints"	FILES ${PLUGINS_SHAREPOINTS})

#Create a static library from the object files
add_library(Plugins STATIC ${PLUG_HEADERS} ${PLUG_SOURCES})
