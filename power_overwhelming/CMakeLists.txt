# CMakeLists.txt
# Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.

cmake_minimum_required(VERSION 3.1.0)

set(IncludeDirectory "include")
set(SourceDirectory "${CMAKE_CURRENT_SOURCE_DIR}")


# Glob all the files to include in the project.
file(GLOB_RECURSE HeaderFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${IncludeDirectory}/*.h" "${SourceDirectory}/*.h" "${IncludeDirectory}/*.inl" "${SourceDirectory}/*.inl")
file(GLOB_RECURSE SourceFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${SourceDirectory}/*.cpp")


# Configure the compiler.
include_directories("${IncludeDirectory}")
add_definitions("-DPOWER_OVERWHELMING_EXPORTS")


# Configure the output.
add_library(trrojancore SHARED ${HeaderFiles} ${SourceFiles})
