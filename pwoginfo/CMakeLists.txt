# CMakeLists.txt
# Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
# Licensed under the MIT licence. See LICENCE file for details.


project(pwoginfo)

# Collect source files.
file(GLOB_RECURSE HeaderFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.h" "*.inl")
file(GLOB_RECURSE SourceFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.cpp")

# Define the output.
add_executable(${PROJECT_NAME} ${HeaderFiles} ${SourceFiles})

# Configure the linker.
target_link_libraries(${PROJECT_NAME} power_overwhelming)

# Deploy DLLs with the executable.
pwrowg_add_parquet_post_build(${PROJECT_NAME})
pwrowg_add_runtime_dll_post_build(${PROJECT_NAME})
