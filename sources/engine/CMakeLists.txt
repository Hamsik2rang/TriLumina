set(TARGET_NAME engine)

project(${TARGET_NAME})

add_compile_definitions(MVR_ENGINE)

set(HEADERS
    MVREngine.h
)

set(SOURCES
    private/MVREngine.cpp
)

add_library(${TARGET_NAME}
    SHARED
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(${TARGET_NAME}
    PUBLIC
    render
)

target_include_directories(${TARGET_NAME} PRIVATE private)

# Define project properties
if(WIN32)
    set_property(TARGET ${TARGET_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../)
    set_property(TARGET ${TARGET_NAME} PROPERTY LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../)
    set_property(TARGET ${TARGET_NAME} PROPERTY ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../)
endif()