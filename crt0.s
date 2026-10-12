.module crt0

.globl _main
.globl _ctc_isr

.globl  l__DATA             ; DATAエリアのサイズ
.globl  s__DATA             ; DATAエリアの開始アドレス
.globl  l__INITIALIZER
.globl  s__INITIALIZER
.globl  s__INITIALIZED

.area _HEADER (ABS)
.org 0x0000
    jp start

.org 0x0038
    jp _ctc_isr

.area _HOME
.area _CODE
.area _INITIALIZER
.area _GSINIT
.area _GSFINAL

.area _DATA
.area _INITIALIZED


.area _CODE
start:
    ld sp,#0xffff           ; スタックポインタの初期化
    call gsinit             ; グローバル変数の初期化
    call _main              ; main関数呼び出し

hang:
    jr hang                 ; 無限ループ


.area _GSINIT
gsinit:                     ; DATAの初期化
    ld bc,#l__DATA          ; bcにDATAのサイズをロード
    ld a,b                  ; サイズが0かどうかを確認
    or c
    jr z,data_done          ; サイズが0ならdata_zoneへジャンプ

    ld hl,#s__DATA          ; hlにDATAエリアの開始アドレスをロード
    xor a                   ; aをゼロクリア
    ld (hl),a               ; DATAの先頭アドレスをゼロクリア
    dec bc                  ; 残りサイズを1減らす
    ld a,b                  ; 残りサイズが0かどうかを確認
    or c
    jr z,data_done          ; 残りサイズが0ならdata_doneへジャンプ

    ld de,#s__DATA+1        ; deに次のアドレスをロード
    ldir                    ; 残りをゼロクリア

data_done:                  ;_INITIALIZER 
    ld bc,#l__INITIALIZER   ; bcにINITIALIZERのサイズをロード
    ld a,b                  ; サイズが0かどうかを確認
    or c
    jr z,initializer_done   ; サイズが0ならinitializer_doneへジャンプ

    ld hl,#s__INITIALIZER   ; hlにコピー元のアドレスをロード
    ld de,#s__INITIALIZED   ; deにコピー先のアドレスをロード
    ldir                    ; コピー

initializer_done:
.area _GSFINAL
    ret
