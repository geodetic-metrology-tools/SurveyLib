 get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
 include(${SELF_DIR}/SpatialObjects-targets.cmake)
 get_filename_component(myproj_INCLUDE_DIRS "${SELF_DIR}/include" ABSOLUTE)