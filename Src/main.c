#include <stdint.h>

#include "interrupt.h"
#include "io.h"
#include "port.h"
#include "uart.h"

volatile uint16_t count = 0;
volatile uint8_t flag = 0;

void ctc_isr() __interrupt {
    count++;
    if (count >= 1000) {
        count = 0;
        flag = 1;
    }
}

void main() {
    disableInterrupts();
    setInterruptMode2();
    initializeUart();

    // CTC_CH0を1ms周期で割り込みを発生させるように設定
    io_out(CTC_CH0, 0x00);
    io_out(CTC_CH0, 0xA7);
    io_out(CTC_CH0, 38);

    enableInterrupts();

    while (1) {
        if (flag) {
            flag = 0;
            uart_putc('.');
        }
    }
}
