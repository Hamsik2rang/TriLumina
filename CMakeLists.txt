cmake_minimum_required(VERSION 3.19.2)

set(ENGINE_NAME "TriLumina")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

# list(REMOVE_DUPLICATES CMAKE_CXX_FLAGS_DEBUG) # 중복 제거
if(APPLE)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof -Winline-new-delete -fno-rtti")
endif()

project(${ENGINE_NAME})

include_directories(sources)

add_subdirectory(dependencies)
add_subdirectory(sources)
