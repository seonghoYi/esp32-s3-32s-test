#ifndef MAIN_BSP_BSP_H_
#define MAIN_BSP_BSP_H_

#include "def.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#include "esp_timer.h"



bool bspInit();

uint32_t millis();
uint32_t micros();
void delay(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif /* MAIN_BSP_BSP_H_ */
