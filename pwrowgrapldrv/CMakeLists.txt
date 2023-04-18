# CMakeLists.txt
# Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.


# The Windows Driver Kit is required to build this.
find_package(WDK)


project(pwrowgrapldrv)

# Collect source files.
set(IncludeDir ${CMAKE_CURRENT_SOURCE_DIR})
set(SourceDir ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE HeaderFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${IncludeDir}/*.h" "${IncludeDir}/*.inl")
file(GLOB_RECURSE SourceFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${SourceDir}/*.cpp")

# Define the target if we fulfil the requirements.
if (WDK_FOUND)
    # Define the output.
    wdk_add_driver(${PROJECT_NAME} ${HeaderFiles} ${SourceFiles})
endif ()
