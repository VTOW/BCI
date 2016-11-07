#ifndef BCI_UART_C_INCLUDED
#define BCI_UART_C_INCLUDED

#include "uart.h"

void BCI_UART_ClearDataInBuffer(TUARTs port)
{
  while(getChar(port) != -1) {}
}

#endif // BCI_UART_C_INCLUDED
