#include "system/platform/TLPlatformDefinition.h"
#include "system/TLLog.h"
#include "system/TLSystemContext.h"

#include "SDL/SDL.h"
#include "SDL/SDL_vulkan.h"

#include <vector>

TL_NS_BEGIN

PlatformNativeObject tl_platform_create_native_object(const char* title, uint32 width, uint32 height, bool vSync)
{
    PlatformNativeObject handle{};

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER))
    {
        TL_LOG_CRASH("Error: %s", SDL_GetError());
        return {};
    }

    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
    // TODO: Windows에서 DX Graphics Interface도 고려해야 함.
    SDL_WindowFlags windowFlags = (SDL_WindowFlags)(SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)width, (int)height, windowFlags);
    if (nullptr == window)
    {
        TL_LOG_CRASH("Error Creating SDLWindow: %s", SDL_GetError());
        return {};
    }

    handle._window = window;
    // Windows의 경우 renderer, layer가 필요하지 않음.
    handle._renderer = nullptr;
    handle._layer = nullptr;

    return handle;
}

void tl_platform_destroy_native_object(PlatformNativeObject& handle)
{
    SDL_Window* window = static_cast<SDL_Window*>(handle._window);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void tl_platform_poll_events()
{
    SystemContext* systemContext = SystemContext::Get();

    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        switch (e.type)
        {
        case SDL_QUIT: systemContext->shouldQuit = true; break;
        }
    }
}

void tl_platform_get_window_size(const PlatformNativeObject& handle, uint32& width, uint32& height)
{
    int w, h;
    SDL_GetWindowSize(static_cast<SDL_Window*>(handle._window), &w, &h);

    width = w;
    height = h;
}

void tl_platform_set_window_size(const PlatformNativeObject& handle, uint32 width, uint32 height)
{
    SDL_SetWindowSize(static_cast<SDL_Window*>(handle._window), static_cast<int>(width), static_cast<int>(height));
}

bool tl_platform_create_surface_vulkan(const PlatformNativeObject& handle, VkInstance instanceVK, VkSurfaceKHR* surfaceVK)
{
    return static_cast<bool>(SDL_Vulkan_CreateSurface(static_cast<SDL_Window*>(handle._window), instanceVK, surfaceVK));
}


TL_NS_END

