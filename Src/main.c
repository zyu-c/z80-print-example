#include <stdint.h>

#include "io.h"
#include "port.h"
#include "uart.h"

volatile uint16_t count = 0;
volatile uint8_t flag = 0;

void ctc_isr() __critical __interrupt(0) {
    count++;
    if (count >= 1000) {
        count = 0;
        flag = 1;
    }
}

void main() {
    // 初期化中は割り込み禁止
    __asm
        di
        im 1
    __endasm;

    initializeUart();

    // CTC_CH0を1ms周期で割り込みを発生させるように設定
    io_out(CTC_CH0, 0xA7);
    io_out(CTC_CH0, 38);

    // 割り込み許可
    __asm
        ei
    __endasm;

    while (1) {
        if (flag) {
            flag = 0;
            uart_putc('.');
        }
    }
}
