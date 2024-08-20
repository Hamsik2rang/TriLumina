#include "engine/TLEngine.h"
#include "editor/TLEditorWindow.h"
#include "graphics/TLGraphicsContext.h"

TL_NS_EDITOR_BEGIN

TLEditorWindow::TLEditorWindow(TLSystemContext* systemContext, const char* title, uint32 width, uint32 height)
	: TLIWindow(systemContext, title, width, height)
	, _surface{ nullptr }
	, _engine{ nullptr }

{
	_engine = Engine::TLEngine::Get();
	createSurface();

	_surface->SetSwapchain(_engine->GetGraphicsContext()->CreateSwapchain(this));
}

TLEditorWindow::~TLEditorWindow()
{
	delete _surface;
}

void TLEditorWindow::createSurface()
{
	_surface = new Engine::TLSurface();
}

void TLEditorWindow::OnRender()
{
	_engine->GetGraphicsContext()->Present(_surface->GetSwapchain());
}


TL_NS_EDITOR_END
