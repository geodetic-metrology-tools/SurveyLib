# Setting the include path - to include a given directory
include_directories (
	.
	${SURVEYLIB_INCLUDE_PATH}
	${NAGC_INCLUDE_PATH}
)




##### This will correspond to one VS project!

# Create a variable containing all .cpp files:
set(ShortestPath_SOURCES 
	TGraph.cpp
	TRefFrameWrapper.cpp
	TRefSystemFactory.cpp
	TTransformWrapper.cpp
)

# Create a variable containing all .h files:
set(ShortestPath_HEADERS 
	${SURVEYLIB_INCLUDE_PATH}/DynamicPriorityQueue.h
	${SURVEYLIB_INCLUDE_PATH}/PtrGreater.h
	${SURVEYLIB_INCLUDE_PATH}/TGraph.h
	${SURVEYLIB_INCLUDE_PATH}/TRefFrameWrapper.h
	${SURVEYLIB_INCLUDE_PATH}/TRefSystemFactory.h
	${SURVEYLIB_INCLUDE_PATH}/TTransformWrapper.h
)

# Create a static library from sources:
add_library(ShortestPath STATIC ${ShortestPath_SOURCES} ${ShortestPath_HEADERS})
install(FILES ${ShortestPath_HEADERS} DESTINATION ${INSTALL_PREFIX}/include)
#####