#############################################################
#
# VCPKG setup for SurveyLib and the projects that embed it (LGC, CSGeo ...)
#
# MUST be included BEFORE project() in the top-level CMakeLists.txt:
#   include("<path to SurveyLib>/source/SurveyLibVcpkg.cmake")
#
# Dependencies are listed in vcpkg.json next to this file (manifest mode).

# vcpkg toolchain, unless the user passed one with -DCMAKE_TOOLCHAIN_FILE=...
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{VCPKG_ROOT})
	set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "")
endif()

# Use SurveyLib's manifest even when another project is top-level
if(NOT DEFINED VCPKG_MANIFEST_DIR)
	set(VCPKG_MANIFEST_DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE PATH "")
endif()

# Static libraries with the dynamic MSVC runtime (/MD), so no GDAL DLLs have to be shipped
# and the CRT stays compatible with projects that link SurveyLib's static libraries.
if(CMAKE_HOST_WIN32 AND NOT DEFINED VCPKG_TARGET_TRIPLET)
	if(CMAKE_GENERATOR_PLATFORM STREQUAL "Win32")
		set(VCPKG_TARGET_TRIPLET "x86-windows-static-md" CACHE STRING "")
	else()
		set(VCPKG_TARGET_TRIPLET "x64-windows-static-md" CACHE STRING "")
	endif()
endif()