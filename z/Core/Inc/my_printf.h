#ifndef __MY_PRINTF_H__
#define __MY_PRINTF_H__

#include "string.h"
#include "stdio.h"
#include "stdarg.h"
#include "main.h"

#define TXBUF_SIZE_MAX 100

void uart2_printf( const char *format, ...);
void uart3_printf( const char *format, ...);
#endif
