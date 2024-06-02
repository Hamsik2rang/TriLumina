#include "system/platform/cocoa/MVRAutoreleasePool.h"

#import <Foundation/Foundation.h>

namespace MVR {

void* mvr_autorelease_pool_init()
{
    NSAutoreleasePool* p = [[NSAutoreleasePool alloc] init];
    return (__bridge void*)p;
}
void mvr_autorelease_pool_release(void* pool)
{
    NSAutoreleasePool* p = (__bridge NSAutoreleasePool*)pool;
    [p release];
}

MVRAutoreleasePool::MVRAutoreleasePool()
{
    pool = mvr_autorelease_pool_init();
}

MVRAutoreleasePool::~MVRAutoreleasePool()
{
    mvr_autorelease_pool_release(pool);
}

}
