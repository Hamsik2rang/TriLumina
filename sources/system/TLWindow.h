#ifndef __TL_WINDOW__
#define __TL_WINDOW__

#include "TLBase.h"
#include "SDL/SDL.h"
#include "TLLog.h"

TL_NS_BEGIN

class TLIWindow
{
public:
    TLIWindow() = default;

    void Init()
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
        {
            TL_LOG_ERROR("Error: %s\n", SDL_GetError());
            return;
        }
    }
    
    inline const uint32 GetWidth() const { return _width; }
    inline const uint32 GetHeight() const { return _height; }
    inline const char* GetTitle() const { return _title; }
    inline void* GetHandle() { return _handle; }

    static TLIWindow* Create();
private:
    const char* _title;
    uint32 _width;
    uint32 _height;
    void* _handle;
};


TL_NS_END


#endif
