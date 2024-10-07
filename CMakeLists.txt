# Copyright (c) 2024 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.19.0)

set(MBED_PATH ${CMAKE_CURRENT_SOURCE_DIR}/mbed-os CACHE INTERNAL "")
set(MBED_CONFIG_PATH ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")
set(APP_TARGET Beer-Carbonation-System)

include(${MBED_PATH}/tools/cmake/app.cmake)

project(${APP_TARGET})

add_subdirectory(${MBED_PATH})

include_directories(include)

file(GLOB all_srcs "${PROJECT_SOURCE_DIR}/include/*.h"
                   "${PROJECT_SOURCE_DIR}/include/*.hpp"
        	       "${PROJECT_SOURCE_DIR}/src/*.cpp"
        	   "${PROJECT_SOURCE_DIR}/src/*.c")

add_executable(${APP_TARGET}
	       ${all_srcs})

target_link_libraries(${APP_TARGET} mbed-os)

mbed_set_post_build(${APP_TARGET})

option(VERBOSE_BUILD "Have a verbose build process")
if(VERBOSE_BUILD)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()
