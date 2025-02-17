cmake_minimum_required(VERSION 3.19.0)

## Mbed configuration
set(MBED_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/mbed-os CACHE INTERNAL "")
set(MBED_CONFIG_PATH ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")

include(${MBED_PATH}/tools/cmake/app.cmake)

## App configuration
project(beer-carbonation-system)

add_subdirectory(${MBED_PATH})

set(APP_TARGET beer-carbonation-system)

include_directories(include)

file(GLOB app_target_sources
  "${PROJECT_SOURCE_DIR}/include/*.h"
  "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(${APP_TARGET} ${app_target_sources})

target_link_libraries(${APP_TARGET} PRIVATE mbed-os)

mbed_set_post_build(${APP_TARGET})

option(VERBOSE_BUILD "Have a verbose build process")
if(VERBOSE_BUILD)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()
