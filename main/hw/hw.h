#ifndef MAIN_HW_HW_H_
#define MAIN_HW_HW_H_

#include "hw_def.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "gpio.h"
#include "led.h"
#include "uart.h"

bool hwInit();

#ifdef __cplusplus
}
#endif

#endif /* MAIN_HW_HW_H_ */
