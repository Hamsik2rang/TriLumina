#include "editor/TLEditor.h"
#include "graphics/private/vulkan/TLGraphicsContextVK.h"
#include "system/TLWindow.h"

using namespace TL;
using namespace TL::Graphics;

TL_NS_EDITOR_BEGIN

void TLEditor::Print(const char* msg)
{
	
}

void TLEditor::Run()
{
	TLIWindow* window = new TLIWindow("Test Window", 1280, 720);
	
	delete window;
}


TL_NS_EDITOR_END
