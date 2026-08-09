#include <stdint.h>

#include "io.h"
#include "port.h"

void initializeCtc() {
    // 割り込み不可、タイマモード、16分周
    io_out(CTC_CH3, 0x07);
    // タイムコンスタント = 4
    io_out(CTC_CH3, 0x04);
}

void main() {
    initializeCtc();
    while (1);
}
