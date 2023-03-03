# CMakeLists.txt
# Copyright © 2022 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.

cmake_minimum_required(VERSION 3.15.0)


project(power-overwhelming)

# User-configurable options.
option(PWROWG_BuildDemo "Build demo programme" OFF)

if (WIN32)
    option(PWROWG_BuildStablePower "Build setstablepowerstate tool" OFF)
else (WIN32)
    set(PWROWG_BuildStablePower FALSE)
endif (WIN32)

if (WIN32)
    option(PWROWG_BuildTests "Build unit tests." ON)
else (WIN32)
    set(PWROWG_BuildTests FALSE)
endif (WIN32)

if (WIN32)
    option(PWROWG_BuildWeb "Build browser for benchmarking web-based visualisations" OFF)
else (WIN32)
    set(PWROWG_BuildWeb FALSE)
endif (WIN32)


# Dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party)

# The library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/power_overwhelming)

# Unit tests
if (PWROWG_BuildTests)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif (PWROWG_BuildTests)

# Demo programme
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/podump)

# Browser
if (PWROWG_BuildWeb)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/poweb)
endif (PWROWG_BuildWeb)

# Stable power tool
if (PWROWG_BuildStablePower)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/setstablepowerstate)
endif (PWROWG_BuildStablePower)
