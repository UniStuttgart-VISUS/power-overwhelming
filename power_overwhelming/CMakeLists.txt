# CMakeLists.txt
# Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.

# User-configurable options
option(PWROWG_WithAdl "Build support for the AMD Display Library" ON)
option(PWROWG_WithNvml "Build support for the NVIDIA Management Library" ON)
option(PWROWG_WithTimeSynchronisation "Build support for Cristian's algorithm" OFF)
option(PWROWG_WithVisa "Build support for the VISA-based instruments" ON)
cmake_dependent_option(PWROWG_ForceDirect3D11 "Force GPU enumeration via Direct3D 11" OFF WIN32 OFF)
mark_as_advanced(FORCE PWROWG_ForceDirect3D11)

# If requested, search the locally installed VISA library
if (PWROWG_WithVisa)
    find_package(VISA)
endif ()

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

if (VISA_FOUND)
    add_definitions("-DPOWER_OVERWHELMING_WITH_VISA")
    target_include_directories(${PROJECT_NAME} PRIVATE ${VISA_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME})
endif ()

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${IncludeDir}>
    PRIVATE
        $<BUILD_INTERFACE:${SourceDir}>)

target_link_libraries(${PROJECT_NAME}
    PUBLIC salieri
    PRIVATE adl nlohmann_json nvml tinkerforge)

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
