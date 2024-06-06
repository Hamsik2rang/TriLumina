#include "system/platform/cocoa/TLAutoreleasePool.h"

#import <Foundation/Foundation.h>

namespace TL {

void* TL_autorelease_pool_init()
{
    NSAutoreleasePool* p = [[NSAutoreleasePool alloc] init];
    return (__bridge void*)p;
}
void TL_autorelease_pool_release(void* pool)
{
    NSAutoreleasePool* p = (__bridge NSAutoreleasePool*)pool;
    [p release];
}

TLAutoreleasePool::TLAutoreleasePool()
{
    pool = TL_autorelease_pool_init();
}

TLAutoreleasePool::~TLAutoreleasePool()
{
    TL_autorelease_pool_release(pool);
}

}
