#ifndef __TL_WINDOW__
#define __TL_WINDOW__

#include "TLBase.h"
#include "SDL/SDL.h"
#include "TLLog.h"

TL_NS_BEGIN

class TLIWindow
{
public:
    TLIWindow() = delete;
    TLIWindow(const char* title, uint32 width, uint32 height);
    
    virtual ~TLIWindow();
    
    inline const uint32 GetWidth() const { return _width; }
    inline const uint32 GetHeight() const { return _height; }
    inline const char* GetTitle() const { return _title; }
    virtual void* GetHandle() { return _handle; }
    
    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnEvent() {}
    virtual void OnUpdate(float deltaTime) {}
    virtual void OnRender() {}
    virtual void OnGUI() {}
    
private:
    const char* _title;
    uint32 _width;
    uint32 _height;
    
    void* _handle;
};


TL_NS_END


#endif
