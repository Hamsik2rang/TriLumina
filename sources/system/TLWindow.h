#ifndef __TL_WINDOW__
#define __TL_WINDOW__

#include "TLBase.h"


TL_NS_BEGIN

class TLIWindow
{
public:
    TLIWindow() = default;
    
    inline const uint32 GetWidth() const { return _width; }
    inline const uint32 GetHeight() const { return _height; }
    inline const char* GetTitle() const { return _title; }
    virtual void* GetHandle() = 0;
private:
    const char* _title;
    uint32 _width;
    uint32 _height;
};


TL_NS_END


#endif
