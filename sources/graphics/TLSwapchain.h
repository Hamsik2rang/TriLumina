#ifndef __TL_SWAPCHAIN__
#define __TL_SWAPCHAIN__

#include "TLBase.h"
#include "system/TLWindow.h"

TL_NS_GRAPHICS_BEGIN

class TLISwapchain
{
public:
    TLISwapchain() = delete;
    TLISwapchain(TLIWindow* window) : _window{ window } {}
    virtual ~TLISwapchain() { _window = nullptr; }
    
    TLIWindow* GetWindow() { return _window; }
    
protected:
    TLIWindow* _window = nullptr;
};


TL_NS_GRAPHICS_END

#endif
