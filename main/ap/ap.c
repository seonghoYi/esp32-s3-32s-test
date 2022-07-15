#include "ap.h"


void apInit()
{
  //ledOn(_DEF_LED1);
  //ledOn(_DEF_LED2);
  uartOpen(_DEF_UART1, 38400);
  uartPrintf(_DEF_UART1, "uart baud: %d\n", uartGetBaud(_DEF_UART1));
}


void apMain()
{
  uint32_t loop_time = millis();

  while(1)
  {
    //ledToggle(_DEF_LED1);
    //delay(1000);
    if (millis()-loop_time>=1000)
    {
      ledToggle(_DEF_LED2);
      loop_time = millis();
    }

    if (uartAvailable(_DEF_UART1) > 0)
    {
      uint8_t rx = uartRead(_DEF_UART1);
      uartPrintf(_DEF_UART1, "%c\n", (char)rx);
    }
  }
}