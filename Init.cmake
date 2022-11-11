# SPDX-License-Identifier: Zlib
# SPDX-FileCopyrightText: 2022 CERN (home.cern)
# SPDX-FileContributor: Author: Sylvain Fargier <sylvain.fargier@cern.ch>

find_package(Git REQUIRED)
if(GIT_FOUND)
    set(GIT_EXE ${GIT_EXECUTABLE})
endif(GIT_FOUND)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/deps/SUSoftCMakeCommon/.git")
    message("Initializing SUSoftCMakeCommon submodule")
    execute_process(COMMAND ${GIT_EXE} "submodule" "update" "--init" "--recursive" "deps/SUSoftCMakeCommon"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

include("${CMAKE_CURRENT_SOURCE_DIR}/deps/SUSoftCMakeCommon/CMakeLists.txt")

include(PostInit)
