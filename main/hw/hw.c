#include "hw.h"




bool hwInit()
{
	bool ret = true;
	ret &= bspInit();
	ret &= ledInit();
	ret &= uartInit();

	return ret;
}
