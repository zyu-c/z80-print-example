#include <stdint.h>

#include "uart.h"

void main() {
    initializeUart();

    while (1) {
        uart_putc(uart_getc());
    }
}
