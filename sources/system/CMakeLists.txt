set(TARGET_NAME system)

project(${TARGET_NAME})

set(HEADERS
    MVRLog.h
)

set(SOURCES
    private/MVRLog.cpp
)

add_library(${TARGET_NAME}
    STATIC
    ${HEADERS}
    ${SOURCES}
)

target_include_directories(${TARGET_NAME} PRIVATE private)

# Define project properties
if(WIN32)
    set_property(TARGET ${TARGET_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../)
    set_property(TARGET ${TARGET_NAME} PROPERTY LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../)
    set_property(TARGET ${TARGET_NAME} PROPERTY ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../)
endif()