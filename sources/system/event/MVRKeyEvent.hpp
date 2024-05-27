#ifndef __MVR_KEY_EVENT__
#define __MVR_KEY_EVENT__

#include "system/event/MVREvent.h"

#include <sstream>

MVR_NS_BEGIN

class MVRKeyEvent : public MVREvent
{
public:
    MVRkeyEvent(int keyCode)
    : _keyCode(keyCode)
    {}

    inline int GetKeyCode() { return _keyCode; }
    
    EVENT_CLASS_CATEGORY(MVREventCategory::INPUT | MVREventCategory::KEYBOARD)

private:
    int _keyCode;
};

class MVRKeyPressedEvent : public MVRKeyEvent
{
public:
    MVRKeyPressedEvent(int keyCode, uint32 repeatCount)
    : MVRKeyEvent(keyCode),
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

class MVRKeyReleasedEvent : public MVRKeyEvent
{
public:
    MVRKeyReleasedEvent(int keyCode)
    : MVRKeyEvent(keyCode)
    {}
    
    virtual std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << _keyCode;
        
        return ss.str();
    }
    
    EVENT_CLASS_TYPE(KEY_RELEASED)
};

MVR_NS_END

#endif
