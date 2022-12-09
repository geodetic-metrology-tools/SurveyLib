# SPDX-License-Identifier: Zlib
# SPDX-FileCopyrightText: 2022 CERN (home.cern)
# SPDX-FileContributor: Author: Sylvain Fargier <sylvain.fargier@cern.ch>

find_package(Git REQUIRED)
if(GIT_FOUND)
    set(GIT_EXE ${GIT_EXECUTABLE})
endif(GIT_FOUND)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/SUSoftCMakeCommon/.git")
    message("Initializing cmake submodule")
    execute_process(COMMAND ${GIT_EXE} "submodule" "update" "--init" "--recursive" "cmake"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
endif()


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/SUSoftCMakeCommon;${CMAKE_CURRENT_SOURCE_DIR}/SUSoftCMakeCommon/cmake")

include(PostInit)

include(${CMAKE_CURRENT_SOURCE_DIR}/SUSoftCMakeCommon/CMakeLists.txt)

