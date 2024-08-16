#include "system/platform/TLPlatformDefinition.h"
#include "system/TLLog.h"
#include "system/TLSystemContext.h"

#include "SDL/SDL.h"

#include <vector>

TL_NS_BEGIN

TLPlatformNativeObject tl_platform_create_native_object(const char* title, uint32 width, uint32 height, bool vSync)
{
    TLPlatformNativeObject handle{};

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

void tl_platform_destroy_native_object(TLPlatformNativeObject& handle)
{
    SDL_Window* window = static_cast<SDL_Window*>(handle._window);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void tl_platform_poll_events()
{
    TLSystemContext* systemContext = TLSystemContext::Get();

    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        switch (e.type)
        {
        case SDL_QUIT: systemContext->shouldQuit = true; break;
        }
    }
}


TL_NS_END

