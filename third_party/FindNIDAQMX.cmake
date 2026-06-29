# FindNIDAQMX.cmake
# Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
# Licensed under the MIT licence. See LICENCE file for details.

include(FindPackageHandleStandardArgs)


# Determine where the platform-dependent library location is.
if(DEFINED ENV{NIEXTCCOMPILERSUPP})
    set(NIDAQMX_DIR "$ENV{NIEXTCCOMPILERSUPP}")
    message(STATUS "Have NIEXTCCOMPILERSUPP environment variable: ${NIDAQMX_DIR}")

else()
    if (WIN32)
        set (NIDAQMX_DIR "National Instruments/Shared/ExternalCompilerSupport/C")
        set (NIDAQMX_DIR "$ENV{ProgramFiles}/${NiCDir}")
        if (NOT EXISTS ${NIDAQMX_DIR})
            set (NIDAQMX_DIR "$ENV{ProgramFiles\(x86\)}/${NiCDir}")
        endif ()

    else ()
        # TODO
        #set(NiDir "/usr")
    endif ()
    message(STATUS "Use custom NI directory: ${NIDAQMX_DIR}")
endif ()

if (WIN32)
    if ("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
        set(NiLibDir "lib32")
    else ()
        set(NiLibDir "lib64")
    endif ()

    set(NiLib "NIDAQmx.lib")
else ()
    # TODO
    set(NiLibDir "")
    set(NiLib "nidaqmx")
endif ()

message(STATUS "Searching NI-DAQmx library ${NiLib} in ${NIDAQMX_DIR} ...")

# Find the base location
find_path(NIDAQMX_DIR
    NAMES include
    PATHS ${NIDAQMX_DIR}
)
mark_as_advanced(NIDAQMX_DIR)

# Find location of public headers
find_path(NIDAQMX_INCLUDE_DIR
    NAMES NIDAQmx.h
    PATHS ${NIDAQMX_DIR}
    PATH_SUFFIXES "include"
)
mark_as_advanced(NIDAQMX_INCLUDE_DIR)

# Find the library
find_library(NIDAQMX_LIBRARY
    NAMES ${NiLib}
    PATHS ${NIDAQMX_DIR}
    PATH_SUFFIXES "${NiLibDir}/msvc"
)
mark_as_advanced(NIDAQMX_LIBRARY)

find_package_handle_standard_args(NIDAQMX REQUIRED_VARS NIDAQMX_DIR NIDAQMX_INCLUDE_DIR NIDAQMX_LIBRARY)
