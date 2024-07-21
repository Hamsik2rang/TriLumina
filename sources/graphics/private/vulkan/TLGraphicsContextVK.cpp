#include "graphics/private/vulkan/TLGraphicsContextVK.h"
#include "graphics/private/vulkan/TLVulkanUtility.h"

#include <vector>

TL_NS_GRAPHICS_BEGIN

TLGraphicsContextVK::TLGraphicsContextVK()
{

}

TLGraphicsContextVK::~TLGraphicsContextVK()
{
	Shutdown();
}

bool TLGraphicsContextVK::Init()
{
	return false;
}

bool TLGraphicsContextVK::Load()
{
	return false;
}

bool TLGraphicsContextVK::initInstance()
{
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pNext = nullptr;
	appInfo.pApplicationName = "TriLumina";
	appInfo.applicationVersion = VK_MAKE_API_VERSION(0, 0, 1, 0);
	appInfo.pEngineName = "TriLumina";
	appInfo.engineVersion = VK_MAKE_API_VERSION(0, 0, 1, 0);
	appInfo.apiVersion = VK_MAKE_API_VERSION(0, 1, 3, 0);

	uint32 layerCount;
	VK_CHECK_ERROR(vkEnumerateInstanceLayerProperties(&layerCount, nullptr));

	std::vector<VkLayerProperties> layerProps(layerCount);
	VK_CHECK_ERROR(vkEnumerateInstanceLayerProperties(&layerCount, layerProps.data()));

	std::vector<const char*> enabledLayerNames;
	for (int i = 0; i < layerCount; i++)
	{
		enabledLayerNames.push_back(layerProps[i].layerName);
	}

	uint32 extensionCount;
	VK_CHECK_ERROR(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr));
	
	std::vector<VkExtensionProperties> extensionProps(extensionCount);
	VK_CHECK_ERROR(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionProps.data()));

	std::vector<const char*> supportedExtensionNames;
	for (int i = 0; i < extensionCount; i++)
	{
		supportedExtensionNames.push_back(extensionProps[i].extensionName);
	}
	
	std::vector<const char*> enabledExtensionNames;
	for (const char* extension : supportedExtensionNames)
	{
		if (std::string("VK_KHR_Surface") == std::string(extension) ||
			std::string("VK_KHR_win32_surface") == std::string(extension))
		{
			enabledExtensionNames.push_back(extension);
		}
	}


	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledLayerCount = layerCount;
	createInfo.ppEnabledLayerNames = enabledLayerNames.data();
	createInfo.enabledExtensionCount = extensionCount;
	createInfo.ppEnabledExtensionNames = enabledExtensionNames.data();

	VK_CHECK_ERROR(vkCreateInstance(&createInfo, nullptr, &_instance));


	return true;
}

bool TLGraphicsContextVK::Load()
{
	return true;
}

void TLGraphicsContextVK::Shutdown()
{
	//Not implemented;
}

TL_NS_GRAPHICS_END