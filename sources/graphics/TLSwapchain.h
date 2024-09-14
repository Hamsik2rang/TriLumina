#ifndef __TL_SWAPCHAIN__
#define __TL_SWAPCHAIN__

#include "TLBase.h"
#include "system/TLWindow.h"

TL_NS_GRAPHICS_BEGIN

class Swapchain
{
public:
    Swapchain() = delete;
    Swapchain(Window* window) : _window{ window } {}
    virtual ~Swapchain() { _window = nullptr; }
    
    Window* GetWindow() { return _window; }
    
protected:
    Window* _window = nullptr;
};


TL_NS_GRAPHICS_END

#endif
