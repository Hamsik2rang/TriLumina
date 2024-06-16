set(TARGET_NAME application)

project(${TARGET_NAME})

set(COMMON_HEADERS
    TLMain.h)

source_group("public" FILES ${COMMON_HEADDERS})

set(COMMON_SOURCES
    private/TLMain.cpp
)

source_group("private" FILES ${COMMON_SOURCES})

add_executable(${TARGET_NAME}
    ${COMMON_HEADERS}
    ${COMMON_SOURCES}
)

target_link_libraries(${TARGET_NAME}
    PUBLIC
    engine
    editor
)

target_compile_definitions(${TARGET_NAME} PUBLIC
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:MinSizeRel>:_RELEASE>
    $<$<CONFIG:Release>:_RELEASE>
    $<$<CONFIG:RelWithDebInfo>:_RELWITHDEBINFO>
)

if(APPLE)
    set(CMAKE_XCODE_GENERATE_SCHEME TRUE)

    if(TL_LEAK_CHECK)
        set_target_properties(application PROPERTIES
            XCODE_SCHEME_ARGUMENTS "XCODE_SCHEME_GUARD_MALLOC"
            XCODE_SCHEME_ARGUMENTS "XCODE_SCHEME_MALLOC_SCRIBBLE")
    endif()
endif()

# Define project properties
if(WIN32)
    set_property(TARGET ${TARGET_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../)
    set_property(TARGET ${TARGET_NAME} PROPERTY LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../)
    set_property(TARGET ${TARGET_NAME} PROPERTY ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../)
endif()