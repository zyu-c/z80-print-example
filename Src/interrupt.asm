.module interrupt

.area _CODE

.globl _disableInterrupts
.globl _enableInterrupts
.globl _setInterruptMode0
.globl _setInterruptMode1
.globl _setInterruptMode2

; void disableInterrupts();
_disableInterrupts:
    di
    ret

; void enableInterrupts();
_enableInterrupts:
    ei
    ret

; void setInterruptMode0();
_setInterruptMode0:
    im 0
    ret

; void setInterruptMode1();
_setInterruptMode1:
    im 1
    ret

; void setInterruptMode2();
_setInterruptMode2:
    im 2
    ret
