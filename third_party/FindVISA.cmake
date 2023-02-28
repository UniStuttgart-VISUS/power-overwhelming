# FindVISA.cmake
# Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.

include(FindPackageHandleStandardArgs)


# Potential installation locations of VISA
set(VisaDirs "$ENV{ProgramFiles}/IVI Foundation/VISA" "$ENV{ProgramFiles\(x86\)}/IVI Foundation/VISA")
message(STATUS "Searching VISA library in ${VisaDirs} ...")

# Determine the name of the library for the current platform
if ("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
    set(VisaLibrary "visa32.lib")
else ("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
    set(VisaLibrary "visa64.lib")
endif ("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")

# Find location of public headers
find_path(VISA_INCLUDE_DIR
    NAMES visa.h
    PATHS ${VisaDirs}
    PATH_SUFFIXES "WinNT/Include" "Win64/Include"
)
mark_as_advanced(VISA_INCLUDE_DIR)

# Find the library
find_library(VISA_LIBRARY
    NAMES ${VisaLibrary}
    PATHS ${VisaDirs}
    PATH_SUFFIXES "WinNT/lib/msc" "WinNT/Lib_x64/msc" "Win64/Lib_x64/msc"
)
mark_as_advanced(VISA_LIBRARY)

find_package_handle_standard_args(VISA REQUIRED_VARS VISA_INCLUDE_DIR VISA_LIBRARY)
