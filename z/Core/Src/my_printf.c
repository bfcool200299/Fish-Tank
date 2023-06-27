#include "my_printf.h"
#include "usart.h"

void uart2_printf( const char *format, ...)
{
    va_list args;
    uint32_t length;
    uint8_t txbuf[TXBUF_SIZE_MAX] = {0};
 
    va_start(args, format);
    length = vsnprintf((char *)txbuf, sizeof(txbuf), (char *)format, args);
    va_end(args);
    HAL_UART_Transmit(&huart2, (uint8_t *)txbuf, length, HAL_MAX_DELAY);
    memset(txbuf, 0, TXBUF_SIZE_MAX);
}

void uart3_printf( const char *format, ...)
{
    va_list args;
    uint32_t length;
    uint8_t txbuf[TXBUF_SIZE_MAX] = {0};
 
    va_start(args, format);
    length = vsnprintf((char *)txbuf, sizeof(txbuf), (char *)format, args);
    va_end(args);
    HAL_UART_Transmit(&huart3, (uint8_t *)txbuf, length, HAL_MAX_DELAY);
    memset(txbuf, 0, TXBUF_SIZE_MAX);
}
