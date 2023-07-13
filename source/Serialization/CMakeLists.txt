cmake_minimum_required(VERSION 3.10)

#############################################################
#
# PROJECT NAME
#

project(Serialization)

#############################################################
#
# App specific includes

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/source/tests)

############################
# Final target

add_library(${PROJECT_NAME} STATIC 
	source/Serializer.hpp 
	source/Serializer_json.hpp 
	source/Serializer_json.cpp 
	source/CustomTypeTraits.hpp
)

#add_dependencies(${PROJECT_NAME}
#)
#target_link_libraries(${PROJECT_NAME}
	#rapidjson TODO
#)
add_definitions(-DRAPIDJSON_HAS_STDSTRING) # TODO

target_include_directories(${PROJECT_NAME} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/source
	# TODO - REMOVE AFTER CMAKE UPDATE
	${RAPIDJSON_INCLUDE_DIR}
)

# needed for linux compilation
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

set_target_properties(${PROJECT_NAME} ${PROJECT_NAME}_Test PROPERTIES FOLDER "SurveyLib/Serializer")
