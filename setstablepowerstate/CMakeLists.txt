﻿# CMakeLists.txt
# Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
# Licensed under the MIT licence. See LICENCE file for details.

cmake_minimum_required(VERSION 3.21.0)


project(setstablepowerstate)

# Collect source files.
file(GLOB_RECURSE HeaderFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.h" "*.inl")
file(GLOB_RECURSE SourceFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.cpp")

# Define the output.
add_executable(${PROJECT_NAME} ${HeaderFiles} ${SourceFiles})

# Configure the linker.
target_link_libraries(${PROJECT_NAME} power_overwhelming)

# Deploy DLLs with the executable.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND_EXPAND_LISTS)