#ifndef PORT_H
#define PORT_H

// Super AKI-80 I/Oポート定義
#define CTC_CH0 0x10  // CTCチャンネル0
#define CTC_CH1 0x11  // CTCチャンネル1
#define CTC_CH2 0x12  // CTCチャンネル2
#define CTC_CH3 0x13  // CTCチャンネル3

#define SIOA_D 0x18  // SIOチャンネルA データ
#define SIOA_C 0x19  // SIOチャンネルA コマンド/ステータス
#define SIOB_D 0x1A  // SIOチャンネルB データ
#define SIOB_C 0x1B  // SIOチャンネルB コマンド/ステータス

#define PIOA_D 0x1C  // PIOチャンネルA データ
#define PIOA_C 0x1D  // PIOチャンネルA コマンド/ステータス
#define PIOB_D 0x1E  // PIOチャンネルB データ
#define PIOB_C 0x1F  // PIOチャンネルB コマンド/ステータス

#define PPI0A_D 0x30  // PPI0チャンネルA データ
#define PPI0B_D 0x31  // PPI0チャンネルB データ
#define PPI0C_D 0x32  // PPI0チャンネルC データ
#define PPI0_C 0x33   // PPI0 コマンド

#define PPI1A_D 0x34  // PPI1チャンネルA データ
#define PPI1B_D 0x35  // PPI1チャンネルB データ
#define PPI1C_D 0x36  // PPI1チャンネルC データ
#define PPI1_C 0x37   // PPI1 コマンド

#define WDT_S 0xF0  // ウォッチドッグタイマ スタンバイ モード設定
#define WDT_C 0xF1  // ウォッチドッグタイマ コマンド

#endif  // PORT_H
