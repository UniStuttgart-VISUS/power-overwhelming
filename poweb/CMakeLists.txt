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

# Add resource scripts.
target_sources(${PROJECT_NAME} PRIVATE ${ResourceFiles})

# Add Nuget packages.
#STRING(TOLOWER ${CMAKE_MAKE_PROGRAM} MakeProgramme)
#set_property(TARGET ${PROJECT_NAME} PROPERTY VS_USER_PROPS "${CMAKE_CURRENT_SOURCE_DIR}/packages.props")
#target_sources(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/packages.config")
#
#if (${MakeProgramme} MATCHES ".*msbuild.*")
#    add_custom_command(TARGET ${PROJECT_NAME}
#        PRE_BUILD
#        COMMAND ${CMAKE_MAKE_PROGRAM} -p:Platform=${CMAKE_VS_PLATFORM_NAME} -t:Restore $(SolutionPath))
#endif (${MakeProgramme} MATCHES ".*msbuild.*")
##    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Configure the compiler.
add_definitions("-DUNICODE -D_UNICODE")

#target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

# Configure the linker.
target_link_libraries(${PROJECT_NAME}
    nlohmann_json
    power_overwhelming
    WIL::WIL)

# Deploy DLLs with the executable.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND_EXPAND_LISTS)
