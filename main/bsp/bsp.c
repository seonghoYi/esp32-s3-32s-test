#include "bsp.h"

bool bspInit()
{
  bool ret = true;

  return ret;
}



uint32_t millis()
{
	return (uint32_t)(esp_timer_get_time() / 1000ULL);
}

uint32_t micros()
{
  return (uint32_t)(esp_timer_get_time());
}

void delay(uint32_t ms)
{
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}