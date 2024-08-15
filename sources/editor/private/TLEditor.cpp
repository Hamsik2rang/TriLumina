#include "editor/TLEditor.h"
#include "editor/TLEditorWindow.h"
#include "graphics/TLGraphicsContext.h"

using namespace TL;
using namespace TL::Graphics;

TL_NS_EDITOR_BEGIN

bool TLEditor::Init()
{
    TLSystemContext* systemContext = TLSystemContext::Create();
    _system = systemContext;
#ifdef TL_PLATFORM_MACOS
    Engine::TLEngine::Create(TLEGraphicsInterface::METAL);
#else
    Engine::TLEngine::Create(TLEGraphicsInterface::VULKAN);
#endif
    
    _windows = new TLEditorWindow(_system, "TriLumina", 1280, 720);
}

void TLEditor::Run()
{
    while (false == _system->shouldQuit)
    {
        _system->PollEvents();
        
        for (int i = 0; i < 1; i++)
        {
            _windows->OnEvent();
            
            _windows->OnUpdate(_deltaTime);
            
            _windows->OnRender();
        }
    }
}

void TLEditor::Shutdown()
{
    delete _windows;
}

TL_NS_EDITOR_END
