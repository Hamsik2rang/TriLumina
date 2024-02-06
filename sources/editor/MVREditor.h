#ifndef __MVR_EDITOR__
#define __MVR_EDITOR__

#include "MVRBase.h"

#include "engine/MVREngine.h"
#include "system/MVRLog.h"

MVR_NS_EDITOR_BEGIN

using namespace MVR;

class MVR_EDITOR_API MVREditor
{
public:
	void Print(const char* msg);

private:
	Engine::MVREngine _engine;
};

MVR_NS_EDITOR_END

#endif