.module vector

.globl _ctc_isr

.globl _im2_vector_table

.area _VECTOR_TABLE (ABS)
.org 0x0100
_im2_vector_table:
    .dw _ctc_isr        ; 0x00
