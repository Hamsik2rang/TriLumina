#include "TLBase.h"

#include "graphics/TLGraphicsContext.h"

TL_NS_GRAPHICS_BEGIN

class TLGraphicsContextMTL : public TLIGraphicsContext
{
public:
    virtual bool Load() override;
    virtual bool Init() override;
    
    virtual void Shutdown() override;
    
private:
};

TL_NS_GRAPHICS_END
