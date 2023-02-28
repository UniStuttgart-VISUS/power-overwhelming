# CMakeLists.txt
# Copyright © 2022 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.

cmake_minimum_required(VERSION 3.15.0)


project(power-overwhelming)

# User-configurable options.
option(PWROVRWHLMG_BuildDemo "Build demo programme" OFF)

if (WIN32)
    option(PWROVRWHLMG_BuildStablePower "Build setstablepowerstate tool" OFF)
else (WIN32)
    set(PWROVRWHLMG_BuildStablePower FALSE)
endif (WIN32)

if (WIN32)
    option(PWROVRWHLMG_BuildTests "Build unit tests." ON)
else (WIN32)
    set(PWROVRWHLMG_BuildTests FALSE)
endif (WIN32)

if (WIN32)
    option(PWROVRWHLMG_BuildWeb "Build browser for benchmarking web-based visualisations" OFF)
else (WIN32)
    set(PWROVRWHLMG_BuildWeb FALSE)
endif (WIN32)


# Dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party)

# The library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/power_overwhelming)

# Unit tests
if (PWROVRWHLMG_BuildTests)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif (PWROVRWHLMG_BuildTests)

# Demo programme
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/podump)

# Browser
if (PWROVRWHLMG_BuildWeb)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/poweb)
endif (PWROVRWHLMG_BuildWeb)

# Stable power tool
if (PWROVRWHLMG_BuildStablePower)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/setstablepowerstate)
endif (PWROVRWHLMG_BuildStablePower)
