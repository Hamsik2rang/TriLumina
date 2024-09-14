#ifndef __TL_GRAPHICS_CONTEXT_MTL__
#define __TL_GRAPHICS_CONTEXT_MTL__

#include "TLBase.h"

#include "graphics/TLGraphicsContext.h"


TL_NS_GRAPHICS_BEGIN

class GraphicsContextMTL : public GraphicsContext
{
public:
    virtual bool Load() override;
    virtual bool Init() override;
    virtual Swapchain* CreateSwapchain(Window* window) override;
    virtual void Present(Swapchain* swapchain) override;
    virtual void Shutdown() override;
    
private:
    void* _device;
    
};

TL_NS_GRAPHICS_END

#endif
