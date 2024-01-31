set(TARGET_NAME application)

project(${TARGET_NAME})

set(SOURCES
    private/MVRMain.cpp
)

add_executable(${TARGET_NAME}
    ${SOURCES}
)

target_link_libraries(${TARGET_NAME}
    PUBLIC
    editor
)
target_include_directories(${TARGET_NAME} PRIVATE private)

# Define project properties
if(WIN32)
    set_property(TARGET ${TARGET_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../)
    set_property(TARGET ${TARGET_NAME} PROPERTY LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../)
    set_property(TARGET ${TARGET_NAME} PROPERTY ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../)
endif()