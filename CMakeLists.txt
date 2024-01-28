cmake_minimum_required(VERSION 3.7.1)

set(ENGINE_NAME "MVR")

set(CMAKE_CPP_STANDARD 17)

project(${ENGINE_NAME})

add_subdirectory(dependencies)
add_subdirectory(sources)
