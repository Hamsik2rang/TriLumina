#ifndef __TL_ENGINE__
#define __TL_ENGINE__

#include "TLBase.h"
#include "graphics/TLGraphicsDefinition.h"

namespace TL { namespace Graphics { class GraphicsContext; } }

TL_NS_ENGINE_BEGIN

class TL_API EngineContext
{
public:
    ~EngineContext();
    
    inline Graphics::GraphicsContext* GetGraphicsContext() { return _graphicsContext; }
    
    static EngineContext* Create(Graphics::GraphicsInterface graphicsInterface);
    static EngineContext* Get();
    
private:
    EngineContext(Graphics::GraphicsInterface graphicsInterface);

    static EngineContext* s_instance;
    
    Graphics::GraphicsContext* _graphicsContext;
};

TL_NS_ENGINE_END
#endif

