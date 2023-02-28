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

set(JsonDir ${CMAKE_CURRENT_SOURCE_DIR}/json)
set(JsonInclude ${JsonDir}/include PARENT_SCOPE)
set(JSON_BuildTests OFF)

set(NvmlDir ${CMAKE_CURRENT_SOURCE_DIR}/gdk_wddm_amd64_release/nvml)
set(NvmlInclude ${NvmlDir}/include PARENT_SCOPE)

set(RsHmc8015Dir ${CMAKE_CURRENT_SOURCE_DIR}/rshmc8015-cvi-1.0.3)
set(RsHmc8015Include ${RsHmc8015Dir} PARENT_SCOPE)

set(RsRtxDir ${CMAKE_CURRENT_SOURCE_DIR}/rsrtx-cvi-1.4.0)
set(RsRtxInclude ${RsRtxDir} PARENT_SCOPE)

set(TinkerforgeDir ${CMAKE_CURRENT_SOURCE_DIR}/tinkerforge_c_bindings_2_1_32/source PARENT_SCOPE)
set(TinkerforgeInclude ${CMAKE_CURRENT_SOURCE_DIR}/tinkerforge_c_bindings_2_1_32/source PARENT_SCOPE)
