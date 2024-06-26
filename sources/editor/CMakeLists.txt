set(TARGET_NAME editor)

add_compile_definitions(TL_EDITOR)

set(COMMON_HEADERS
    TLEditor.h
    TLImGuiContext.h
)

source_group("public" FILES ${COMMON_HEADERS})

set(COMMON_SOURCES
    private/TLEditor.cpp
    private/TLImGuiContext.cpp
)

source_group("private" FILES ${COMMON_SOURCES})

list(APPEND IMGUI
    thirdparty/ImGui/imconfig.h
    thirdparty/ImGui/imgui_internal.h
    thirdparty/ImGui/imgui.h
    thirdparty/ImGui/imstb_rectpack.h
    thirdparty/ImGui/imstb_textedit.h
    thirdparty/ImGui/imstb_truetype.h
    thirdparty/ImGui/imgui.cpp
    thirdparty/ImGui/imgui_demo.cpp
    thirdparty/ImGui/imgui_draw.cpp
    thirdparty/ImGui/imgui_tables.cpp
    thirdparty/ImGui/imgui_widgets.cpp
)

source_group("thirdparty\\ImGui" FILES ${IMGUI})

if(APPLE)
    list(APPEND IMGUI_BACKENDS
        thirdparty/ImGui/backends/imgui_impl_osx.h
        thirdparty/ImGui/backends/imgui_impl_osx.mm
        thirdparty/ImGui/backends/imgui_impl_metal.h
        thirdparty/ImGui/backends/imgui_impl_metal.mm
    )
else()
    # TODO: 추후 그래픽스 API 지원에 맞게 추가할 것.
    list(APPEND IMGUI_BACKENDS
        thirdparty/ImGui/backends/imgui_impl_win32.h
        thirdparty/ImGui/backends/imgui_impl_win32.cpp
        thirdparty/ImGui/backends/imgui_impl_vulkan.h
        thirdparty/ImGui/backends/imgui_impl_vulkan.cpp
    )
endif()

source_group("thirdparty\\ImGui\\backends" FILES ${IMGUI_BACKENDS})

set(THIRDPARTY
    ${IMGUI}
    ${IMGUI_BACKENDS}
)

add_library(${TARGET_NAME}
    SHARED
    ${COMMON_HEADERS}
    ${COMMON_SOURCES}
    ${THIRDPARTY}
)

target_link_libraries(${TARGET_NAME}
    PRIVATE
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