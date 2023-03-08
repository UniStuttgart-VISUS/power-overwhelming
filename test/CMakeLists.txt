# CMakeLists.txt
# Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.

cmake_minimum_required(VERSION 3.21.0)


project(test)

# First-class hack adapted from https://jslav.livejournal.com/13059.html to get
# access to the VC installation directory.
string(REGEX REPLACE "/MSBuild.+" "/VC" VcInstallDir ${CMAKE_MAKE_PROGRAM})

# Collect source files.
file(GLOB_RECURSE HeaderFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.h" "*.inl")
file(GLOB_RECURSE SourceFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.cpp")

# Define the output.
add_library(${PROJECT_NAME} SHARED ${HeaderFiles} ${SourceFiles})

# Configure the compiler.
add_definitions("-DUNICODE -D_UNICODE")

# In the test driver, the compiler needs to know about the private includes of
# the library, so we add these manually.
target_include_directories(${PROJECT_NAME}
    PRIVATE ${AdlInclude}
    PRIVATE ${NvmlInclude}
    PRIVATE ${PowerOverwhelmingTestInclude}
    PRIVATE ${TinkerforgeInclude})

#target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

# Configure the linker: besides the library to test, we also need to link the
# Visual Studio testing framework.
target_link_directories(${PROJECT_NAME} PRIVATE "${VcInstallDir}/Auxiliary/VS/UnitTest/lib/$(LibrariesArchitecture)")
target_link_libraries(${PROJECT_NAME}
    Microsoft.VisualStudio.TestTools.CppUnitTestFramework.lib
    SetupApi.lib
    nlohmann_json
    power_overwhelming)

# Grab the DLLs to be tested and copy them to the output directory such that
# the Visual Studio test driver finds everything.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND_EXPAND_LISTS)
