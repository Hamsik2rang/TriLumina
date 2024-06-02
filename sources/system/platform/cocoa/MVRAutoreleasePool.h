#ifndef __MVR_AUTORELEASE_POOL__
#define __MVR_AUTORELEASE_POOL__

namespace MVR {

void* mvr_autorelease_pool_init();
void mvr_autorelease_pool_release(void* pool);

class MVRAutoreleasePool
{
public:
    MVRAutoreleasePool();
    ~MVRAutoreleasePool();
    
private:
    void* pool;
};

}

#endif
