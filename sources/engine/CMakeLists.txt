set(TARGET_NAME engine)

add_compile_definitions(TL_ENGINE)

set(COMMON_HEADERS
    TLEngineContext.h
    TLApplication.h
    TLSurface.h
)

source_group("public" FILES ${COMMON_HEADERS})

set(RENDERER_HEADERS 
    renderer/TLRenderer.h
    renderer/TLForwardRenderer.h
)

source_group("renderer\\public" FILES ${RENDERER_HEADERS})

set(RENDERER_SOURCES
    private/renderer/TLRenderer.cpp
    private/renderer/TLForwardRenderer.cpp
)

source_group("renderer\\private" FILES ${RENDERER_SOURCES})

set(RENDERPASS_HEADERS
    renderer/renderpass/TLRenderPass.h
    renderer/renderpass/TLForwardRenderPass.h
)

source_group("renderer\\public\\renderpass" FILES ${RENDERPASS_HEADERS})

set(RENDERPASS_SOURCES
    private/renderer/renderpass/TLRenderPass.cpp
    private/renderer/renderpass/TLForwardRenderPass.cpp
)

source_group("renderer\\private\\renderpass" FILES ${RENDERPASS_SOURCES})


set(COMMON_SOURCES
    private/TLEngineContext.cpp
    private/TLApplication.cpp
    private/TLSurface.cpp
)

source_group("private" FILES ${COMMON_SOURCES})

add_library(${TARGET_NAME}
    SHARED
    ${COMMON_HEADERS}
    ${COMMON_SOURCES}
    ${RENDERER_HEADERS}
    ${RENDERER_SOURCES}
    ${RENDERPASS_HEADERS}
    ${RENDERPASS_SOURCES}
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