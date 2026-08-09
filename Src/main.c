#include <stdint.h>

#include "io.h"
#include "port.h"

void initializeCtc() {
    // 9.8304MHz / 16分周 / 4 = 153.6kHz
    // 割り込み不可、タイマモード、16分周
    io_out(CTC_CH3, 0x07);
    // タイムコンスタント = 4
    io_out(CTC_CH3, 0x04);
}

void initializeSio() {
    // WR0、チャネルリセット
    io_out(SIOA_C, 0x18);
    // 次の書き込み先にWR4を選択
    io_out(SIOA_C, 0x04);
    // WR4、x16クロック、1ストップビット、パリティなし
    io_out(SIOA_C, 0x44);
    // 次の書き込み先にWR5を選択
    io_out(SIOA_C, 0x05);
    // WR5、送信8bit、RTS有効、送信有効
    io_out(SIOA_C, 0x68);
}

uint8_t getSioStatus() { return io_in(SIOA_C); }

void putc(uint8_t data) {
    while (!(getSioStatus() & 0x04));  // 送信可能になるまで待つ
    io_out(SIOA_D, data);
}

void puts(const uint8_t* str) {
    while (*str) {
        putc(*str++);
    }
}

void print_hex4(uint8_t value) {
    value &= 0x0F;
    if (value < 0x0A) {
        putc('0' + value);
    } else {
        putc('A' + value - 0x0A);
    }
}

void print_hex16(uint16_t value) {
    print_hex4((uint8_t)(value >> 12));
    print_hex4((uint8_t)(value >> 8));
    print_hex4((uint8_t)(value >> 4));
    print_hex4((uint8_t)value);
}

void main() {
    initializeCtc();
    initializeSio();

    for (uint16_t i = 0;; i++) {
        puts("0x");
        print_hex16(i);
        putc('\n');
        if (i == 0xFFFF) {
            break;
        }
    }

    while (1);
}
