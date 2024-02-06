#include "editor/MVREditor.h"
#include <iostream>

using namespace MVR;
using namespace MVR::Editor;



int main()
{
    MVR_LOG_INFO("This is %s.", "info");
    MVR_LOG_DEBUG("This is %s.", "debug");
    MVR_LOG_TRACE("This is %s.", "trace");
    MVR_LOG_WARNING("This is %s.", "warning");
    MVR_LOG_ERROR("This is %s.", "error");
    //MVR_LOG_CRASH("This is %s.", "crash");

    MVR_CHECK(false, "this is check");

    MVR_ASSERT(sizeof(int8) == 1, "Size of int8 should be %d", 1);
    MVR_ASSERT(sizeof(int16) == 2, "Size of int16 should be %d", 2);
    MVR_ASSERT(sizeof(int32) == 4, "Size of int32 should be %d", 4);
    MVR_ASSERT(sizeof(int64) == 8, "Size of int64 should be %d", 8);
    MVR_ASSERT(sizeof(uint8) == 1, "Size of uint8 should be %d", 1);
    MVR_ASSERT(sizeof(uint16) == 2, "Size of uint16 should be %d", 2);
    MVR_ASSERT(sizeof(uint32) == 4, "Size of uint32 should be %d", 4);
    MVR_ASSERT(sizeof(uint64) == 8, "Size of uint64 should be %d", 8);
    
    MVR_NEVER_HAPPEN();

    return 0;
}