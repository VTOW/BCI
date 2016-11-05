#ifndef BCI_UART_H_INCLUDED
#define BCI_UART_H_INCLUDED

//UART flag for no data
#define BCI_UART_NO_DATA -1

/**
 * Reads the next non-empty data
 * @param  var  Variable to save data to
 * @param  port UART port to read from
 */
#define BCI_UART_ReadNextData(var, port) while ((var = getChar(port)) == BCI_UART_NO_DATA) { wait1Msec(1); }

#endif //BCI_UART_H_INCLUDED
