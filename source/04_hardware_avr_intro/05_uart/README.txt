This is an example of using the serial port
in polling mode

Three routines:
UART_init(): initializes the UART (19200)
UART_putChar(uint8_t): waits for the uart to be free and writes a character
UART_getChar(): blocking, waits for an input to be available

The program implements a simple serial echo
Use a serial terminal, and write something