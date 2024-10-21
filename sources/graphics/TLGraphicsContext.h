#ifndef __TL_GRAPHICS_CONTEXT__
#define __TL_GRAPHICS_CONTEXT__

#include "TLBase.h"

#include "system/TLWindow.h"

#include "graphics/TLGraphicsDefinition.h"
#include "graphics/TLSwapchain.h"


TL_NS_GRAPHICS_BEGIN

class GraphicsContext
{
public:
	GraphicsContext() = default;
	virtual ~GraphicsContext() = default;

	virtual bool Init() = 0;
	virtual bool Load() = 0;
    virtual Swapchain* CreateSwapchain(Window* window) = 0;
	virtual uint32 AcquireNextImageIndex(Swapchain* swapchain) = 0;
	virtual uint32 GetCurrentImageIndex(Swapchain* swapchain) = 0;
    virtual void Present(Swapchain* swapchain) = 0;
	virtual void Shutdown() = 0;

    static GraphicsContext* Create(GraphicsInterface interface);
};


TL_NS_GRAPHICS_END

#endif
