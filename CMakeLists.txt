cmake_minimum_required(VERSION 3.7.1)

set(ENGINE_NAME "MVR")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(${ENGINE_NAME})

add_subdirectory(dependencies)
add_subdirectory(sources)

if(__APPLE__)
    add_definitions()
endif()