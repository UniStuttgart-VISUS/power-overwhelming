# CMakeLists.txt
# Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.

cmake_minimum_required(VERSION 3.21.0)


project(poweb)

# Collect source files.
file(GLOB_RECURSE HeaderFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.h" "*.inl")
file(GLOB_RECURSE SourceFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.cpp")
file(GLOB_RECURSE ResourceFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.rc")

# Define the output.
add_executable(${PROJECT_NAME} ${HeaderFiles} ${SourceFiles})
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)

# Add resource scripts.
target_sources(${PROJECT_NAME} PRIVATE ${ResourceFiles})

# Add Nuget packages.
set(PackagesConfig "${CMAKE_CURRENT_SOURCE_DIR}/packages.config")
target_sources(${PROJECT_NAME} PRIVATE ${PackagesConfig})

file(READ ${PackagesConfig} Packages)
string(REGEX REPLACE ".*version=\"([0-9\\.]+)\".*" "\\1" WebView2Version ${Packages})
message(STATUS "WebView2 package has version ${WebView2Version}.")
set(WebView2Dir ${CMAKE_BINARY_DIR}/packages/Microsoft.Web.WebView2.${WebView2Version}/build/native)

string(TOLOWER ${CMAKE_MAKE_PROGRAM} MakeProgramme)
if (${MakeProgramme} MATCHES ".*msbuild.*")
    message(STATUS "Restoring Nuget packages ...")
    message(STATUS "${CMAKE_MAKE_PROGRAM} -p:Platform=${CMAKE_VS_PLATFORM_NAME} -t:Restore -p:RestorePackagesConfig=true $(SolutionPath)")
    add_custom_command(TARGET ${PROJECT_NAME}
        PRE_BUILD
        COMMAND ${CMAKE_MAKE_PROGRAM} -p:Platform=${CMAKE_VS_PLATFORM_NAME} -t:Restore -p:RestorePackagesConfig=true $(SolutionPath))
else ()
    message(FATAL_ERROR "An MSBuild-based process is required to restore Nuget packages.")
endif (${MakeProgramme} MATCHES ".*msbuild.*")

# Configure the compiler.
add_definitions("-DUNICODE -D_UNICODE")
target_include_directories(${PROJECT_NAME}
    PRIVATE ${WebView2Dir}/include)

#target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

# Configure the linker.
target_link_libraries(${PROJECT_NAME}
    nlohmann_json
    power_overwhelming
    WIL::WIL
    # I can't believe that actually worked ...
    ${WebView2Dir}/Microsoft.Windows.ImplementationLibrary.targets)

# Deploy DLLs with the executable.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND_EXPAND_LISTS)
