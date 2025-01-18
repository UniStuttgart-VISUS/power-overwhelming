# CMakeLists.txt
# Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
# Licensed under the MIT licence. See LICENCE file for details.

# Search optional dependencies
find_package(VISA QUIET)

# User-configurable options
option(PWROWG_WithAdl "Build support for the AMD Display Library" ON)
option(PWROWG_WithBenchlab "Build support for the Benchlab telemetry system" ON)
option(PWROWG_WithNvml "Build support for the NVIDIA Management Library" ON)
option(PWROWG_WithPowenetics "Build support for Powenetics" ON)
option(PWROWG_WithTimeSynchronisation "Build support for Cristian's algorithm" OFF)
option(PWROWG_WithVisa "Build support for the VISA-based instruments" ${VISA_FOUND})
cmake_dependent_option(PWROWG_ForceDirect3D11 "Force GPU enumeration via Direct3D 11" OFF WIN32 OFF)
mark_as_advanced(FORCE PWROWG_ForceDirect3D11)

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
target_compile_definitions(${PROJECT_NAME} PRIVATE POWER_OVERWHELMING_EXPORTS UNICODE _UNICODE)

if (PWROWG_WithAdl)
    target_compile_definitions(${PROJECT_NAME} PUBLIC POWER_OVERWHELMING_WITH_ADL)
endif ()

if (PWROWG_WithNvml)
    target_compile_definitions(${PROJECT_NAME} PUBLIC POWER_OVERWHELMING_WITH_NVML)
endif ()

if (PWROWG_WithTimeSynchronisation)
    target_compile_definitions(${PROJECT_NAME} PUBLIC POWER_OVERWHELMING_WITH_TIME_SYNCHRONISER)
endif ()

if (PWROWG_WithVisa)
    find_package(VISA REQUIRED)
    add_definitions("-DPOWER_OVERWHELMING_WITH_VISA")
    target_include_directories(${PROJECT_NAME} PRIVATE ${VISA_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME})
endif ()

if (PWROWG_CustomTinkerforgeFirmwareMajor)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CUSTOM_TINKERFORGE_FIRMWARE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CUSTOM_TINKERFORGE_FIRMWARE_MJ=${PWROWG_CustomTinkerforgeFirmwareMajor})

    if (PWROWG_CustomTinkerforgeFirmwareMinor)
        target_compile_definitions(${PROJECT_NAME} PRIVATE CUSTOM_TINKERFORGE_FIRMWARE_MN=${PWROWG_CustomTinkerforgeFirmwareMinor})
    endif ()

    if (PWROWG_CustomTinkerforgeFirmwareRevision)
        target_compile_definitions(${PROJECT_NAME} PRIVATE CUSTOM_TINKERFORGE_FIRMWARE_RV=${PWROWG_CustomTinkerforgeFirmwareRevision})
    endif ()
endif ()

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${IncludeDir}>
    PRIVATE
        $<BUILD_INTERFACE:${SourceDir}>)

if (WIN32)
    target_compile_options(${PROJECT_NAME} PRIVATE "-doc")
endif ()

target_link_libraries(${PROJECT_NAME}
    PRIVATE adl nlohmann_json::nlohmann_json nvml tinkerforge)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC Ws2_32)
else ()
    find_package(Threads REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_DL_LIBS} Threads::Threads)
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif ()

# Provide the internal API to the unit tests.
set(PowerOverwhelmingTestInclude "${CMAKE_CURRENT_SOURCE_DIR}/src" PARENT_SCOPE)

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
