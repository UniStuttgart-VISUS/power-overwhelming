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

# Unless disabled for CI, restore packages as pre-build step.
if (NOT ${PWROWG_NoPackageRestore})
    string(TOLOWER ${CMAKE_MAKE_PROGRAM} MakeProgramme)

    if (${MakeProgramme} MATCHES ".*msbuild.*")
        message(STATUS "Restoring Nuget packages ...")
        message(STATUS "${CMAKE_MAKE_PROGRAM} -p:Platform=${CMAKE_VS_PLATFORM_NAME} -t:Restore -p:RestorePackagesConfig=true $(SolutionPath)")
        add_custom_command(TARGET ${PROJECT_NAME}
            PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${PackagesConfig} ${CMAKE_BINARY_DIR} && ${CMAKE_MAKE_PROGRAM} -p:Platform=${CMAKE_VS_PLATFORM_NAME} -t:Restore -p:RestorePackagesConfig=true $(SolutionPath))
    else ()
        message(FATAL_ERROR "An MSBuild-based process is required to restore Nuget packages.")
    endif ()
endif()

# Configure the compiler.
target_compile_definitions(${PROJECT_NAME} PRIVATE UNICODE _UNICODE)
target_include_directories(${PROJECT_NAME} PRIVATE ${WebView2Dir}/include)

#WebView2LoaderPreference Static
#target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

# Configure the linker.
set(EffectivePlatform ${CMAKE_VS_PLATFORM_NAME})
if (${EffectivePlatform} STREQUAL "Win32")
    set(EffectivePlatform "x86")
endif (${EffectivePlatform} STREQUAL "Win32")

target_link_libraries(${PROJECT_NAME}
    power_overwhelming
    nlohmann_json::nlohmann_json
    WIL
    # I can't believe that actually worked ...
    ${WebView2Dir}/Microsoft.Windows.ImplementationLibrary.targets
    ${WebView2Dir}/${EffectivePlatform}/WebView2LoaderStatic.lib)








# Deploy DLLs with the executable.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND_EXPAND_LISTS)
