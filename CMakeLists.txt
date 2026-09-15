# CMakeLists.txt
# Copyright © 2022 - 2026 Visualisierungsinstitut der Universität Stuttgart.
# Licensed under the MIT licence. See LICENCE file for details.

cmake_minimum_required(VERSION 3.24...3.31)

project(power_overwhelming)

include(CMakeDependentOption)
include(GNUInstallDirs)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
#set(MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# User-configurable options.
option(PWROWG_BuildDemo "Build demo programme" OFF)
cmake_dependent_option(PWROWG_BuildDriver "Build RAPL MSR driver" OFF WIN32 OFF)
option(PWROWG_BuildDumpReadings "Build dump_readings utility" OFF)
option(PWROWG_BuildDumpSensors "Build dump_sensors utility" ON)
option(PWROWG_BuildLptTest "Build parallel port test tool" OFF)
option(PWROWG_BuildPwogTools "Build tools for the PWOG file format" OFF)
option(PWROWG_BuildRtxConfig "Build R&S RTA/RTB configuration utility" OFF)
cmake_dependent_option(PWROWG_BuildStablePower "Build setstablepowerstate tool" OFF WIN32 OFF)
cmake_dependent_option(PWROWG_BuildTests "Build unit tests." ON WIN32 OFF)
cmake_dependent_option(PWROWG_BuildWeb "Build browser for benchmarking web-based visualisations" OFF WIN32 OFF)
option(PWROWG_NoPackageRestore "Disable automatic restore of Nuget packages as pre-build step" OFF)
mark_as_advanced(PWROWG_NoPackageRestore)
set(PWROWG_CustomTinkerforgeFirmwareMajor "" CACHE STRING "The major firmware version that identifies our custom changes")
set(PWROWG_CustomTinkerforgeFirmwareMinor "" CACHE STRING "The minor firmware version that identifies our custom changes")
set(PWROWG_CustomTinkerforgeFirmwareRev "" CACHE STRING "The firmware revision that identifies our custom changes")
option(PWROWG_CustomTinkerforgeFirmwareMandatory "Raises an exception if a custom firmware was specified, but not found on all bricklets" OFF)
option(PWROWG_WithAdl "Build support for the AMD Display Library" ON)
# TODO: Enable this for Linux too, once libbenchlab is fully functional.
#option(PWROWG_WithBenchlab "Build support for the Benchlab telemetry system" ON)
cmake_dependent_option(PWROWG_WithBenchlab "Build support for the Benchlab telemetry system" ON WIN32 OFF)
cmake_dependent_option(PWROWG_WithIgcl "Build support for IGCL" ON WIN32 OFF)
option(PWROWG_WithNiDaqMx "Build support for NI-DAQmx" OFF)
cmake_dependent_option(PWROWG_WithNvapi "Build support for NVIDIA API" OFF WIN32 OFF)
option(PWROWG_WithNvml "Build support for the NVIDIA Management Library" ON)
option(PWROWG_WithParquet "Build support for Apache Parquet sinks" OFF)
option(PWROWG_WithPowenetics "Build support for Powenetics" ON)
option(PWROWG_WithStaticParquet "Build support for Apache Parquet sinks by embedding Arrow in Power Overwhelming" OFF)
option(PWROWG_WithThreadStats "Enable collector thread statistics" OFF)
option(PWROWG_WithTimeSynchronisation "Build support for Cristian's algorithm" OFF)
option(PWROWG_WithVisa "Build support for the VISA-based instruments" ${VISA_FOUND})

# Derived options.
if (PWROWG_WithStaticParquet)
    set(PWROWG_WithParquet ON)
    # TODO: I have no idea how to fudge this ...
    #set(PWROWG_UseStaticParquet ON)
endif ()


# Dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party)

# NVAPI Wrapper
if (PWROWG_WithNvapi)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pwrovrnvapi)
endif ()

# The library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/power_overwhelming)

# Unit tests
if (PWROWG_BuildTests)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif ()

# Demo programme
if (PWROWG_BuildDemo)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/podump)
endif ()

# RAPL MSR driver
if (PWROWG_BuildDriver)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pwrowgrapldrv)
endif ()

# dump_readings utility
if (PWROWG_BuildDumpReadings)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dump_readings)
endif ()

# dump_sensors utility
if (PWROWG_BuildDumpSensors)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dump_sensors)
endif ()

# Parallel port test tool
if (PWROWG_BuildLptTest)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lpt_test)
endif ()

# PWOG file tools
if (PWROWG_BuildPwogTools)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pwoginfo)

    if (PWROWG_WithStaticParquet)
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pwog2parquet)
    endif ()
endif ()

# Oscilloscope configuration utility
if (PWROWG_BuildRtxConfig)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/rtx_config)
endif ()

# Browser
if (PWROWG_BuildWeb)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/poweb)
endif ()

# Stable power tool
if (PWROWG_BuildStablePower)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/setstablepowerstate)
endif ()
