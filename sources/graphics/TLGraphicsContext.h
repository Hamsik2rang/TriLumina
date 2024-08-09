#ifndef __TL_GRAPHICS_CONTEXT__
#define __TL_GRAPHICS_CONTEXT__

#include "TLBase.h"
#include "graphics/TLGraphicsDefinition.h"

TL_NS_GRAPHICS_BEGIN

class TLIGraphicsContext
{
public:
	TLIGraphicsContext() = default;
	virtual ~TLIGraphicsContext() = default;

	virtual bool Init() = 0;
	virtual bool Load() = 0;

	virtual void Shutdown() = 0;

    TLIGraphicsContext* Create(TLEGraphicsInterface interface);
};


TL_NS_GRAPHICS_END

#endif
