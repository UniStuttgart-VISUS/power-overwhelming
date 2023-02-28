# FindVISA.cmake
# Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.

include(FindPackageHandleStandardArgs)


# Determine where the platform-dependent library location is.
if ("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
    set(VisaDirs "$ENV{ProgramFiles\(x86\)}/IVI Foundation/VISA")
else ()
    set(VisaDirs "$ENV{ProgramFiles}/IVI Foundation/VISA")
endif ()

message(STATUS "Searching VISA library in ${VisaDirs} ...")

# Find location of public headers
find_path(VISA_INCLUDE_DIR
    NAMES visa.h
    PATHS ${VisaDirs}
    PATH_SUFFIXES "WinNT/RsVisa/include" "Win64/RsVisa/include"
)
mark_as_advanced(VISA_INCLUDE_DIR)

# Find the library
find_library(VISA_LIBRARY
    NAMES visa32.lib
    PATHS ${VisaDirs}
    PATH_SUFFIXES "WinNT/RsVisa/Lib/msc" "Win64/RsVisa/Lib/msc"
)
mark_as_advanced(VISA_LIBRARY)

find_package_handle_standard_args(VISA REQUIRED_VARS VISA_INCLUDE_DIR VISA_LIBRARY)
