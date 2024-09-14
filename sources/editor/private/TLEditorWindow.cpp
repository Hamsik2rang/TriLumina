#include "engine/TLEngineContext.h"
#include "editor/TLEditorWindow.h"
#include "graphics/TLGraphicsContext.h"

TL_NS_EDITOR_BEGIN

TLEditorWindow::TLEditorWindow(SystemContext* systemContext, const char* title, uint32 width, uint32 height)
	: Window(systemContext, title, width, height)
	, _surface{ nullptr }
	, _engine{ nullptr }

{
	_engine = EngineContext::EngineContext::Get();
	createSurface();

	_surface->SetSwapchain(_engine->GetGraphicsContext()->CreateSwapchain(this));
}

TLEditorWindow::~TLEditorWindow()
{
	delete _surface;
}

void TLEditorWindow::createSurface()
{
	_surface = new EngineContext::Surface();
}

void TLEditorWindow::OnRender()
{
	_engine->GetGraphicsContext()->Present(_surface->GetSwapchain());
}


TL_NS_EDITOR_END
