#ifndef __TL_GRAPHICS_CONTEXT__
#define __TL_GRAPHICS_CONTEXT__

#include "TLBase.h"

TL_NS_GRAPHICS_BEGIN

class TLGraphicsContext
{
public:
	TLGraphicsContext() = delete;
	~TLGraphicsContext();

	void Init();
	void Load();



};


TL_NS_GRAPHICS_END

#endif