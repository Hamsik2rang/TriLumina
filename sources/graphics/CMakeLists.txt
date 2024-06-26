set(TARGET_NAME graphics)

set(COMMON_HEADERS
    TLGraphicsContext.h
)

source_group("public" FILES ${COMMON_HEADERS})

set(COMMON_SOURCES
    private/TLGraphicsContext.cpp
)

source_group("private" FILES ${COMMON_SOURCES})

add_library(${TARGET_NAME}
    STATIC
    ${COMMON_HEADERS}
    ${COMMON_SOURCES}
)

target_link_libraries(${TARGET_NAME}
    PUBLIC
    system
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