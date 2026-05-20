# CMakeLists.txt
# Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
# Licensed under the MIT licence. See LICENCE file for details.

project(pwrovrnvapi)

find_package(NVAPI REQUIRED)

# Collect source files.
set(IncludeDir "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SourceDir "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE PublicHeaderFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${IncludeDir}/*.h" "${IncludeDir}/*.inl")
file(GLOB_RECURSE PrivateHeaderFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${SourceDir}/*.h" "${SourceDir}/*.inl")
file(GLOB_RECURSE SourceFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${SourceDir}/*.cpp")

source_group("Header Files\\include" FILES  ${PublicHeaderFiles})
source_group("Header Files\\src" FILES ${PrivateHeaderFiles})
source_group("Source Files\\src" FILES ${SourceFiles})


# Define the output.
add_library(${PROJECT_NAME} SHARED ${PublicHeaderFiles} ${PrivateHeaderFiles} ${SourceFiles})

# Configure the compiler.
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${IncludeDir}>
    PRIVATE
        $<BUILD_INTERFACE:${SourceDir}>)
target_compile_definitions(${PROJECT_NAME} PRIVATE PWROVRNVAPI_EXPORTS UNICODE _UNICODE)

# Configure the linker.
target_link_libraries(${PROJECT_NAME} PUBLIC nvapi)

# Allow the parent project accessing the include directory to use the
# library when loading it manually. This is the whole point of this library: we
# want to avoid linking against NVAPI as this would prevent the application from
# running on machines without NVIDIA GPU alltogether.
set(PWROVRNVAPI_INCLUDE_DIR "${IncludeDir}" PARENT_SCOPE)

# Likewise, the parent project needs to know where the wrapper DLL is located to
# copy it manually.
set(PWROVRNVAPI_BINARY "$<TARGET_FILE:${PROJECT_NAME}>" PARENT_SCOPE)

# Install
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Config.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
