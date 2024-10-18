#include "editor/TLEditor.h"
#include "editor/TLEditorWindow.h"
#include "graphics/TLGraphicsContext.h"


TL_NS_EDITOR_BEGIN

using namespace TL::Engine;
using namespace TL::Graphics;

Editor::Editor()
    : Engine::Application()
{

}

Editor::~Editor()
{

}

bool Editor::Init()
{
    if (nullptr == SystemContext::Create())
    {
        return false;
    }
    _system = SystemContext::Get();
#ifdef TL_PLATFORM_MACOS
    EngineContext::EngineContext::Create(TLEGraphicsInterface::METAL);
#else
    if (nullptr == EngineContext::EngineContext::Create(GraphicsInterface::VULKAN))
    {
        return false;
    }
#endif
    GraphicsContext* gContext = EngineContext::Get()->GetGraphicsContext();
    gContext->Load();
    gContext->Init();

    _windows = new EditorWindow(_system, "TriLumina", 1280, 720);
    

    return true;
}

void Editor::Run()
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

void Editor::Shutdown()
{
    delete _windows;
}

TL_NS_EDITOR_END
