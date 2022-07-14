#include "hw.h"




bool hwInit()
{
	bool ret = true;
	ret &= bspInit();
	ret &= ledInit();

	return ret;
}
