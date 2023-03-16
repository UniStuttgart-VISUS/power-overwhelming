# CMakeLists.txt
# Copyright © 2022 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.

cmake_minimum_required(VERSION 3.15...3.26)

project(power_overwhelming)

include(CMakeDependentOption)
include(GNUInstallDirs)

# User-configurable options.
option(PWROWG_BuildDemo "Build demo programme" OFF)

option(PWROWG_BuildDumpSensors "Build dump_sensors utility" ON)

cmake_dependent_option(PWROWG_BuildStablePower "Build setstablepowerstate tool" OFF WIN32 OFF)

cmake_dependent_option(PWROWG_BuildTests "Build unit tests." ON WIN32 OFF)

cmake_dependent_option(PWROWG_BuildWeb "Build browser for benchmarking web-based visualisations" OFF WIN32 OFF)

# Dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party)

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

# dump_sensors utility
if (PWROWG_BuildDumpSensors)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dump_sensors)
endif ()

# Browser
if (PWROWG_BuildWeb)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/poweb)
endif ()

# Stable power tool
if (PWROWG_BuildStablePower)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/setstablepowerstate)
endif ()
