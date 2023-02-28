# CMakeLists.txt
# Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.

#find_package(Git REQUIRED)
#include(FetchContent)
#set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})


set(AdlDir ${CMAKE_CURRENT_SOURCE_DIR}/display-library)
set(AdlInclude ${AdlDir}/include PARENT_SCOPE)

#FetchContent_Declare(
#  json
#  GIT_REPOSITORY https://github.com/nlohmann/json.git
#  GIT_TAG v3.11.2
#)

option(JSON_BuildTests OFF)
set(JSON_BuildTests OFF)
mark_as_advanced(JSON_BuildTests)
add_subdirectory(json)

set(NvmlDir ${CMAKE_CURRENT_SOURCE_DIR}/gdk_wddm_amd64_release/nvml)
set(NvmlInclude ${NvmlDir}/include PARENT_SCOPE)

set(RsHmc8015Dir ${CMAKE_CURRENT_SOURCE_DIR}/rshmc8015-cvi-1.0.3)
set(RsHmc8015Include ${RsHmc8015Dir} PARENT_SCOPE)

set(RsRtxDir ${CMAKE_CURRENT_SOURCE_DIR}/rsrtx-cvi-1.4.0)
set(RsRtxInclude ${RsRtxDir} PARENT_SCOPE)

set(TinkerforgeDir ${CMAKE_CURRENT_SOURCE_DIR}/tinkerforge_c_bindings_2_1_32/source PARENT_SCOPE)
set(TinkerforgeInclude ${CMAKE_CURRENT_SOURCE_DIR}/tinkerforge_c_bindings_2_1_32/source PARENT_SCOPE)

set(WilDir ${CMAKE_CURRENT_SOURCE_DIR}/tinkerforge_c_bindings_2_1_32/source PARENT_SCOPE)
set(WilInclude ${WilDir}/include PARENT_SCOPE)

# Cf. https://stackoverflow.com/questions/3766740/overriding-a-default-option-value-in-cmake-from-a-parent-cmakelists-txt
option(FAST_BUILD OFF)
set(FAST_BUILD OFF)
mark_as_advanced(FAST_BUILD)
option(WIL_BUILD_PACKAGING OFF)
set(WIL_BUILD_PACKAGING OFF)
mark_as_advanced(WIL_BUILD_PACKAGING)
option(WIL_BUILD_TESTS OFF)
set(WIL_BUILD_TESTS OFF)
mark_as_advanced(WIL_BUILD_TESTS)
add_subdirectory(wil)
