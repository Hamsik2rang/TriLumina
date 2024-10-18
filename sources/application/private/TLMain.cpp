#include "editor/TLEditor.h"
#include <iostream>

using namespace TL;
using namespace TL::Editor;



int main()
{
#ifdef TL_LEAK_CHECK
    TL_CHECK_MEMORY_START();
#endif

    TLOG(info, "This is %s", "info");
    TLOG(debug, "This is %s", "debug");
    TLOG(trace, "This is %s", "trace");
    TLOG(warning, "This is %s", "warning");
    TLOG(error, "This is %s", "error");
    //TLOG(crash, "This is %s", "crash");

    TL_ASSERT(sizeof(int8) == 1, "Size of int8 should be %d", 1);
    TL_ASSERT(sizeof(int16) == 2, "Size of int16 should be %d", 2);
    TL_ASSERT(sizeof(int32) == 4, "Size of int32 should be %d", 4);
    TL_ASSERT(sizeof(int64) == 8, "Size of int64 should be %d", 8);
    TL_ASSERT(sizeof(uint8) == 1, "Size of uint8 should be %d", 1);
    TL_ASSERT(sizeof(uint16) == 2, "Size of uint16 should be %d", 2);
    TL_ASSERT(sizeof(uint32) == 4, "Size of uint32 should be %d", 4);
    TL_ASSERT(sizeof(uint64) == 8, "Size of uint64 should be %d", 8);
    
    //TL_NEVER_HAPPEN();

    TL::Engine::Application* editor = new TL::Editor::Editor();
    editor->Init();
    editor->Run();

#ifdef TL_LEAK_CHECK
    TL_CHECK_MEMORY_END();
#endif
    return 0;
}
