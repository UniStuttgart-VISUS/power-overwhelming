# FindSnappyPreload.cmake
# Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
# Licensed under the MIT licence. See LICENCE file for details.

include(FindPackageHandleStandardArgs)

# Apache Arrow uses its own modules to find dependencies, including Snappy,
# and takes significant precautions to prevent us from meddling with this
# process. Unfortunately, there is a bug that prevents multi-target solutions
# from working properly (https://github.com/apache/arrow/issues/49499). The
# issue causes debug builds to link against the release build of Snappy, which
# in turn causes a linker error. As we need a fairly old version, we cannot
# apply the fix from the issue.
# Therefore, the infamous  Pre-Loading Institute of Universiät Stuttgart
# "preloads" Snappy using this module, which must be included before including
# Arrow/Parquet (currently only the Power Overwhelming library itself and the
# test driver) to trick Arrow into believing that it already ran its find module
# for snappy, thus leaving the correct version in place.

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

    # And now, we crowbar the target into Arrow: We claim that the
    # Arrow-provided module was successful such that it does not do anything
    # and alias its target to ours.
    set(SnappyAlt_FOUND TRUE)
    add_library(Snappy::snappy-static ALIAS Snappy::snappy)

    unset(_dir)
    unset(_lib)
    unset(_libs)
endif()
