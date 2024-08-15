#include "system/TLLog.h"
#include "engine/TLEngine.h"
#include "graphics/TLGraphicsContext.h"
#include "graphics/TLGraphicsDefinition.h"
#include <cstdio>

TL_NS_ENGINE_BEGIN

TLEngine* TLEngine::s_instance;

TLEngine* TLEngine::Create(Graphics::TLEGraphicsInterface graphicsInterface)
{
    if (nullptr != s_instance)
    {
        TL_LOG_ERROR("TLEngine is already created!");
        return nullptr;
    }
    
    s_instance = new TLEngine(graphicsInterface);
    
    return s_instance;
}

TLEngine* TLEngine::Get()
{
    if (nullptr == s_instance)
    {
        TL_LOG_ERROR("TLEngine not yet created!");
        return nullptr;
    }
    
    return s_instance;
}

TLEngine::TLEngine(Graphics::TLEGraphicsInterface graphicsInterface)
{
    _graphicsContext = Graphics::TLIGraphicsContext::Create(graphicsInterface);
}



TL_NS_ENGINE_END
