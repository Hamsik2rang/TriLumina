set(TARGET_NAME editor)

project(${TARGET_NAME})

set(HEADERS
    MVREditor.h
)

set(SOURCES
    private/MVREditor.cpp
)

add_library(${TARGET_NAME}
    SHARED
    ${HEADERS}
    ${SOURCES}
)

# target_link_libraries(${TARGET_NAME}
# PUBLIC
# engine
# )
target_include_directories(${TARGET_NAME} PRIVATE private)

# Define project properties
set_property(TARGET ${TARGET_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set_property(TARGET ${TARGET_NAME} PROPERTY LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set_property(TARGET ${TARGET_NAME} PROPERTY ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})