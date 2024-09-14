#ifndef __TL_APPLICATION__
#define __TL_APPLICATION__

#include "TLBase.h"

#include "system/TLWindow.h"

TL_NS_ENGINE_BEGIN

class TL_API Application
{
public:
	Application()
		: _windows{ nullptr }
		, _system{ nullptr }
		, _engine{ nullptr }
	{}

	virtual ~Application() {}

	virtual bool Init() = 0;
	virtual void Run() = 0;
	virtual void Shutdown() = 0;

protected:
	//TODO: 추후 List 형식으로 변경.
	Window* _windows;
	SystemContext* _system;
	EngineContext* _engine;

	//TODO: Timer 구현 필요
	float _deltaTime;

};

TL_NS_ENGINE_END
#endif