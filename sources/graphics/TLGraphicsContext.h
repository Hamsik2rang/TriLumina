#ifndef __TL_GRAPHICS_CONTEXT__
#define __TL_GRAPHICS_CONTEXT__

#include "TLBase.h"

#include "system/TLWindow.h"

#include "graphics/TLGraphicsDefinition.h"
#include "graphics/TLSwapchain.h"

#if defined(TL_PLATFORM_MACOS)
#include "graphics/private/metal/TLGraphicsContextMTL.h"
#else
#include "graphics/private/vulkan/TLGraphicsContextVK.h"
#endif

TL_NS_GRAPHICS_BEGIN

#if defined(TL_PLATFORM_MACOS)
class GraphicsContext : public GraphicsContextMTL
#else
class GraphicsContext : public GraphicsContextVK
#endif
{
public:
	GraphicsContext() = default;
    ~GraphicsContext() = default;

	bool Init();
	bool Load();
    Swapchain* CreateSwapchain(Window* window);
	uint32 AcquireNextImageIndex(Swapchain* swapchain);
	uint32 GetCurrentImageIndex(Swapchain* swapchain);
    void Present(Swapchain* swapchain);
	void Shutdown();
};


TL_NS_GRAPHICS_END

#endif
