# FindParquet.cmake
# Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
# Licensed under the MIT licence. See LICENCE file for details.

include(FindPackageHandleStandardArgs)

# TODO: All of this is really wonky and the build system should be overhauled. It had to be quick ...

#message("${CMAKE_PREFIX_PATH}")
find_package(Parquet CONFIG)
