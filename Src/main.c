#include <stdint.h>

#include "uart.h"

void main() {
    initializeUart();

    for (uint16_t i = 0;; i++) {
        uart_puts("0x");
        uart_hex16(i);
        uart_putc('\n');
        if (i == 0xFFFF) {
            break;
        }
    }

    while (1);
}
