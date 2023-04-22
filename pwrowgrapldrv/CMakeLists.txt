# CMakeLists.txt
# Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.

cmake_minimum_required(VERSION 3.15)
find_package(WDK)


project(pwrowgrapldrv)

# Collect source files.
set(IncludeDir ${CMAKE_CURRENT_SOURCE_DIR})
set(SourceDir ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE HeaderFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${IncludeDir}/*.h" "${IncludeDir}/*.inl")
file(GLOB_RECURSE SourceFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${SourceDir}/*.cpp")
file(GLOB_RECURSE InfFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${SourceDir}/*.inf")

source_group("INF Files" FILES  ${InfFiles})


# Define the target if we fulfil the requirements.
if (WDK_FOUND)
    set(PWROWG_KmdfVersion "1.11" CACHE STRING "The version of the Kernel Mode Driver Framework to use")
    mark_as_advanced(PWROWG_KmdfVersion)
    set(PWROWG_StampInfPath "${WDK_ROOT}/bin/${WDK_VERSION}/${WDK_PLATFORM}/stampinf.exe" CACHE STRING "Path to the stampinf tool")
    mark_as_advanced(PWROWG_StampInfPath)
    set(PWROWG_Inf2CatPath "${WDK_ROOT}/bin/${WDK_VERSION}/x86/Inf2Cat.exe" CACHE STRING "Path to the Inf2Cat tool")
    mark_as_advanced(PWROWG_Inf2CatPath)
    set(PWROWG_DriverTargets "7_${WDK_PLATFORM},8_${WDK_PLATFORM},6_3_${WDK_PLATFORM},10_${WDK_PLATFORM}" CACHE STRING "List of OS identifiers passed to Inf2Cat")
    mark_as_advanced(PWROWG_DriverTargets)

    # Derive the architecture for the INF file. Unfortunately, this string is
    # not the same for x64 as ${WDK_PLATFORM}, so we need to adjust it.
    if (${WDK_PLATFORM} STREQUAL "x64")
        set(InfArchitecture "amd64")
    else ()
        set(InfArchitecture ${WDK_PLATFORM})
    endif ()

    # Derive the name of the co-installer DLL from ${PWROWG_KmdfVersion}.
    string(REGEX MATCH "([0-9]+)\.([0-9]+)" _ ${PWROWG_KmdfVersion})
    string(LENGTH ${CMAKE_MATCH_1} KmdfMajorLength)
    math(EXPR KmdfMajorPad "2 - ${KmdfMajorLength}")
    if (${KmdfMajorPad} GREATER 0)
        string(REPEAT "0" ${KmdfMajorPad} KmdfMajorPad)
    else ()
        set(KmdfMajorPad "")
    endif ()
    string(LENGTH ${CMAKE_MATCH_2} KmdfMinorLength)
    math(EXPR KmdfMinorPad "3 - ${KmdfMinorLength}")
    if (${KmdfMinorPad} GREATER 0)
        string(REPEAT "0" ${KmdfMinorPad} KmdfMinorPad)
    else ()
        set(KmdfMinorPad "")
    endif ()
    set(WdfCoInstallerVersion ${KmdfMajorPad})
    string(APPEND WdfCoInstallerVersion ${CMAKE_MATCH_1})
    string(APPEND WdfCoInstallerVersion ${KmdfMinorPad})
    string(APPEND WdfCoInstallerVersion ${CMAKE_MATCH_2})

    # Define the output.
    wdk_add_driver(${PROJECT_NAME}
        KMDF ${PWROWG_KmdfVersion}
        ${HeaderFiles}
        ${SourceFiles})
    target_link_libraries(${PROJECT_NAME} WDK::WDMSEC)

    # Stamp and deploy the inf files for installing the driver.
    foreach (InfFile ${InfFiles})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/${InfFile} $<TARGET_FILE_DIR:${PROJECT_NAME}>
            COMMAND ${PWROWG_StampInfPath} -f $<SHELL_PATH:$<TARGET_FILE_DIR:${PROJECT_NAME}>>\\${InfFile} -a ${InfArchitecture} -k ${PWROWG_KmdfVersion} -v * -d *
            COMMAND ${PWROWG_Inf2CatPath} /driver:$<SHELL_PATH:$<TARGET_FILE_DIR:${PROJECT_NAME}>> /os:${PWROWG_DriverTargets}
            WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${InfFile})
    endforeach ()

    # Copy the WDF coinstaller to the output directory.
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${WDK_ROOT}/redist/wdf/${WDK_PLATFORM}/WdfCoinstaller${WdfCoInstallerVersion}.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND_EXPAND_LISTS)
endif ()
