#ifndef INTERUPT_H
#define INTERUPT_H

/**
 * @brief 割り込みを無効化する
 */
void disableInterrupts();

/**
 * @brief 割り込みを有効化する
 */
void enableInterrupts();

/**
 * @brief 割り込みモードを0にする
 */
void setInterruptMode0();

/**
 * @brief 割り込みモードを1にする
 */
void setInterruptMode1();

/**
 * @brief 割り込みモードを2にする
 */
void setInterruptMode2();

#endif  // INTERRUPT_H
