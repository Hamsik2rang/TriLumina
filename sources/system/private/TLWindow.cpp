#include "system/TLWindow.h"
#include "system/platform/TLPlatformDefinition.h"


TL_NS_BEGIN


Window::Window(SystemContext* systemContext, const char* title, uint32 width, uint32 height)
: _systemContext{ systemContext }
, _title{ title }
, _width{ width }
, _height{ height }
{
    _nativeObjects = tl_platform_create_native_object(_title, _width, _height, _vSync);
}
            
Window::~Window()
{
    tl_platform_destroy_native_object(_nativeObjects);
}


TL_NS_END
