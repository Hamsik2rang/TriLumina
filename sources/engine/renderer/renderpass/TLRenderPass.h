#ifndef __TL_RENDERPASS__
#define __TL_RENDERPASS__

#include "graphics/TLGraphicsContext.h"

TL_NS_ENGINE_BEGIN

class Renderer
{
public:
	Renderer(Graphics::GraphicsContext* graphicsContext);
	virtual ~Renderer();

	virtual void Render();

protected:
	Graphics::GraphicsContext* _graphicsContext;
};

TL_NS_ENGINE_END

#endif