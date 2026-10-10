.module io

.area _CODE

.globl _io_out
.globl _io_in

; void io_out(uint8_t port, uint8_t value);
_io_out:
    ld c, a                 ; c = port
    ld a, l                 ; a = value

    out (c), a              ; portにvalueを出力
    ret


; uint8_t io_in(uint8_t port);
_io_in:
    ld c, a                 ; c = port

    in a, (c)               ; aにportの値を入力

    ld l, a                 ; l = a
    ld h, #0                ; h = 0;

    ret                     ; hlを返す
