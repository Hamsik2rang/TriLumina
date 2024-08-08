set(TARGET_NAME graphics)

set(COMMON_HEADERS
    TLGraphicsContext.h
    TLGraphicsDefinition.h
)

source_group("public" FILES ${COMMON_HEADERS})

set(COMMON_SOURCES
    private/TLGraphicsContext.cpp
)

source_group("private" FILES ${COMMON_SOURCES})

set(PRIVATE_VULKAN
    private/vulkan/TLGraphicsContextVK.h
    private/vulkan/TLVulkanUtility.h
)

if(NOT IOS)
    list(APPEND PRIVATE_VULKAN private/vulkan/TLGraphicsContextVK.cpp)
endif()

source_group("private\\vulkan" FILES ${PRIVATE_VULKAN})

add_library(${TARGET_NAME}
    STATIC
    ${COMMON_HEADERS}
    ${COMMON_SOURCES}
    ${PRIVATE_VULKAN}
)

target_link_libraries(${TARGET_NAME}
    PUBLIC
    system
    ${VULKAN}
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