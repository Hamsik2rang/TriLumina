#ifndef __TL_KEY_EVENT__
#define __TL_KEY_EVENT__

#include "system/event/TLEvent.h"

#include <sstream>

TL_NS_BEGIN

class KeyEvent : public Event
{
public:
    KeyEvent(int keyCode)
    : _keyCode(keyCode)
    {}

    inline int GetKeyCode() { return _keyCode; }
    
    EVENT_CLASS_CATEGORY(EventCategory::INPUT | EventCategory::KEYBOARD)

protected:
    int _keyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
    KeyPressedEvent(int keyCode, uint32 repeatCount)
        : KeyEvent(keyCode)
        , _repeatCount(repeatCount)
    {}
    
    inline int GetRepeatCount() { return _repeatCount; }
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

class KeyReleasedEvent : public KeyEvent
{
public:
    KeyReleasedEvent(int keyCode)
    : KeyEvent(keyCode)
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
