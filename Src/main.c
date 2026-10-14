#include <stdint.h>

#include "interrupt.h"
#include "io.h"
#include "port.h"
#include "uart.h"

volatile uint8_t count_1s = 0;
volatile uint8_t flag_1s = 0;

void ctc_isr() __interrupt {
    count_1s++;
    if (count_1s >= 200) {
        flag_1s = 1;
        count_1s = 0;
    }
}

void main() {
    disableInterrupts();
    setInterruptMode2();
    initializeUart();

    // CTC_CH0を5ms周期で割り込みを発生させるように設定
    io_out(CTC_CH0, 0x00);
    io_out(CTC_CH0, 0xA7);
    io_out(CTC_CH0, 192);

    enableInterrupts();

    uint16_t time = 0;
    while (1) {
        if (flag_1s) {
            flag_1s = 0;
            uart_hex16(time);
            uart_puts(" s\n");
            time++;
        }
    }
}
