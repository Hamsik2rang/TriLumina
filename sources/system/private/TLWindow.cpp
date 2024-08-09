#include "system/TLWindow.h"
#include "system/platform/TLPlatformDefinition.h"


TL_NS_BEGIN


TLIWindow::TLIWindow(const char* title, uint32 width, uint32 height)
: _title { title }
, _width { width }
, _height{ height }
, _handle{ nullptr }
{
    _handle = tl_platform_window_create(title, width, height);
}

TLIWindow::~TLIWindow()
{
    tl_platform_window_destroy(_handle);
}


TL_NS_END
