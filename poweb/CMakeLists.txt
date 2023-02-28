# CMakeLists.txt
# Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.

cmake_minimum_required(VERSION 3.21.0)


project(poweb)

# First-class hack adapted from https://jslav.livejournal.com/13059.html to get
# access to the VC installation directory.
string(REGEX REPLACE "/MSBuild.+" "/VC" VcInstallDir ${CMAKE_MAKE_PROGRAM})

# Collect source files.
file(GLOB_RECURSE HeaderFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.h" "*.inl")
file(GLOB_RECURSE SourceFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.cpp")

# Define the output.
add_executable(${PROJECT_NAME} ${HeaderFiles} ${SourceFiles})

# Add Nuget packages.
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_PACKAGE_REFERENCES "Microsoft.Web.WebView2_*;Microsoft.Windows.ImplementationLibrary_*")
#add_custom_command(TARGET ${PROJECT_NAME}
#    PRE_BUILD
#    COMMAND nuget restore ${CMAKE_BINARY_DIR}/power-overwelming.sln)

#find_program(NugetExe NAMES nuget)
#if (NOT NugetExe)
#    message("Nuget exeucable not found.")
#    message(FATAL_ERROR "Please install this executable, and run CMake again.")
#endif()
#
#exec_program(${NugetExe}
#    ARGS install "Microsoft.Web.WebView2" -ExcludeVersion -OutputDirectory ${CMAKE_BINARY_DIR}/packages)
#exec_program(${NugetExe}
#    ARGS install "Microsoft.Windows.ImplementationLibrary" -ExcludeVersion -OutputDirectory ${CMAKE_BINARY_DIR}/packages)

# Configure the compiler.
target_include_directories(${PROJECT_NAME} PRIVATE ${JsonInclude})

#target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

# Configure the linker.
target_link_libraries(${PROJECT_NAME} power_overwhelming)

# Deploy DLLs with the executable.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND_EXPAND_LISTS)