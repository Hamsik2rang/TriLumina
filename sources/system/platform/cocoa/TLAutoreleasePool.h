#ifndef __TL_AUTORELEASE_POOL__
#define __TL_AUTORELEASE_POOL__

namespace TL {

void* TL_autorelease_pool_init();
void TL_autorelease_pool_release(void* pool);

class TLAutoreleasePool
{
public:
    TLAutoreleasePool();
    ~TLAutoreleasePool();
    
private:
    void* pool;
};

}

#endif
