#ifndef __TL_EDITOR__
#define __TL_EDITOR__

#include "TLBase.h"

#include "system/TLLog.h"
#include "engine/TLEngineContext.h"
#include "engine/TLApplication.h"

TL_NS_EDITOR_BEGIN


class TL_EDITOR_API Editor : public Engine::Application
{
public:
    Editor();
    virtual ~Editor();

    virtual bool Init() final;
    virtual void Run() final;
    virtual void Shutdown() final;
    
private:
    
};

TL_NS_EDITOR_END

#endif
