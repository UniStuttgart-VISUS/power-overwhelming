# CMakeLists.txt
# Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.

cmake_minimum_required(VERSION 3.15.0)


project(power_overwhelming)

# User-configurable options
if (WIN32)
    option(PWROVRWHLMG_ForceDirect3D11 "Force GPU enumeration via Direct3D 11" OFF)
    mark_as_advanced(PWROVRWHLMG_ForceDirect3D11)
else (WIN32)
    set(PWROVRWHLMG_ForceDirect3D11 OFF)
endif (WIN32)

option(PWROVRWHLMG_WithAdl "Build support for the AMD Display Library" ON)

option(PWROVRWHLMG_WithNvml "Build support for the NVIDIA Management Library" ON)

option(PWROVRWHLMG_WithTimeSynchronisation "Build support for Cristian's algorithm" OFF)

option(PWROVRWHLMG_WithVisa "Build support for the VISA-based instruments" ON)

if (PWROVRWHLMG_WithVisa)
    find_package(VISA)
endif (PWROVRWHLMG_WithVisa)

# Collect source files.
set(IncludeDir "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SourceDir "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE PublicHeaderFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${IncludeDir}/*.h" "${IncludeDir}/*.inl")
file(GLOB_RECURSE PrivateHeaderFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${SourceDir}/*.h" "${SourceDir}/*.inl")
file(GLOB_RECURSE SourceFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${SourceDir}/*.cpp")

#source_group(TREE ${IncludeDir} FILES ${PublicHeaderFiles})
#source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PrivateHeaderFiles})
#source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SourceFiles})

message(STATUS "Including Tinkerforge API from ${TinkerforgeDir} ...")
file(GLOB_RECURSE TinkerforgeHeaderFiles "${TinkerforgeDir}/*.h" "${TinkerforgeDir}/*.inl")
file(GLOB_RECURSE TinkerforgeSourceFiles "${TinkerforgeDir}/*.c")

#source_group(tinkerforge ${TinkerforgeDir} FILES ${TinkerforgeHeaderFiles})
#source_group(tinkerforge ${TinkerforgeDir} FILES ${TinkerforgeSourceFiles})

# Define the output.
add_library(${PROJECT_NAME} SHARED ${PublicHeaderFiles} ${PrivateHeaderFiles} ${SourceFiles} ${TinkerforgeHeaderFiles} ${TinkerforgeSourceFiles})

# Configure the compiler.
add_definitions("-DPOWER_OVERWHELMING_EXPORTS")

if (PWROVRWHLMG_WithAdl)
    add_definitions("-DPOWER_OVERWHELMING_WITH_ADL")
endif (PWROVRWHLMG_WithAdl)

if (PWROVRWHLMG_WithNvml)
    add_definitions("-DPOWER_OVERWHELMING_WITH_NVML")
endif (PWROVRWHLMG_WithNvml)

if (PWROVRWHLMG_WithTimeSynchronisation)
    add_definitions("-DPOWER_OVERWHELMING_WITH_TIME_SYNCHRONISER")
endif (PWROVRWHLMG_WithTimeSynchronisation)

if (VISA_FOUND)
    add_definitions("-DPOWER_OVERWHELMING_WITH_VISA")
    target_include_directories(${PROJECT_NAME} PRIVATE ${VISA_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${VISA_LIBRARY} nlohmann_json)
endif (VISA_FOUND)

target_include_directories(${PROJECT_NAME}
    PUBLIC $<BUILD_INTERFACE:${IncludeDir}>
    PRIVATE $<BUILD_INTERFACE:${SourceDir}>
    PRIVATE ${AdlInclude}
    PRIVATE ${NvmlInclude}
    PRIVATE ${TinkerforgeInclude})

# Configure the linker.
if (WIN32)
    target_link_libraries(${PROJECT_NAME} Ws2_32)
endif (WIN32)

# Provide the internal API to the unit tests.
set(PowerOverwhelmingTestInclude "${CMAKE_CURRENT_SOURCE_DIR}/src" PARENT_SCOPE)
