#ifndef __TL_PLATFORM_DEFINITION__
#define __TL_PLATFORM_DEFINITION__

#include "TLBase.h"


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

TL_NS_END

#endif
