#include "led.h"
#include "driver/gpio.h"

#ifdef _USE_HW_LED

typedef struct
{
  gpio_num_t pin;
  bool on_state;
  bool off_state;
} led_tbl_t;




led_tbl_t led_tbl[LED_MAX_CH] = {
  {GPIO_NUM_38, true, false},
  {GPIO_NUM_39, true, false},

};

bool ledInit(void)
{
  bool ret = true;

  for(int i = 0; i < LED_MAX_CH; i++)
  {
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = 1ULL<<led_tbl[i].pin;
    io_conf.pull_down_en = false;
    io_conf.pull_up_en = false;

    if (gpio_config(&io_conf) != ESP_OK)
    {
      ret = false;
    }

    gpio_set_level(led_tbl[i].pin, led_tbl[i].off_state);
  }

  return ret;
}

void ledOn(uint8_t ch)
{
  if (ch >= LED_MAX_CH) return;
	gpio_set_level(led_tbl[ch].pin, led_tbl[ch].on_state);

}

void ledOff(uint8_t ch)
{
  if (ch >= LED_MAX_CH) return;
	gpio_set_level(led_tbl[ch].pin, led_tbl[ch].off_state);
}

void ledToggle(uint8_t ch)
{
  bool cur_state;
  if (ch >= LED_MAX_CH) return;

  if (led_tbl[ch].pin > GPIO_NUM_31)
  {
    cur_state = (GPIO_REG_READ(GPIO_OUT1_REG) >> (led_tbl[ch].pin - GPIO_NUM_32) & 0x1F) & 1U; //read gpio output1 register
  }
  else
  {
    cur_state = (GPIO_REG_READ(GPIO_OUT_REG) >> led_tbl[ch].pin & 0x1F) & 1U; //read gpio output register
  }
  
  cur_state ^= true;
  gpio_set_level(led_tbl[ch].pin, cur_state);
}


#endif