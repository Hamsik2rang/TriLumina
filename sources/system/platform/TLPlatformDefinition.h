#include "TLBase.h"


TL_NS_BEGIN


void* tl_platform_window_create(const char* title, uint32 width, uint32 height);
void tl_platform_window_destroy(void* handle);

TL_NS_END
