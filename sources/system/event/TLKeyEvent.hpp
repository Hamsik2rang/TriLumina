#ifndef __TL_KEY_EVENT__
#define __TL_KEY_EVENT__

#include "system/event/TLEvent.h"

#include <sstream>

TL_NS_BEGIN

class TLKeyEvent : public TLEvent
{
public:
    TLkeyEvent(int keyCode)
    : _keyCode(keyCode)
    {}

    inline int GetKeyCode() { return _keyCode; }
    
    EVENT_CLASS_CATEGORY(TLEventCategory::INPUT | TLEventCategory::KEYBOARD)

private:
    int _keyCode;
};

class TLKeyPressedEvent : public TLKeyEvent
{
public:
    TLKeyPressedEvent(int keyCode, uint32 repeatCount)
    : TLKeyEvent(keyCode),
      _repeatCount(repeatCount)
    {}
    
    inlie int GetRepeatCount() { return _repeatCount; }
    virtual std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << _keyCode << "(" << _repeatCount << " repeats)";
        
        return ss.str();
    }
    
    EVENT_CLASS_TYPE(KEY_PRESSED)
private:
    uint32 _repeatCount;
};

class TLKeyReleasedEvent : public TLKeyEvent
{
public:
    TLKeyReleasedEvent(int keyCode)
    : TLKeyEvent(keyCode)
    {}
    
    virtual std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << _keyCode;
        
        return ss.str();
    }
    
    EVENT_CLASS_TYPE(KEY_RELEASED)
};

TL_NS_END

#endif
