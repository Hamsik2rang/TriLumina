#include "system/TLLog.h"
#include "engine/TLEngineContext.h"
#include "graphics/TLGraphicsContext.h"
#include "graphics/TLGraphicsDefinition.h"
#include <cstdio>

TL_NS_ENGINE_BEGIN

EngineContext* EngineContext::s_instance;

EngineContext* EngineContext::Create(Graphics::GraphicsInterface graphicsInterface)
{
    if (nullptr != s_instance)
    {
        TL_LOG_ERROR("EngineContext is already created!");
        return nullptr;
    }
    
    s_instance = new EngineContext(graphicsInterface);
    
    return s_instance;
}

EngineContext* EngineContext::Get()
{
    if (nullptr == s_instance)
    {
        TL_LOG_ERROR("EngineContext not yet created!");
        return nullptr;
    }
    
    return s_instance;
}

EngineContext::EngineContext(Graphics::GraphicsInterface graphicsInterface)
{
    _graphicsContext = Graphics::GraphicsContext::Create(graphicsInterface);
}



TL_NS_ENGINE_END
