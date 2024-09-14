#ifndef __TL_EDITOR__
#define __TL_EDITOR__

#include "TLBase.h"

#include "system/TLLog.h"
#include "engine/TLEngineContext.h"
#include "engine/TLApplication.h"

TL_NS_EDITOR_BEGIN

class TL_API TL::EngineContext::Application;

class TL_EDITOR_API TLEditor : public EngineContext::Application
{
public:
    TLEditor();
    virtual ~TLEditor();

    virtual bool Init() final;
    virtual void Run() final;
    virtual void Shutdown() final;
    
private:
    
};

TL_NS_EDITOR_END

#endif
