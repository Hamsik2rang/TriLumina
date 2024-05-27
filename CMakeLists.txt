cmake_minimum_required(VERSION 3.19.2)

set(ENGINE_NAME "MVR")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS_DEBUG "-D_DEBUG")

project(${ENGINE_NAME})

include_directories(sources)

add_subdirectory(dependencies)
add_subdirectory(sources)
