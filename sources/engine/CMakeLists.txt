set(TARGET_NAME engine)

add_compile_definitions(TL_ENGINE)

set(COMMON_HEADERS
    TLEngine.h
    TLApplication.h
    TLSurface.h
)

source_group("public" FILES ${COMMON_HEADERS})

set(COMMON_SOURCES
    private/TLEngine.cpp
    private/TLApplication.cpp
    private/TLSurface.cpp
)

source_group("private" FILES ${COMMON_SOURCES})

add_library(${TARGET_NAME}
    SHARED
    ${COMMON_HEADERS}
    ${COMMON_SOURCES}
)

# TARGET_LINK_LIBRARIES(engine PRIVATE "-Wl,-all_load" system render "-Wl,-force_load" ${VULKAN} ${OPENSSL} "-framework OpenGL -framework Foundation -framework CoreFoundation -framework QuartzCore -framework AppKit -framework IOKit  -framework Metal -framework CoreAudio -framework AudioToolbox -framework AVFoundation")
if(APPLE)
    target_link_libraries(${TARGET_NAME}
        PUBLIC
        graphics
        PRIVATE
        ${VULKAN} "-framework OpenGL -framework Foundation -framework CoreFoundation -framework QuartzCore -framework AppKit -framework IOKit  -framework Metal -framework GameController -framework CoreAudio -framework AudioToolbox -framework AVFoundation"
    )
else()
    target_link_libraries(${TARGET_NAME}
        PUBLIC
        graphics
        "-Wl"
        ${VULKAN}
    )
endif()

target_compile_definitions(${TARGET_NAME} PUBLIC
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:MinSizeRel>:_RELEASE>
    $<$<CONFIG:Release>:_RELEASE>
    $<$<CONFIG:RelWithDebInfo>:_RELWITHDEBINFO>
    TL_ENGINE
)

# Define project properties
if(WIN32)
    set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
endif()