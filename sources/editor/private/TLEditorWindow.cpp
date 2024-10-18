#include "engine/TLEngineContext.h"
#include "editor/TLEditorWindow.h"
#include "graphics/TLGraphicsContext.h"

TL_NS_EDITOR_BEGIN

EditorWindow::EditorWindow(SystemContext* systemContext, const char* title, uint32 width, uint32 height)
	: Window(systemContext, title, width, height)
	, _surface{ nullptr }
	, _engine{ nullptr }

{
	_engine = Engine::EngineContext::Get();
	createSurface();

	_surface->SetSwapchain(_engine->GetGraphicsContext()->CreateSwapchain(this));
}

EditorWindow::~EditorWindow()
{
	delete _surface;
}

void EditorWindow::createSurface()
{
	_surface = new Engine::Surface();
}

void EditorWindow::OnRender()
{
	_engine->GetGraphicsContext()->Present(_surface->GetSwapchain());
}


TL_NS_EDITOR_END
