#ifndef __TL_EDITOR__
#define __TL_EDITOR__

#include "TLBase.h"

#include "engine/TLEngine.h"
#include "engine/TLApplication.h"
#include "system/TLLog.h"

TL_NS_EDITOR_BEGIN

class TL_EDITOR_API TLEditor : public TLIApplication
{
public:
    virtual bool Init() override;
    virtual void Run() override;
    virtual void Shutdown() override;
    
private:
	Engine::TLEngine* _engine;
    
};

TL_NS_EDITOR_END

#endif
