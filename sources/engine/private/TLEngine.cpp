#include "engine/TLEngine.h"

#include <cstdio>

TL_NS_ENGINE_BEGIN

void TLEngine::Print(const char* msg)
{
	printf("%s", msg);
}

TL_NS_ENGINE_END
