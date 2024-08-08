#ifndef __TL_EDITOR__
#define __TL_EDITOR__

#include "TLBase.h"

#include "engine/TLEngine.h"
#include "system/TLLog.h"

TL_NS_EDITOR_BEGIN

using namespace TL;

class TL_EDITOR_API TLEditor
{
public:
	void Print(const char* msg);
	void Run();

private:
	Engine::TLEngine _engine;
};

TL_NS_EDITOR_END

#endif
