#ifndef __TL_WINDOW__
#define __TL_WINDOW__

#include "TLBase.h"


TL_NS_BEGIN

class TLWindow
{
public:
    TLWindow() = default;
    
    
    
    inline const uint32 GetWidth() const { return _width; }
    virtual void* GetHandle() = 0;
private:
    const char* _title;
    uint32 _width;
    uint32 _height;
    
    void* _handle;
};


TL_NS_END


#endif
