;16 bit addition function
; To assemble, sdas8051 -ol add_16.asm

;Export the function name. Assembly functions will need a prefix _ to be callable from c. 
.globl _add_16

;CSEG definition below is important. Otherwise linker will place the below code at a location occupied by C code.
.area CSEG
_add_16:
;Calculate pointer to 2nd argument
mov a, sp
clr c
subb a, #3	;SP - 3 will point to LSB of the 2nd argument
mov R0, a	;For @R0 access of 2nd argument

;Add LSB
mov a, dpl	;LSB of arg1 in dpl
add a, @R0	;LSB of arg2 in @R0
mov dpl, a	;LSB of result to be stored in dpl

;Add MSB
mov a, dph	;MSB of arg1 in dph
inc R0
addc a, @R0
mov dph, a	;MSB of result in dph

ret

