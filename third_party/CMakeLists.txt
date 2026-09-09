# CMakeLists.txt
# Copyright © 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart.
# Licensed under the MIT licence. See LICENCE file for details.

include(ExternalProject)
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
    DOWNLOAD_EXTRACT_TIMESTAMP ON
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


# Apache Arrow (for Parquet output). This is a giant hack as we need a version
# that still works with C++17. Technically, this would be 22, but this is not
# available on vcpkg, so we get 21 here.
if (PWROWG_WithParquet)
    set(_arrow_root ${CMAKE_CURRENT_SOURCE_DIR}/arrow-21.0.0)
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(_triplet x64)
    else ()
        set(_triplet x86)
    endif()
    if (WIN32)
        set(_triplet "${_triplet}-windows-static-md")
    else ()
        set(_triplet "${_triplet}-linux")
    endif()

    ExternalProject_Add(arrow
        GIT_REPOSITORY "https://github.com/microsoft/vcpkg.git"
        BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/arrow-build"
        LOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/arrow-log"
        SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/arrow-src"
        STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/arrow-stamp"
        TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/arrow-tmp"
        CONFIGURE_COMMAND "<SOURCE_DIR>/bootstrap-vcpkg$<IF:${WIN32},.bat,.sh>" -disableMetrics
        COMMAND "<SOURCE_DIR>/$<IF:${WIN32},vcpkg.exe,vcpkg>" install
            --vcpkg-root "${CMAKE_CURRENT_BINARY_DIR}/arrow-src"
            --x-manifest-root ${_arrow_root}
            --triplet ${_triplet}
            --clean-after-build
        BUILD_COMMAND ""
        INSTALL_COMMAND "")
    set(CMAKE_PREFIX_PATH "${_arrow_root}/vcpkg_installed/${_triplet}" ${CMAKE_PREFIX_PATH} PARENT_SCOPE)
    #set(ARROW_VCPKG TRUE PARENT_SCOPE)
    #set(VCPKG_TARGET_TRIPLET ${_triplet})
    #include("${CMAKE_CURRENT_BINARY_DIR}/arrow-src/scripts/buildsystems/vcpkg.cmake")
    mark_as_advanced(FORCE
        _VCPKG_INSTALLED_DIR
        X_VCPKG_APPLOCAL_DEPS_INSTALL
        X_VCPKG_APPLOCAL_DEPS_SERIALIZED)

    unset(_arrow_root)
    unset(_triplet)
endif ()


