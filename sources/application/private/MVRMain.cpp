#include "editor/MVREditor.h"

using namespace MVR;
using namespace MVR::Editor;

int main()
{
    MVREditor editor;
    editor.Print("Hello MVR!");

    assert(sizeof(int8) == 1);
    assert(sizeof(uint8) == 1);
    assert(sizeof(int16) == 2);
    assert(sizeof(uint16) == 2);
    assert(sizeof(int32) == 4);
    assert(sizeof(uint32) == 4);
    assert(sizeof(int64) == 8);
    assert(sizeof(uint64) == 8);
    

    return 0;
}