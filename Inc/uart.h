#ifndef UART_H
#define UART_H

#include <stdint.h>

#include "io.h"
#include "port.h"

/**
 * @brief UARTの初期化
 * @note 9600bps、8bit、1ストップビット、パリティなし
 */
void initializeUart();

/**
 * @brief 1文字を送信する
 * @param data 送信する文字
 */
void uart_putc(uint8_t data);

/**
 * @brief 文字列を出力する
 * @param str 出力する文字列
 */
void uart_puts(const uint8_t* str);

/**
 * @brief 4bitの数値を16進数1桁として出力する
 * @param value 出力する数値
 */
void uart_hex4(uint8_t value);

/**
 * @brief 16bitの数値を16進数4桁として出力する
 * @param value 出力する数値
 */
void uart_hex16(uint16_t value);

/**
 * @brief 1文字を受信する
 * @return 受信した文字
 */
uint8_t uart_getc();

#endif  // UART_H
