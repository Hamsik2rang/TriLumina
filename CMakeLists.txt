cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(ENGINE_NAME "TriLumina")

project(${ENGINE_NAME})

set(TL_ROOT_DIR ${TriLumina_SOURCE_DIR})
message(STATUS "TL_ROOT_DIR: ${TL_ROOT_DIR}")

set(TL_BIN_DIR ${TriLumina_BINARY_DIR})
message(STATUS "TL_BIN_DIR ${TL_BIN_DIR}")

set(TL_SRC_DIR ${TL_ROOT_DIR}/sources)
message(STATUS "TL_SRC_DIR ${TL_SRC_DIR}")

set(TL_DEPS_DIR ${TL_ROOT_DIR}/dependencies)
message(STATUS "TL_DEPS_DIR ${TL_DEPS_DIR}")

if(APPLE)
    if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "arm64")
        set(TL_ARCH "arm64")
    else()
        set(TL_ARCH "x86_64")
    endif()

    message(STATUS "TL_ARCH is ${TL_ARCH}")

    set(TL_DEPS_LIB_DIR ${TL_DEPS_DIR}/lib/osx/${TL_ARCH})
    set(TL_DEPS_DLL_DIR ${TL_DEPS_DIR}/dll/osx/${TL_ARCH})
else() # MSVC
    if("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "X86")
        # set(TL_ARCH "i686")
        message(FATAL_ERROR "TriLumina is only support x64")
    elseif("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "x64")
        set(TL_ARCH "x86_64")
    elseif("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "ARM")
        set(TL_ARCH "arm64")
    elseif()
        message(FATAL_ERROR "Failed to determine the MSVC target architecture: ${MSVC_C_ARCHITECTURE_ID}")
    endif()

    message(STATUS "TL_ARCH is ${TL_ARCH}")

    set(TL_DEPS_LIB_DIR ${TL_DEPS_DIR}/lib/win/${TL_ARCH})
    set(TL_DEPS_DLL_DIR ${TL_DEPS_DIR}/dll/win/${TL_ARCH})
endif()

set(TL_DEPS_INCLUDE_DIR ${TL_DEPS_DIR}/include)

# Vulkan
if(APPLE)
    # dylib? static lib으로 들어가야 할 듯.
    set(VULKAN ${TL_DEPS_DLL_DIR}/libvulkan.1.dylib)
else()
    set(VULKAN ${TL_DEPS_LIB_DIR}/vulkan-1.lib)
endif()

message("Vulkan has found from: ${VULKAN}")

if(APPLE)
else()
    set(SDL ${TL_DEPS_LIB_DIR}/SDL2.lib ${TL_DEPS_LIB_DIR}/SDL2main.lib ${TL_DEPS_LIB_DIR}/SDL2test.lib)
endif()

if(APPLE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof -Winline-new-delete -fno-rtti")
endif()

set(INSTALL_FOLDER "$<TARGET_FILE_DIR:application>")

# if(WIN32)
# set(CMAKE_INSTALL_PREFIX "C:/Program Files/${CMAKE_PROJECT_NAME}")
# endif()
include_directories(sources)
include_directories(SYSTEM ${TL_DEPS_INCLUDE_DIR})

option(TL_DEVELOPER "" OFF)
option(TL_LEAK_CHECK "" OFF)

if(TL_DEVELOPER)
    add_definitions("-DTL_DEVELOPER")
endif()

if(TL_LEAK_CHECK)
    add_definitions("-DTL_LEAK_CHECK")
endif()

add_subdirectory(dependencies)
add_subdirectory(sources)
