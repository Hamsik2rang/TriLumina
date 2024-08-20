#ifndef __TL_GRAPHICS_CONTEXT_VK__
#define __TL_GRAPHICS_CONTEXT_VK__

#include "graphics/TLGraphicsContext.h"
#if defined(TL_PLATFORM_WINDOWS)
	#define VK_USE_PLATFORM_WIN32_KHR
#endif
#include <vulkan/vulkan.h>

TL_NS_GRAPHICS_BEGIN

class TLGraphicsContextVK : public TLIGraphicsContext
{
public:
	TLGraphicsContextVK();
	~TLGraphicsContextVK();

	virtual bool Init() override;
	virtual bool Load() override;
    virtual TLISwapchain* CreateSwapchain(TLIWindow* window) override;
    virtual void Present(TLISwapchain* swapchain);
	virtual void Shutdown() override;

private:
	bool createInstance();
	bool createDevice();


	VkInstance _instance;
	VkPhysicalDevice _physicalDevice;
	VkDevice _logicalDevice;
	VkQueue _queue;

};

TL_NS_GRAPHICS_END

#endif
