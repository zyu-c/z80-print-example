#ifndef IO_H
#define IO_H

#include <stdint.h>

/**
 * @brief IOポートへ1バイトを出力する
 * @param port 出力先のIOポート番号
 * @param value 出力する値
 */
void io_out(uint8_t port, uint8_t value) __sdcccall(0);

/**
 * @brief IOポートから1バイトを入力する
 * @param port 入力元のIOポート番号
 * @return 入力した値
 */
uint8_t io_in(uint8_t port) __sdcccall(0);

#endif  // IO_H
