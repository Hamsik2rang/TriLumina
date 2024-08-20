#ifndef __TL_PLATFORM_DEFINITION__
#define __TL_PLATFORM_DEFINITION__

#include "TLBase.h"

#include <vector>
#include <vulkan/vulkan.h>

TL_NS_BEGIN

struct TLPlatformNativeObject
{
    void* _window;
    void* _renderer;
    void* _layer;
};

TLPlatformNativeObject tl_platform_create_native_object(const char* title, uint32 width, uint32 height, bool vSync);
void tl_platform_destroy_native_object(TLPlatformNativeObject& handle);
void tl_platform_poll_events();

void tl_platform_get_window_size(const TLPlatformNativeObject& handle, uint32& width, uint32& height);
void tl_platform_set_window_size(const TLPlatformNativeObject& handle, uint32 width, uint32 height);

bool tl_platform_create_surface_vulkan(const TLPlatformNativeObject& handle, VkInstance instanceVK, VkSurfaceKHR* surfaceVK);

TL_NS_END

#endif
