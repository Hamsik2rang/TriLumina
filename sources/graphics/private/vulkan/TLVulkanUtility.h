#ifndef __TL_VULKAN_UTILITY__
#define __TL_VULKAN_UTILITY__

#include "TLBase.h"
#include "system/TLLog.h"

#include <vulkan/vulkan.h>
#include <string>

TL_NS_GRAPHICS_BEGIN

#ifdef TL_PROFILE_DEBUG
#define VK_CHECK_RESULT(vkFunc)                                                         \
    do                                                                                  \
    {                                                                                   \
        if (VkResult result = vkFunc; result != VK_SUCCESS)                             \
        {                                                                               \
            TL_LOG_ERROR("%s returns %s.", #vkFunc, tl_vkresult_to_string(result));     \
        }                                                                               \
    } while (0)
#else
#define VK_CHECK_RESULT(vkFunction)                                                     \
        do                                                                              \
        {                                                                               \
            vkFunction                                                                  \
        } while (0)
#endif

std::string tl_vkresult_to_string(VkResult vkResult);

TL_NS_GRAPHICS_END
#endif