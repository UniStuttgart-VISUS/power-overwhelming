# FindVISA.cmake
# Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.

include(FindPackageHandleStandardArgs)


# Determine where the platform-dependent library location is.
if (WIN32)
    if ("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
        set(VisaDirs "$ENV{ProgramFiles\(x86\)}/IVI Foundation/VISA")
    else ()
        set(VisaDirs "$ENV{ProgramFiles}/IVI Foundation/VISA")
    endif ()

    set(VisaLib "visa32.lib")

else (WIN32)
    set(VisaDirs "/usr")
    set(VisaLib "librsvisa.so")
endif (WIN32)

message(STATUS "Searching VISA library ${VisaLib} in ${VisaDirs} ...")

# Find location of public headers
find_path(VISA_INCLUDE_DIR
    NAMES visa.h
    PATHS ${VisaDirs}
    PATH_SUFFIXES "WinNT/RsVisa/include" "Win64/RsVisa/include" "include" "include/rsvisa"
)
mark_as_advanced(VISA_INCLUDE_DIR)

# Find the library
find_library(VISA_LIBRARY
    NAMES ${VisaLib}
    PATHS ${VisaDirs}
    PATH_SUFFIXES "WinNT/RsVisa/Lib/msc" "Win64/RsVisa/Lib/msc" "lib64" "lib"
)
mark_as_advanced(VISA_LIBRARY)

find_package_handle_standard_args(VISA REQUIRED_VARS VISA_INCLUDE_DIR VISA_LIBRARY)
