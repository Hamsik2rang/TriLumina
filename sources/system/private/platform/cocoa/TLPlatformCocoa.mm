#include "system/platform/TLPlatformDefinition.h"
#include "system/TLLog.h"
#include "system/TLSystemContext.h"

#include "SDL/SDL.h"

TL_NS_BEGIN

TLPlatformNativeObject tl_platform_create_native_object(const char* title, uint32 width, uint32 height, bool vSync)
{
    TLPlatformNativeObject handle{};
    
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER))
    {
        TL_LOG_CRASH("Error: %s", SDL_GetError());
        return handle;
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
        return handle;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, vSync? SDL_RENDERER_PRESENTVSYNC : 0);
    
    handle._window = window;
    handle._renderer = renderer;
    handle._layer = SDL_RenderGetMetalLayer(renderer);
    
    return handle;
}

void tl_platform_destroy_native_object(TLPlatformNativeObject& handle)
{
    SDL_Renderer* renderer = static_cast<SDL_Renderer*>(handle._renderer);
    SDL_DestroyRenderer(renderer);
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
