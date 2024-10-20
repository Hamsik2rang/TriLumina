#ifndef __TL_WINDOW__
#define __TL_WINDOW__

#include "TLBase.h"
#include "system/TLSystemContext.h"
#include "system/platform/TLPlatformDefinition.h"
#include "TLLog.h"

TL_NS_BEGIN

class Window
{
public:
    
    Window() = delete;
    Window(SystemContext* systemContext, const char* title, uint32 width, uint32 height);
    
    virtual ~Window();
    
    inline uint32 GetWidth() const { return _width; }
    inline uint32 GetHeight() const { return _height; }
    inline const char* GetTitle() const { return _title; }
    inline bool GetVSync() const { return _vSync; }
    virtual const PlatformNativeObject& GetNativeHandle() { return _nativeObjects; }
    
    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnEvent() {}
    virtual void OnUpdate(float deltaTime) {}
    virtual void OnRender() {}
    virtual void OnGUI() {}
    
protected:
    virtual void createSurface() = 0;
    
    SystemContext* _systemContext = nullptr;
    
    const char* _title;
    uint32 _width;
    uint32 _height;
    // TODO: 추후 세팅 방법 정의
    bool _vSync = true;
    PlatformNativeObject _nativeObjects;
    
};


TL_NS_END

#endif
