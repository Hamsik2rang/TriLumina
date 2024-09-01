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

	virtual bool Load() final;
	virtual bool Init() final;
    virtual TLISwapchain* CreateSwapchain(TLIWindow* window) final;
	virtual uint32 AcquireNextImageIndex(TLISwapchain* swapchain) final;
	virtual uint32 GetCurrentImageIndex(TLISwapchain* swapchaon) final;
    virtual void Present(TLISwapchain* swapchain) final;
	virtual void Shutdown() final;

private:
	bool createInstance();
	bool createDevice();
	void setupDebugMessenger();



	VkInstance _instance;
	VkPhysicalDevice _physicalDevice;
	VkDevice _logicalDevice;
	VkQueue _queue;

	// TODO: 별도 객체로 분리될 것.
	VkCommandPool _tempCommandPool;
	VkCommandBuffer _tempCommandBuffer[3];

};

TL_NS_GRAPHICS_END

#endif
