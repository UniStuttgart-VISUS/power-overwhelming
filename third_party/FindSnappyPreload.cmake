# FindSnappyPreload.cmake
# Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
# Licensed under the MIT licence. See LICENCE file for details.

include(FindPackageHandleStandardArgs)

if (SnappyPreload_FOUND)
    return()
endif ()


find_package(Snappy CONFIG)
set(SnappyPreload_FOUND ${Snappy_FOUND})

if (${SnappyPreload_FOUND})
    set(SnappyPreload_FOUND TRUE)

    # Get the the CMake-generated targets.
    include("${Snappy_DIR}/SnappyTargets.cmake")

    get_filename_component(_dir "${Snappy_LIB}" DIRECTORY)
    get_filename_component(_lib "${_dir}" NAME)
    get_filename_component(_dir "${_dir}" DIRECTORY)

    #if(NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE MATCHES "^[Dd][Ee][Bb][Uu][Gg]$")
    #    set(_libs "${_dir}/debug/${_lib}" "${_dir}/${_lib}")
    #else ()
    #    set(_libs "${_dir}/${_lib}" "${_dir}/debug/${_lib}")
    #endif()
    #if (NOT "${CMAKE_LIBRARY_PATH}")
    #    set(CMAKE_LIBRARY_PATH "${_libs}")
    #else ()
    #    list(INSERT 0 CMAKE_LIBRARY_PATH "${_libs}")
    #endif ()

    # And now, we crowbar the target into Arrow: We claim that the
    # Arrow-provided module was successful such that it does not do anything
    # and alias its target to ours.
    set(SnappyAlt_FOUND TRUE)
    add_library(Snappy::snappy-static ALIAS Snappy::snappy)

    #if(NOT CMAKE_PROPERTY_LIST)
    #    execute_process(COMMAND cmake --help-property-list OUTPUT_VARIABLE CMAKE_PROPERTY_LIST)
    #    string(REGEX REPLACE ";" "\\\\;" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")
    #    string(REGEX REPLACE "\n" ";" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")
    #    list(REMOVE_DUPLICATES CMAKE_PROPERTY_LIST)
    #endif()
    #foreach(property ${CMAKE_PROPERTY_LIST})
    #    string(REPLACE "<CONFIG>" "${CMAKE_BUILD_TYPE}" property ${property})
    #    # Fix https://stackoverflow.com/questions/32197663/how-can-i-remove-the-the-location-property-may-not-be-read-from-target-error-i
    #    if(property STREQUAL "LOCATION" OR property MATCHES "^LOCATION_" OR property MATCHES "_LOCATION$")
    #        continue()
    #    endif()
    #    get_property(was_set TARGET Snappy::snappy-static PROPERTY ${property} SET)
    #    if(was_set)
    #        get_target_property(value Snappy::snappy-static ${property})
    #        message("${property} = ${value}")
    #    endif()
    #endforeach()

    unset(_dir)
    unset(_lib)
    unset(_libs)
endif()
