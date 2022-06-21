# CMakeLists.txt
# Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.

cmake_minimum_required(VERSION 3.15.0)


# WARNING: THIS IS ONLY A HACK FOR TRROJAN AND NOT INTENDED FOR PRODUCTION!


if (WIN32)
    message(STATUS "Retrieving submodules power-overwhelming ...")
    execute_process(COMMAND
      ${GIT_EXECUTABLE} submodule update --init
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/third_party")

    message(STATUS "Building power-overwhelming ...")
    execute_process(COMMAND ${CMAKE_MAKE_PROGRAM} -p:Platform=${CMAKE_VS_PLATFORM_NAME} -p:Configuration=Release power-overwhelming.sln
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif (WIN32)
