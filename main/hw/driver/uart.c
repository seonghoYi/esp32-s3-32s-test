#include "uart.h"
#include "qbuffer.h"


#include "driver/uart.h"

#ifdef _USE_HW_UART



#define UART_RX_BUF_SIZE    512
#define UART_TX_BUF_SIZE    512

typedef struct
{
  bool is_init;

  uart_port_t uart_num;
  uart_config_t uart_config;
  QueueHandle_t queue;
  int queue_size;


  qbuffer_t qbuffer;
  uint8_t q_buf[UART_RX_BUF_SIZE];
  uint8_t rx_buf[UART_RX_BUF_SIZE];
} uart_tbl_t;


uart_tbl_t uart_tbl[UART_MAX_CH];


bool uartInit(void)
{
  bool ret = true;
  for (int i = 0; i < UART_MAX_CH; i++)
  {
    uart_tbl[i].is_init = false;
  }
  return ret;
}


bool uartOpen(uint8_t ch, uint32_t baud)
{
  bool ret = false;
  
  uart_tbl_t *p_uart = &uart_tbl[ch];


  switch (ch)
  {
  case _DEF_UART1:
    p_uart->is_init   = true;
    p_uart->uart_num  = UART_NUM_0;

    p_uart->uart_config.baud_rate   = baud;
    p_uart->uart_config.data_bits   = UART_DATA_8_BITS;
    p_uart->uart_config.parity      = UART_PARITY_DISABLE;
    p_uart->uart_config.stop_bits    = UART_STOP_BITS_1;
    p_uart->uart_config.flow_ctrl   = UART_HW_FLOWCTRL_DISABLE;
    p_uart->uart_config.source_clk  = UART_SCLK_APB;

    p_uart->queue = NULL;
    p_uart->queue_size = 0;

    uart_driver_install(UART_NUM_0, UART_RX_BUF_SIZE, UART_TX_BUF_SIZE, 0, NULL, 0);

    uart_set_pin(UART_NUM_0, 43, 44, -1, -1);

    qbufferCreate(&p_uart->qbuffer, &p_uart->q_buf[0], UART_RX_BUF_SIZE);

    ret = true;
    break;
  case _DEF_UART2:
    break;
  }

  return ret;
}

uint32_t uartAvailable(uint8_t ch)
{
  uint32_t ret = 0;
  uint32_t rx_len;
  uart_tbl_t *p_uart = &uart_tbl[ch];

  switch (ch)
  {
  case _DEF_UART1:
  
    rx_len = uart_read_bytes(p_uart->uart_num, &p_uart->rx_buf[0], UART_RX_BUF_SIZE-1, 10/portTICK_PERIOD_MS);
    qbufferWrite(&p_uart->qbuffer, &p_uart->rx_buf[0], rx_len);
    ret = qbufferAvailable(&p_uart->qbuffer);
  
    break;
  case _DEF_UART2:
    break;
  }
  return ret;
}

uint8_t uartRead(uint8_t ch)
{
  uint8_t ret = 0;

  uart_tbl_t *p_uart = &uart_tbl[ch];

  switch (ch)
  {
  case _DEF_UART1:
    if (qbufferRead(&p_uart->qbuffer, &ret, 1) != true)
    {
      ret = 0;
    }
    break;
  case _DEF_UART2:
    break;
  }
  return ret;
}

uint32_t uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length)
{
  uint32_t ret = 0;
  
  uart_tbl_t *p_uart = &uart_tbl[ch];
  
  switch (ch)
  {
  case _DEF_UART1:
    ret = uart_write_bytes(p_uart->uart_num, (void *)p_data, length); 
    break;
  case _DEF_UART2:
    break;
  }
  return ret;
}

uint32_t uartPrintf(uint8_t ch, char *fmt, ...)
{
  char buf[256];
	va_list args;
	int len;
	uint32_t ret;

	va_start(args, fmt);
	len = vsnprintf(&buf[0], 256, fmt, args);

	ret = uartWrite(ch, (uint8_t *)&buf[0], len);

	va_end(args);
	return ret;
}

uint32_t uartGetBaud(uint8_t ch)
{
  uint32_t ret = 0;
  uart_tbl_t *p_uart = &uart_tbl[ch];

  switch (ch)
  {
  case _DEF_UART1:
    //uart_get_baudrate(p_uart->uart_num, &ret);
    ret = p_uart->uart_config.baud_rate;
    break;
  case _DEF_UART2:
    break;
  }
  return ret;
}

bool uartFlush(uint8_t ch)
{
  bool ret = true;
  uart_tbl_t *p_uart = &uart_tbl[ch];

  switch (ch)
  {
  case _DEF_UART1:
    if (uart_flush(p_uart->uart_num) != ESP_OK)
    {
      ret = false;
    }
    break;
  case _DEF_UART2:
    break;
  }

  return ret;
}


#endif