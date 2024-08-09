#include "TLBase.h"

TL_NS_ENGINE_BEGIN

class TL_API TLIApplication
{
public:
    virtual bool Init() = 0;
    virtual void Run() = 0;
    virtual void Shutdown() = 0;
    
private:
    // TLList<TLIWindow> _windows;
};

TL_NS_ENGINE_END
