#ifndef __TL_ENGINE__
#define __TL_ENGINE__

#include "TLBase.h"
#include "graphics/TLGraphicsDefinition.h"

namespace TL { namespace Graphics { class TLIGraphicsContext; } }

TL_NS_ENGINE_BEGIN

class TL_API TLEngine
{
public:
    ~TLEngine();
    
    inline Graphics::TLIGraphicsContext* GetGraphicsContext() { return _graphicsContext; }
    
    static TLEngine* Create(Graphics::TLEGraphicsInterface graphicsInterface);
    static TLEngine* Get();
    
private:
    TLEngine(Graphics::TLEGraphicsInterface graphicsInterface);

    static TLEngine* s_instance;
    
    Graphics::TLIGraphicsContext* _graphicsContext;
};

TL_NS_ENGINE_END
#endif

