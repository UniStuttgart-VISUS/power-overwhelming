﻿# CMakeLists.txt
# Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
# Licensed under the MIT licence. See LICENCE file for details.

include(FetchContent)

set(FETCHCONTENT_QUIET ON)
mark_as_advanced(FORCE
    FETCHCONTENT_BASE_DIR
    FETCHCONTENT_FULLY_DISCONNECTED
    FETCHCONTENT_QUIET
    FETCHCONTENT_UPDATES_DISCONNECTED)

# AMD Display Library (this is a bit hacky ...)
FetchContent_Declare(adl
    URL "https://github.com/GPUOpen-LibrariesAndSDKs/display-library/archive/17.1.tar.gz"
)
FetchContent_MakeAvailable(adl)
add_library(adl INTERFACE IMPORTED GLOBAL)
set_target_properties(adl PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${adl_SOURCE_DIR}/include")
if (NOT WIN32)
    set_target_properties(adl PROPERTIES INTERFACE_COMPILE_DEFINITIONS "LINUX")
endif ()

mark_as_advanced(FORCE
    FETCHCONTENT_SOURCE_DIR_ADL
    FETCHCONTENT_UPDATES_DISCONNECTED_ADL)

# JSON library
FetchContent_Declare(nlohmann_json
    URL "https://github.com/nlohmann/json/archive/v3.11.3.tar.gz"
)
FetchContent_MakeAvailable(nlohmann_json)
mark_as_advanced(FORCE
    FETCHCONTENT_SOURCE_DIR_NLOHMANN_JSON
    FETCHCONTENT_UPDATES_DISCONNECTED_NLOHMANN_JSON
    JSON_BuildTests
    JSON_CI
    JSON_Diagnostics
    JSON_DisableEnumSerialization
    JSON_GlobalUDLs
    JSON_ImplicitConversions
    JSON_Install
    JSON_LegacyDiscardedValueComparison
    JSON_MultipleHeaders
    JSON_SystemInclude)

# NVIDIA Management Library
add_library(nvml INTERFACE IMPORTED GLOBAL)
set_target_properties(nvml PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/gdk_wddm_amd64_release/nvml/include")

# Rohde & Schwarz HMC 8015
set(RsHmc8015Dir ${CMAKE_CURRENT_SOURCE_DIR}/rshmc8015-cvi-1.0.3)
set(RsHmc8015Include ${RsHmc8015Dir} PARENT_SCOPE)

# Rohde & Schwarz RTB family
set(RsRtxDir ${CMAKE_CURRENT_SOURCE_DIR}/rsrtx-cvi-1.4.0)
set(RsRtxInclude ${RsRtxDir} PARENT_SCOPE)

# Tinkerforge API
set(TinkerforgeDir ${CMAKE_CURRENT_SOURCE_DIR}/tinkerforge_c_bindings_2_1_33/source)
file(GLOB_RECURSE TinkerforgeHeaderFiles "${TinkerforgeDir}/*.h" "${TinkerforgeDir}/*.inl")
file(GLOB_RECURSE TinkerforgeSourceFiles "${TinkerforgeDir}/*.c")
add_library(tinkerforge STATIC ${TinkerforgeHeaderFiles} ${TinkerforgeSourceFiles})
target_include_directories(tinkerforge PUBLIC
    PUBLIC $<BUILD_INTERFACE:${TinkerforgeDir}>)

if (NOT WIN32)
    set_property(TARGET tinkerforge PROPERTY POSITION_INDEPENDENT_CODE ON)
endif ()

# Windows Implementation Library
FetchContent_Declare(wil
    URL "https://github.com/microsoft/wil/archive/refs/tags/v1.0.250325.1.zip"
)
option(FAST_BUILD "" OFF)
option(WIL_BUILD_PACKAGING "" OFF)
option(WIL_BUILD_TESTS "" OFF)
FetchContent_GetProperties(wil)
if (NOT wil_POPULATED)
    FetchContent_Populate(wil)
    add_subdirectory(${wil_SOURCE_DIR} ${wil_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()
mark_as_advanced(FORCE
    FETCHCONTENT_SOURCE_DIR_WIL
    FETCHCONTENT_UPDATES_DISCONNECTED_WIL
    FAST_BUILD
    WIL_BUILD_PACKAGING
    WIL_BUILD_TESTS)

# Powenetics (the "Greek device")
FetchContent_Declare(libpowenetics
    URL "https://github.com/UniStuttgart-VISUS/libpowenetics/archive/refs/tags/v1.1.zip"
)
option(POWENETICS_BuildTests "" OFF)
option(POWENETICS_BuildCclient "" OFF)
option(POWENETICS_BuildExcellentPowenetics "" OFF)
FetchContent_GetProperties(libpowenetics)
if (NOT libpowenetics_POPULATED)
    FetchContent_Populate(libpowenetics)
    add_subdirectory(${libpowenetics_SOURCE_DIR} ${libpowenetics_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()
mark_as_advanced(FORCE
    libpowenetics_SOURCE_DIR
    POWENETICS_BuildTests
    POWENETICS_BuildCclient
    POWENETICS_BuildExcellentPowenetics)

# Benchlab
FetchContent_Declare(libbenchlab
    URL "https://github.com/UniStuttgart-VISUS/libbenchlab/archive/refs/tags/v0.2.zip"
)
option(BENCHLAB_BuildTests "" OFF)
option(BENCHLAB_BuildCclient "" OFF)
option(BENCHLAB_BuildCppClient "" OFF)
option(BENCHLAB_BuildExcellentPowenetics "" OFF)
FetchContent_GetProperties(libbenchlab)
if (NOT libbenchlab_POPULATED)
    FetchContent_Populate(libbenchlab)
    add_subdirectory(${libbenchlab_SOURCE_DIR} ${libbenchlab_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()
mark_as_advanced(FORCE
    libbenchlab_SOURCE_DIR
    BENCHLAB_BuildTests
    BENCHLAB_BuildCclient
    BENCHLAB_BuildExcellentPowenetics)

# Passmark USB PD tester
add_library(usbpdtesterdriver INTERFACE IMPORTED GLOBAL)
if (WIN32)
set_target_properties(usbpdtesterdriver PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/usbpdtesterdriver_2.12.28")
else ()
set_target_properties(usbpdtesterdriver PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/libftd2xx-linux-x86_64-1.4.33")
endif ()

# rapidcsv
FetchContent_Declare(rapidcsv
    URL "https://codeload.github.com/d99kris/rapidcsv/zip/refs/tags/v8.84"
)
FetchContent_MakeAvailable(rapidcsv)
mark_as_advanced(FORCE
    RAPIDCSV_BUILD_TESTS)
