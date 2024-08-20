#include "editor/TLEditor.h"
#include "editor/TLEditorWindow.h"
#include "graphics/TLGraphicsContext.h"


TL_NS_EDITOR_BEGIN

using namespace TL::Engine;
using namespace TL::Graphics;

TLEditor::TLEditor()
    : Engine::TLIApplication()
{

}

TLEditor::~TLEditor()
{

}

bool TLEditor::Init()
{
    if (nullptr == TLSystemContext::Create())
    {
        return false;
    }
    _system = TLSystemContext::Get();
#ifdef TL_PLATFORM_MACOS
    Engine::TLEngine::Create(TLEGraphicsInterface::METAL);
#else
    if (nullptr == Engine::TLEngine::Create(TLEGraphicsInterface::VULKAN))
    {
        return false;
    }
#endif
    TLIGraphicsContext* gContext = TLEngine::Get()->GetGraphicsContext();
    gContext->Load();
    gContext->Init();

    _windows = new TLEditorWindow(_system, "TriLumina", 1280, 720);
    

    return true;
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
