# CMakeLists.txt
# Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
# Licensed under the MIT licence. See LICENCE file for details.

project(usbpd)

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
target_compile_definitions(${PROJECT_NAME} PRIVATE USBPD_EXPORTS UNICODE _UNICODE)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${IncludeDir}>
    PRIVATE
        $<BUILD_INTERFACE:${SourceDir}>)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE passmark_usb_pd_tester)
endif ()

# Install
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Config.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
