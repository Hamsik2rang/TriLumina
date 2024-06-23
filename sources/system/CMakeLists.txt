set(TARGET_NAME system)

set(EVENT_HEADERS
    event/TLEvent.hpp
    event/TLKeyEvent.hpp
    event/TLMouseEvent.hpp
    event/TLApplicationEvent.hpp
)

source_group("event\\public" FILES ${EVENT_HEADERS})

IF(APPLE)
    set(PLATFORM_HEADERS
        platform/cocoa/TLWindowCocoa.h
        platform/cocoa/TLPlatformCocoa.h
        platform/cocoa/TLAutoreleasePool.h
    )
ELSEIF(MSVC)
    set(PLATFORM_HEADERS
        platform/windows/TLWindowWindows.h
        platform/windows/TLPlatformWindows.h
    )
ENDIF()

source_group("platform\\public" FILES ${PLATFORM_HEADERS})

set(COMMON_HEADERS
    TLLog.h
    TLSystemContext.h
    TLWindow.h
)

source_group("public" FILES ${COMMON_HEADERS})

set(HEADERS
    ${EVENT_HEADERS}
    ${PLATFORM_HEADERS}
    ${COMMON_HEADERS}
)

set(EVENT_SOURCES)
source_group("event\\private" FILES ${EVENT_SOURCES})

IF(APPLE)
    set(PLATFORM_SOURCES
        private/platform/cocoa/TLPlatformCocoa.mm
        private/platform/cocoa/TLAutoreleasePool.mm
    )
ELSEIF(MSVC)
    set(PLATFORM_SOURCES
        private/platform/windows/TLPlatformWindows.cpp
    )
ENDIF()

source_group("platform\\private" FILES ${PLATFORM_SOURCES})

set(COMMON_SOURCES
    private/TLLog.cpp
    private/TLSystemContext.cpp
)

source_group("private" FILES ${COMMON_SOURCES})

set(SOURCES
    ${EVENT_SOURCES}
    ${PLATFORM_SOURCES}
    ${COMMON_SOURCES}
)

add_library(${TARGET_NAME}
    STATIC
    ${HEADERS}
    ${SOURCES}
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
