#include "editor/TLEditor.h"
#include <iostream>

using namespace TL;
using namespace TL::Editor;



int main()
{
    TL_LOG_INFO("This is %s.", "info");
    TL_LOG_DEBUG("This is %s.", "debug");
    TL_LOG_TRACE("This is %s.", "trace");
    TL_LOG_WARNING("This is %s.", "warning");
    TL_LOG_ERROR("This is %s.", "error");
//    TL_LOG_CRASH("This is %s.", "crash");

    TL_CHECK(false, "this is check");

    TL_ASSERT(sizeof(int8) == 1, "Size of int8 should be %d", 1);
    TL_ASSERT(sizeof(int16) == 2, "Size of int16 should be %d", 2);
    TL_ASSERT(sizeof(int32) == 4, "Size of int32 should be %d", 4);
    TL_ASSERT(sizeof(int64) == 8, "Size of int64 should be %d", 8);
    TL_ASSERT(sizeof(uint8) == 1, "Size of uint8 should be %d", 1);
    TL_ASSERT(sizeof(uint16) == 2, "Size of uint16 should be %d", 2);
    TL_ASSERT(sizeof(uint32) == 4, "Size of uint32 should be %d", 4);
    TL_ASSERT(sizeof(uint64) == 8, "Size of uint64 should be %d", 8);
    
    TL_NEVER_HAPPEN();

#ifdef TL_PROFILE_DEBUG
    _CrtCheckMemory();
#endif

    return 0;
}
