#ifndef __TL_EDITOR__
#define __TL_EDITOR__

#include "TLBase.h"

#include "system/TLLog.h"
#include "engine/TLEngine.h"
#include "engine/TLApplication.h"

TL_NS_EDITOR_BEGIN

class TL_EDITOR_API TLEditor : public Engine::TLIApplication
{
public:
    virtual bool Init() override;
    virtual void Run() override;
    virtual void Shutdown() override;
    
private:
    
};

TL_NS_EDITOR_END

#endif
