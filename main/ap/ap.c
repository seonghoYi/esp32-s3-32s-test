#include "ap.h"




void apInit()
{
  //ledOn(_DEF_LED1);
  //ledOn(_DEF_LED2);
}


void apMain()
{
  while(1)
  {
    ledToggle(_DEF_LED1);
    delay(1000);
    ledToggle(_DEF_LED2);
    delay(1000);
    //printf("running\n");
  }
}