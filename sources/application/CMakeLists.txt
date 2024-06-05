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

target_compile_definitions(${TARGET_NAME} PUBLIC
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:MinSizeRel>:_RELEASE>
    $<$<CONFIG:Release>:_RELEASE>
    $<$<CONFIG:RelWithDebInfo>:_RELWITHDEBINFO>
)

if(APPLE)
    SET(CMAKE_XCODE_GENERATE_SCHEME TRUE)
    SET_PROPERTY(TARGET application PROPERTY XCODE_SCHEME_ARGUMENTS "")
endif()

# Define project properties
if(WIN32)
    set_property(TARGET ${TARGET_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../)
    set_property(TARGET ${TARGET_NAME} PROPERTY LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../)
    set_property(TARGET ${TARGET_NAME} PROPERTY ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../)
endif()