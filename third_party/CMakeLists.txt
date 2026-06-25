# CMakeLists.txt
# Copyright © 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart.
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


# Apache Arrow (for Parquet) output.
if (PWROWG_WithParquet)
    FetchContent_Declare(arrow
        URL "https://github.com/apache/arrow/archive/refs/tags/apache-arrow-24.0.0.zip"
        DOWNLOAD_EXTRACT_TIMESTAMP ON
    )
    option(ARROW_COMPUTE "" OFF)
    option(ARROW_CSV "" OFF)
    option(ARROW_CUDA "" OFF)
    option(ARROW_FLIGHT "" OFF)
    option(ARROW_GANDIVA "" OFF)
    option(ARROW_GANDIVA_JAVA "" OFF)
    option(ARROW_GCS "" OFF)
    option(ARROW_HDFS "" OFF)
    option(ARROW_JEMALLOC "" OFF)
    option(ARROW_JSON "" OFF)
    option(ARROW_MIMALLOC "" OFF)
    option(ARROW_ORC= "" OFF)
    option(ARROW_PARQUET "" ON)
    option(PARQUET_REQUIRE_ENCRYPTION "" OFF)
    option(ARROW_PYTHON "" OFF)
    option(ARROW_S3 "" OFF)
    option(ARROW_SUBSTRAIT "" OFF)
    option(ARROW_WITH_RE2 "" OFF)
    option(ARROW_TENSORFLOW "" OFF)
    option(ARROW_BUILD_BENCHMARKS "" OFF)
    option(ARROW_BUILD_EXAMPLES "" OFF)
    option(ARROW_BUILD_INTEGRATION "" OFF)
    option(ARROW_BUILD_UTILITIES "" OFF)
    option(ARROW_BUILD_TESTS "" OFF)
    option(ARROW_ENABLE_TIMING_TESTS "" OFF)
    option(ARROW_FUZZING "" OFF)
    set(ARROW_DEPENDENCY_SOURCE "BUNDLED")
    FetchContent_MakeAvailable(arrow)
    add_subdirectory(${arrow_SOURCE_DIR}/cpp ${arrow_BINARY_DIR} EXCLUDE_FROM_ALL)
    mark_as_advanced(FORCE
        FETCHCONTENT_SOURCE_DIR_ARROW
        FETCHCONTENT_UPDATES_DISCONNECTED_ARROW)
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
        URL "https://github.com/UniStuttgart-VISUS/libbenchlab/archive/refs/tags/v0.5.zip"
        DOWNLOAD_EXTRACT_TIMESTAMP ON
    )
    option(BENCHLAB_BuildTests "" OFF)
    option(BENCHLAB_BuildCclient "" OFF)
    option(BENCHLAB_BuildCppClient "" OFF)
    option(BENCHLAB_BuildExcellentBenchlab "" OFF)
    FetchContent_GetProperties(libbenchlab)
    if (NOT libbenchlab_POPULATED)
        FetchContent_Populate(libbenchlab)
        add_subdirectory(${libbenchlab_SOURCE_DIR} ${libbenchlab_BINARY_DIR} EXCLUDE_FROM_ALL)
    endif ()
    mark_as_advanced(FORCE
        libbenchlab_SOURCE_DIR
        BENCHLAB_BuildTests
        BENCHLAB_BuildCclient
        BENCHLAB_BuildExcellentBenchlab)
endif ()


# Powenetics (the "Greek device")
if (PWROWG_WithPowenetics)
    FetchContent_Declare(libpowenetics
        URL "https://github.com/UniStuttgart-VISUS/libpowenetics/archive/refs/tags/v1.3.zip"
        DOWNLOAD_EXTRACT_TIMESTAMP ON
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
    add_library(visa INTERFACE IMPORTED GLOBAL)
    set_target_properties(visa PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${VISA_INCLUDE_DIR}")
endif ()


# Windows Implementation Library
if (WIN32)
    FetchContent_Declare(wil
        URL "https://github.com/microsoft/wil/archive/refs/tags/v1.0.250325.1.zip"
        DOWNLOAD_EXTRACT_TIMESTAMP ON
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
endif()


# rapidcsv
FetchContent_Declare(rapidcsv
    URL "https://codeload.github.com/d99kris/rapidcsv/zip/refs/tags/v8.84"
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)
FetchContent_MakeAvailable(rapidcsv)
mark_as_advanced(FORCE
    RAPIDCSV_BUILD_TESTS)
