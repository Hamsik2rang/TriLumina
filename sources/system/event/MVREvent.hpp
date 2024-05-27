#ifndef __MVR_EVENT__
#define __MVR_EVENT__

#include "MVRBase.h"

#include "system/MVRLog.h"

#include <functional>
#include <string>

MVR_NS_BEGIN

enum class MVREventType : uint8
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

enum class MVREventCategory
{
    NONE            = 0,
    APPLICATION     = BIT(0),
    INPUT           = BIT(1),
    KEYBOARD        = BIT(2),
    MOUSE           = BIT(3),
    MOUSE_BUTTON    = BIT(4),
};

#define EVENT_CLASS_TYPE(type) static MVREventType GetStaticType() { return MVREventType::##type; } \
                                virtual MVREventType GetEventType() const override { return GetStaticType(); } \
                                virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

class MVREvent
{
    friend class MVREventDispatcher;
public:
    virtual MVREventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    virtual std::string ToString() const { return std::string(GetName()); }
    
    inline bool IsHandled() const { return _isHandled; }
    inline bool IsCategory(const MVREventCategory& category) const { return GetCategoryFlags() & category; }
    
protected:
    bool _isHandled;
};

class MVREventDispatcher
{
    template <typename T>
    using EventFunc = std::function<bool(T&)>;
    
public:
    MVREventDispatcher(Event& event) 
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
    MVREvent& _event;
};

MVR_NS_END

#endif
