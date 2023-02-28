# CMakeLists.txt
# Copyright © 2022 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.

cmake_minimum_required(VERSION 3.15.0)


project(power-overwhelming)

# User-configurable options.
option(BuildDemo "Build demo programme" OFF)

if (WIN32)
    option(BuildStablePower "Build setstablepowerstate tool" OFF)
else (WIN32)
    set(BuildStablePower FALSE)
endif (WIN32)

if (WIN32)
    option(BuildTests "Build unit tests." ON)
else (WIN32)
    set(BuildTests FALSE)
endif (WIN32)

if (WIN32)
    option(BuildWeb "Build browser for benchmarking web-based visualisations" OFF)
else (WIN32)
    set(BuildWeb FALSE)
endif (WIN32)


# Dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party)

# The library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/power_overwhelming)

# Unit tests
if (BuildTests)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif (BuildTests)

# Demo programme
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/podump)

# Browser
if (BuildWeb)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/poweb)
endif (BuildWeb)

# Stable power tool
if (BuildStablePower)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/setstablepowerstate)
endif (BuildStablePower)
