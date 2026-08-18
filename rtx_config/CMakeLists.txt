# CMakeLists.txt
# Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
# Licensed under the MIT licence. See LICENCE file for details.

project(rtx_config)

# Collect source files.
file(GLOB_RECURSE HeaderFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.h" "*.inl")
file(GLOB_RECURSE SourceFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.cpp")
file(GLOB_RECURSE ResourceFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.rc")

# Define the output.
add_executable(${PROJECT_NAME} ${HeaderFiles} ${SourceFiles} ${ResourceFiles})

# Add resource scripts.
if (WIN32)
    target_sources(${PROJECT_NAME} PRIVATE ${ResourceFiles})
endif ()

# Enable VISA.
find_package(VISA REQUIRED)
target_compile_definitions(${PROJECT_NAME} PUBLIC POWER_OVERWHELMING_WITH_VISA)
target_include_directories(${PROJECT_NAME} PRIVATE ${VISA_INCLUDE_DIR})

# Configure the linker.
target_link_libraries(${PROJECT_NAME} PRIVATE power_overwhelming)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE WIL::WIL Comctl32)
endif ()

# Deploy DLLs with the executable.
if (WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND_EXPAND_LISTS)
endif (WIN32)
