#ifndef __MVR_WINDOW__
#define __MVR_WINDOW__

#include "MVRBase.h"


MVR_NS_BEGIN

struct MVRSurface
{
    uint32 width;
    uint32 height;
}

class MVRWindow
{
public:
    MVRWindow() = default;
    
    
    
    inline const MVRSurface GetSurface() { return _surface; }
    virtual void* GetHandle() = 0;
private:
    MVRSurface _surface;
    void* _handle;
    
};



MVR_NS_END


#endif
