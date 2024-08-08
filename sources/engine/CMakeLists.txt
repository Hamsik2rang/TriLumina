set(TARGET_NAME engine)

add_compile_definitions(TL_ENGINE)

set(COMMON_HEADERS
    TLEngine.h
)

source_group("public" FILES ${COMMON_HEADERS})

set(COMMON_SOURCES
    private/TLEngine.cpp
)

source_group("private" FILES ${COMMON_SOURCES})

add_library(${TARGET_NAME}
    SHARED
    ${COMMON_HEADERS}
    ${COMMON_SOURCES}
)

if(APPLE)
    target_link_libraries(${TARGET_NAME}
        PUBLIC
        "-Wl"
        graphics
        "-framework OpenGL -framework Foundation -framework CoreFoundation -framework QuartzCore -framework AppKit -framework IOKit  -framework Metal -framework GameController"
    )
else()
    target_link_libraries(${TARGET_NAME}
        PUBLIC
        "-Wl"
        graphics
    )
endif()

target_compile_definitions(${TARGET_NAME} PUBLIC
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:MinSizeRel>:_RELEASE>
    $<$<CONFIG:Release>:_RELEASE>
    $<$<CONFIG:RelWithDebInfo>:_RELWITHDEBINFO>
)

# Define project properties
if(WIN32)
    set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
endif()