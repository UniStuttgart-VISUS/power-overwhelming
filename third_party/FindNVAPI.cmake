# FindNVAPI.cmake
# Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
# Licensed under the MIT licence. See LICENCE file for details.

include(FindPackageHandleStandardArgs)


# VISUS' build environment is more special than yours ...
file(GLOB NdaDirs "S:/Software/Nvidia/NVAPI/*-NDA-Developer")

# Determine where the platform-dependent library location is.
if (WIN32)
    set(NvapiDirs "${CMAKE_CURRENT_SOURCE_DIR}/nvapi" "${NdaDirs}")

    if ("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
        set(NvapiLib "nvapi.lib")
    else ()
        set(NvapiLib "nvapi64.lib")
    endif ()

else ()
    set(NvapiDirs "/usr")
    set(NvapiLib "")
endif ()

message(STATUS "Searching NVAPI library ${NvapiLib} in ${NvapiDirs} ...")

# Find location of public headers
find_path(NVAPI_INCLUDE_DIR
    NAMES nvapi.h
    PATHS ${NvapiDirs}
    PATH_SUFFIXES "R550-NDA-Developer"
)
mark_as_advanced(NVAPI_INCLUDE_DIR)

# Find the library
find_library(NVAPI_LIBRARY
    NAMES ${NvapiLib}
    PATHS ${NvapiDirs}
    PATH_SUFFIXES "amd64" "x86" "R550-NDA-Developer/amx64" "R550-NDA-Developer/x86"
)
mark_as_advanced(NVAPI_LIBRARY)

find_package_handle_standard_args(NVAPI REQUIRED_VARS NVAPI_INCLUDE_DIR NVAPI_LIBRARY)
