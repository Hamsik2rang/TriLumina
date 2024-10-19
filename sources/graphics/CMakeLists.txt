set(TARGET_NAME graphics)

set(COMMON_HEADERS
    TLGraphicsContext.h
    TLGraphicsDefinition.h
    TLSwapchain.h
)

source_group("public" FILES ${COMMON_HEADERS})

set(COMMON_SOURCES
    private/TLGraphicsContext.cpp
)

source_group("private" FILES ${COMMON_SOURCES})
set(PRIVATE_VULKAN
    private/vulkan/TLGraphicsContextVK.h
    private/vulkan/TLVulkanUtility.h
    private/vulkan/TLGraphicsDefinitionVK.h
    private/vulkan/TLSwapchainVK.h
)

if(WIN32)
    list(APPEND PRIVATE_VULKAN
        private/vulkan/TLGraphicsContextVK.cpp
        private/vulkan/TLVulkanUtility.cpp
        private/vulkan/TLSwapchainVK.cpp
    )
endif()

source_group("private\\vulkan" FILES ${PRIVATE_VULKAN})

set(PRIVATE_METAL)

# Vulkan의 경우 Mac에서도 헤더 인클루드가 가능하지만, Metal은 그 반대가 불가능하므로 아래처럼 작성합니다.
if(APPLE)
    list(APPEND PRIVATE_METAL
        private/metal/TLGraphicsContextMTL.h
        private/metal/TLGraphicsContextMTL.mm
        private/metal/TLMetalUtility.h
        private/metal/TLMetalUtility.mm
        private/metal/TLGraphicsDefinitionMTL.h
        private/metal/TLSwapchainMTL.h
        private/metal/TLSwapchainMTL.mm
    )

    source_group("private\\metal" FILES ${PRIVATE_METAL})
endif()

add_library(${TARGET_NAME}
    STATIC
    ${COMMON_HEADERS}
    ${COMMON_SOURCES}
    ${PRIVATE_VULKAN}
    ${PRIVATE_METAL}
)

target_link_libraries(${TARGET_NAME}
    PUBLIC
    system
    ${VULKAN}

    # "-framework OpenGL -framework Foundation -framework CoreFoundation -framework QuartzCore -framework AppKit -framework IOKit -framework Metal -framework GameController"
)

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