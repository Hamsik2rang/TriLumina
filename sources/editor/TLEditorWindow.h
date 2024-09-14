#ifndef __TL_EDITOR_WINDOW__
#define __TL_EDITOR__WINDOW__

#include "TLBase.h"


#include "system/TLWindow.h"
#include "engine/TLSurface.h"
#include "engine/TLEngineContext.h"

TL_NS_EDITOR_BEGIN

class TL_EDITOR_API TLEditorWindow : public Window
{
public:
    TLEditorWindow() = delete;
    TLEditorWindow(SystemContext* systemContext, const char* title, uint32 width, uint32 height);
    
    virtual ~TLEditorWindow();
    
    inline uint32 GetWidth() const { return _width; }
    inline uint32 GetHeight() const { return _height; }
    inline const char* GetTitle() const { return _title; }
    inline bool GetVSync() const { return _vSync; }
    virtual const PlatformNativeObject& GetNativeHandle() { return _nativeObjects; }
    
    // FOR TEST
//    virtual void OnAttach() override;
//    virtual void OnDetach() override;
//    virtual void OnEvent() override;
//    virtual void OnUpdate(float deltaTime) override;
    virtual void OnRender() override;
//    virtual void OnGUI() override;
    
protected:
    virtual void createSurface() override;
    
private:
    EngineContext::Surface* _surface;
    EngineContext::EngineContext* _engine;
};


TL_NS_EDITOR_END
#endif