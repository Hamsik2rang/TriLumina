#ifndef __TL_EVENT__
#define __TL_EVENT__

#include "TLBase.h"

#include "system/TLLog.h"

#include <functional>
#include <string>

TL_NS_BEGIN

enum class TLEventType : uint8
{
    NONE = 0,
    
    KEY_PRESSED,
    KEY_RELEASED,
    
    MOUSE_MOVED,
    MOUSE_SCROLLED,
    MOUSE_BUTTON_PRESSED,
    MOUSE_BUTTON_RELEASED,
    
    WINDOW_CLOSED,
    WINDOW_RESIZED,
    WINDOW_MOVED,
    WINDOW_FOCUSED,
    WINDOW_LOST_FOCUSED,

    APP_TICK,
    APP_UPDATE,
    APP_RENDER,
};

enum class TLEventCategory
{
    NONE            = 0,
    APPLICATION     = BIT(0),
    INPUT           = BIT(1),
    KEYBOARD        = BIT(2),
    MOUSE           = BIT(3),
    MOUSE_BUTTON    = BIT(4),
};

#define EVENT_CLASS_TYPE(type) static TLEventType GetStaticType() { return TLEventType::##type; } \
                                virtual TLEventType GetEventType() const override { return GetStaticType(); } \
                                virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

class TLEvent
{
    friend class TLEventDispatcher;
public:
    virtual TLEventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    virtual std::string ToString() const { return std::string(GetName()); }
    
    inline bool IsHandled() const { return _isHandled; }
    inline bool IsCategory(const TLEventCategory& category) const { return GetCategoryFlags() & category; }
    
protected:
    bool _isHandled;
};

class TLEventDispatcher
{
    template <typename T>
    using EventFunc = std::function<bool(T&)>;
    
public:
    TLEventDispatcher(TLEvent& event) 
        : _event{event}
    {}
    
    template <typename T>
    bool Dispatch(EventFunc<T> func)
    {
        if (_event.GetEventType() == T::GetStaticType())
        {
            _event._isHandled = func(*(T*)&_event);
            
            return true;
        }
        
        return false;
    }
    
private:
    TLEvent& _event;
};

TL_NS_END

#endif