# Intel Graphics Control Library (this is even more hacky, because Intel has no 
# releases on GitHub atm.)
FetchContent_Declare(igcl
    URL "https://github.com/intel/drivers.gpu.control-library/archive/refs/heads/master.zip"
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)
FetchContent_MakeAvailable(igcl)
add_library(igcl INTERFACE IMPORTED GLOBAL)
set_target_properties(igcl PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${igcl_SOURCE_DIR}/include")
mark_as_advanced(FORCE
    FETCHCONTENT_SOURCE_DIR_IGCL
    FETCHCONTENT_UPDATES_DISCONNECTED_IGCL)


# Benchlab
if (PWROWG_WithBenchlab)
    FetchContent_Declare(libbenchlab
        URL "https://github.com/UniStuttgart-VISUS/libbenchlab/archive/refs/tags/v0.7.zip"
        DOWNLOAD_EXTRACT_TIMESTAMP ON
    )
    option(BENCHLAB_BuildTests "" OFF)
    option(BENCHLAB_BuildCclient "" OFF)
    option(BENCHLAB_BuildCppClient "" OFF)
    option(BENCHLAB_BuildExcellentBenchlab "" OFF)
    FetchContent_MakeAvailable(libbenchlab)
    mark_as_advanced(FORCE
        libbenchlab_SOURCE_DIR
        BENCHLAB_BuildTests
        BENCHLAB_BuildCclient
        BENCHLAB_BuildCppClient
        BENCHLAB_BuildExcellentBenchlab
        FETCHCONTENT_SOURCE_DIR_LIBBENCHLAB
        FETCHCONTENT_UPDATES_DISCONNECTED_LIBBENCHLAB)
endif ()


# Powenetics (the "Greek device")
if (PWROWG_WithPowenetics)
    FetchContent_Declare(libpowenetics
        URL "https://github.com/UniStuttgart-VISUS/libpowenetics/archive/refs/tags/v1.4.zip"
        DOWNLOAD_EXTRACT_TIMESTAMP ON
    )
    option(POWENETICS_BuildTests "" OFF)
    option(POWENETICS_BuildCclient "" OFF)
    option(POWENETICS_BuildExcellentPowenetics "" OFF)
    FetchContent_MakeAvailable(libpowenetics)
    mark_as_advanced(FORCE
        libpowenetics_SOURCE_DIR
        POWENETICS_BuildTests
        POWENETICS_BuildCclient
        POWENETICS_BuildExcellentPowenetics
        FETCHCONTENT_SOURCE_DIR_LIBPOWENETICS
        FETCHCONTENT_UPDATES_DISCONNECTED_LIBPOWENETICS)
endif ()


# JSON library
FetchContent_Declare(nlohmann_json
    URL "https://github.com/nlohmann/json/archive/refs/tags/v3.12.0.zip"
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)
FetchContent_MakeAvailable(nlohmann_json)
mark_as_advanced(FORCE
    FETCHCONTENT_SOURCE_DIR_NLOHMANN_JSON
    FETCHCONTENT_UPDATES_DISCONNECTED_NLOHMANN_JSON
    JSON_BuildTests
    JSON_CI
    JSON_Diagnostics
    JSON_DisableEnumSerialization
    JSON_Diagnostic_Positions
    JSON_GlobalUDLs
    JSON_ImplicitConversions
    JSON_Install
    JSON_LegacyDiscardedValueComparison
    JSON_MultipleHeaders
    JSON_SystemInclude)


# NI-DAQmx (headers only)
if (PWROWG_WithNiDaqMx)
    find_package(NIDAQMX REQUIRED)
    add_library(nidaqmx INTERFACE)
    set_target_properties(nidaqmx PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${NIDAQMX_INCLUDE_DIR}")
    install(TARGETS nidaqmx EXPORT nidaqmxTargets)
    install(EXPORT nidaqmxTargets
        FILE nidaqmxConfig.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/nidaqmx)
endif ()


# NVIDIA Management Library
add_library(nvml INTERFACE IMPORTED GLOBAL)
set_target_properties(nvml PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/gdk_wddm_amd64_release/nvml/include")


## oneAPI Level Zero
#FetchContent_Declare(oneapi
#    URL "https://github.com/oneapi-src/level-zero/archive/refs/tags/v1.28.6.zip"
#    DOWNLOAD_EXTRACT_TIMESTAMP ON
#)
#option(BUILD_L0_LOADER_TESTS "" OFF)
#option(BUILD_INSTALLER "" OFF)
#FetchContent_MakeAvailable(oneapi)
#add_library(oneapi INTERFACE IMPORTED GLOBAL)
#set_target_properties(oneapi PROPERTIES
#    INTERFACE_INCLUDE_DIRECTORIES "${oneapi_SOURCE_DIR}/include")
#mark_as_advanced(FORCE
#    FETCHCONTENT_SOURCE_DIR_ONEAPI
#    FETCHCONTENT_UPDATES_DISCONNECTED_ONEAPI)


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


# Passmark USB PD tester
add_library(usbpdtesterdriver INTERFACE IMPORTED GLOBAL)
if (WIN32)
set_target_properties(usbpdtesterdriver PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/usbpdtesterdriver_2.12.28")
else ()
set_target_properties(usbpdtesterdriver PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/libftd2xx-linux-x86_64-1.4.33")
endif ()


# VISA (headers only)
if (PWROWG_WithVisa)
    find_package(VISA REQUIRED)
    add_library(visa INTERFACE)
    set_target_properties(visa PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${VISA_INCLUDE_DIR}")
    install(TARGETS visa EXPORT visaTargets)
    install(EXPORT visaTargets
        FILE visaConfig.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/visa)
endif ()


# Windows Implementation Library
if (WIN32)
    FetchContent_Declare(wil
        URL "https://github.com/microsoft/wil/archive/refs/tags/v1.0.260126.7.zip"
        DOWNLOAD_EXTRACT_TIMESTAMP ON
    )
    option(FAST_BUILD "" OFF)
    option(WIL_BUILD_PACKAGING "" OFF)
    option(WIL_BUILD_TESTS "" OFF)
    FetchContent_MakeAvailable(wil)
    mark_as_advanced(FORCE
        FETCHCONTENT_SOURCE_DIR_WIL
        FETCHCONTENT_UPDATES_DISCONNECTED_WIL
        FAST_BUILD
        WIL_BUILD_PACKAGING
        WIL_BUILD_TESTS
        WIL_ENABLE_ASAN
        WIL_ENABLE_UBSAN)
endif()


# rapidcsv
FetchContent_Declare(rapidcsv
    URL "https://codeload.github.com/d99kris/rapidcsv/zip/refs/tags/v8.84"
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)
FetchContent_MakeAvailable(rapidcsv)
mark_as_advanced(FORCE
    RAPIDCSV_BUILD_TESTS
    FETCHCONTENT_SOURCE_DIR_RAPIDCSV
    FETCHCONTENT_UPDATES_DISCONNECTED_RAPIDCSV)
