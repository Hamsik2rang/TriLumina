#ifndef __TL_GRAPHICS_CONTEXT__
#define __TL_GRAPHICS_CONTEXT__

#include "TLBase.h"

#include "system/TLWindow.h"

#include "graphics/TLGraphicsDefinition.h"
#include "graphics/TLSwapchain.h"


TL_NS_GRAPHICS_BEGIN

class TLIGraphicsContext
{
public:
	TLIGraphicsContext() = default;
	virtual ~TLIGraphicsContext() = default;

	virtual bool Init() = 0;
	virtual bool Load() = 0;
    virtual TLISwapchain* CreateSwapchain(TLIWindow* window) = 0;
	virtual uint32 AcquireNextImageIndex(TLISwapchain* swapchain) = 0;
	virtual uint32 GetCurrentImageIndex(TLISwapchain* swapchain) = 0;
    virtual void Present(TLISwapchain* swapchain) = 0;
	virtual void Shutdown() = 0;

    static TLIGraphicsContext* Create(TLEGraphicsInterface interface);
};


TL_NS_GRAPHICS_END

#endif
