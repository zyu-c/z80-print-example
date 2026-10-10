#include <stdint.h>

#include "io.h"
#include "port.h"

/**
 * @brief CTC3の初期化
 */
void initializeCtc() {
    // 9.8304MHz / 16分周 / 4 = 153.6kHz
    // 割り込み不可、タイマモード、16分周
    io_out(CTC_CH3, 0x07);
    // タイムコンスタント = 4
    io_out(CTC_CH3, 0x04);
}

/**
 * @brief SIOAの初期化
 * @note UART出力用 (9600bps)
 */
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

/**
 * @brief SIOAのコマンド/ステータスレジスタを取得する
 * @return SIOAのコマンド/ステータスレジスタの値
 */
uint8_t getSioStatus() { return io_in(SIOA_C); }

/**
 * @brief 1文字を送信する
 * @param data 送信する文字
 */
void uart_putc(uint8_t data) {
    while (!(getSioStatus() & 0x04));  // 送信可能になるまで待つ
    io_out(SIOA_D, data);
}

/**
 * @brief 文字列を出力する
 * @param str 出力する文字列
 */
void uart_puts(const uint8_t* str) {
    while (*str) {
        uart_putc(*str++);
    }
}

/**
 * @brief 4bitの数値を16進数1桁として出力する
 * @param value 出力する数値
 */
void uart_hex4(uint8_t value) {
    value &= 0x0F;
    if (value < 0x0A) {
        uart_putc('0' + value);
    } else {
        uart_putc('A' + value - 0x0A);
    }
}

/**
 * @brief 16bitの数値を16進数4桁として出力する
 * @param value 出力する数値
 */
void uart_hex16(uint16_t value) {
    uart_hex4((uint8_t)(value >> 12));
    uart_hex4((uint8_t)(value >> 8));
    uart_hex4((uint8_t)(value >> 4));
    uart_hex4((uint8_t)value);
}

void main() {
    initializeCtc();
    initializeSio();

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
