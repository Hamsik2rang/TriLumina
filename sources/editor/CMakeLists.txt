set(TARGET_NAME editor)

add_compile_definitions(MVR_EDITOR)

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

target_link_libraries(${TARGET_NAME}
    PUBLIC
    engine
)

target_compile_definitions(${TARGET_NAME} PUBLIC
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:MinSizeRel>:_RELEASE>
    $<$<CONFIG:Release>:_RELEASE>
    $<$<CONFIG:RelWithDebInfo>:_RELWITHDEBINFO>
)
# Define project properties
if(WIN32)
    set_property(TARGET ${TARGET_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../)
    set_property(TARGET ${TARGET_NAME} PROPERTY LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../)
    set_property(TARGET ${TARGET_NAME} PROPERTY ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../)
endif()