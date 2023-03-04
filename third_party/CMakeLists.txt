# CMakeLists.txt
# Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.

find_package(Git REQUIRED)

include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
mark_as_advanced(FETCHCONTENT_BASE_DIR)
set(FETCHCONTENT_QUIET ON)
mark_as_advanced(FETCHCONTENT_QUIET)

# AMD Display Library (this is a bit hacky ...)
FetchContent_Declare(adl
    GIT_REPOSITORY "https://github.com/GPUOpen-LibrariesAndSDKs/display-library.git"
    GIT_TAG "17.0"
    GIT_PROGRESS TRUE
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/adl"
)
FetchContent_MakeAvailable(adl)
set(AdlDir ${CMAKE_CURRENT_SOURCE_DIR}/adl)
set(AdlInclude ${AdlDir}/include PARENT_SCOPE)

# JSON library
FetchContent_Declare(nlohmann_json
    GIT_REPOSITORY "https://github.com/nlohmann/json.git"
    GIT_TAG "v3.11.2"
    GIT_PROGRESS TRUE
)
# Cf. https://stackoverflow.com/questions/3766740/overriding-a-default-option-value-in-cmake-from-a-parent-cmakelists-txt
option(JSON_BuildTests OFF)
set(JSON_BuildTests OFF)
mark_as_advanced(JSON_BuildTests)
FetchContent_MakeAvailable(nlohmann_json)

# NVIDIA Management Library
set(NvmlDir ${CMAKE_CURRENT_SOURCE_DIR}/gdk_wddm_amd64_release/nvml)
set(NvmlInclude ${NvmlDir}/include PARENT_SCOPE)

# Rohde & Schwarz HMC 8015
set(RsHmc8015Dir ${CMAKE_CURRENT_SOURCE_DIR}/rshmc8015-cvi-1.0.3)
set(RsHmc8015Include ${RsHmc8015Dir} PARENT_SCOPE)

# Rohde & Schwarz RTB family
set(RsRtxDir ${CMAKE_CURRENT_SOURCE_DIR}/rsrtx-cvi-1.4.0)
set(RsRtxInclude ${RsRtxDir} PARENT_SCOPE)

# Tinkerforge API
set(TinkerforgeDir ${CMAKE_CURRENT_SOURCE_DIR}/tinkerforge_c_bindings_2_1_32/source PARENT_SCOPE)
set(TinkerforgeInclude ${CMAKE_CURRENT_SOURCE_DIR}/tinkerforge_c_bindings_2_1_32/source PARENT_SCOPE)

# Windows Implementation Library
FetchContent_Declare(wil
    GIT_REPOSITORY "https://github.com/microsoft/wil"
    GIT_TAG "v1.0.230202.1"
    GIT_PROGRESS TRUE
)
option(FAST_BUILD OFF)
set(FAST_BUILD OFF)
mark_as_advanced(FAST_BUILD)
option(WIL_BUILD_PACKAGING OFF)
set(WIL_BUILD_PACKAGING OFF)
mark_as_advanced(WIL_BUILD_PACKAGING)
option(WIL_BUILD_TESTS OFF)
set(WIL_BUILD_TESTS OFF)
mark_as_advanced(WIL_BUILD_TESTS)
FetchContent_MakeAvailable(wil)
