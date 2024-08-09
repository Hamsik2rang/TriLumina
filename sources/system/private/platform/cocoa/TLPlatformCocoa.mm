#include "system/platform/TLPlatformDefinition.h"
#include "system/TLLog.h"

#include "SDL/SDL.h"

TL_NS_BEGIN

void* tl_platform_window_create(const char* title, uint32 width, uint32 height)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER))
    {
        TL_LOG_CRASH("Error: %s", SDL_GetError());
        return nullptr;
    }
    
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "metal");
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
    
    SDL_Window* window = SDL_CreateWindow(title,
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          width,
                                          height,
                                          SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
                                          );
    if (nullptr == window)
    {
        TL_LOG_CRASH("Error Creating SDLWindow: %s", SDL_GetError());
        return nullptr;
    }
    
    return window;
}

void tl_platform_window_destroy(void* handle)
{
    SDL_Window* window = static_cast<SDL_Window*>(handle);
    SDL_DestroyWindow(window);
}

TL_NS_END
