;16 bit multiplication function
; To assemble, sdas8051 -ol mul_16.asm
;
;Register Planning
; R0 & R1 for @R0/@R1 access
;      @R0 points to YL
; R7:R6: Argument 1 X passed through B:A
; R2 = XL.YL.LSB (X_LowByte * Y_LowByte)
; R3 = XL.YL.MSB + XH.YL.LSB + XL.YH.LSB
; R4 =             XH.YL.MSB + XL.YH.MSB + XH.YH.LSB + C
; R5 =                                     XH.YH.MSB + C
; R5:R2 has the 32 bit multiplication result



;Export the function name. Assembly functions will need a prefix _ to be callable from c. 
.globl _mul_16

;CSEG definition below is important. Otherwise linker will place the below code at a location occupied by C code.
.area CSEG
_mul_16:
;Calculate pointer to 2nd argument
mov a, sp
clr c
subb a, #3	;SP - 3 will point to LSB of the 2nd argument
mov R0, a	;For @R0 access of 2nd argument

mov R7, DPH	;XH
mov R6, DPL	;XL

mov B, R6	;XL
mov A, @R0	;YL
mul AB		;XL.YL
mov R2, A	;R2 = XL.YL.LSB /Completed
mov R3, B	;R3 = XL.YL.MSB

mov B, R7	;XH
mov A, @R0	;YL
mul AB		;XH.YL
add A, R3
mov R3, A	;R3 = XL.YL.MSB + XH.YL.LSB
clr A
addc A, B
mov R4, A	;R4 = XH.YL.MSB + C
clr A
addc A, #00
mov R5, A	;R5=0+C

mov B, R6	;XL
inc R0
mov A, @R0	;YH
mul AB		;XL.YH
add A, R3
mov R3, A	;R3 = XL.YL.MSB + XH.YL.LSB + XL.YH.LSB	/Completed
mov A, B
addc A, R4
mov R4, A	;R4 = XH.YL.MSB + XL.YH.MSB + C
clr A
addc A, R5
mov R5, A	;R5 = 0+C 

mov B, R7
mov A, @R0
mul AB		;XH.YH
add A, R4
mov R4, A	;R4 = XH.YL.MSB + XL.YH.MSB + XH.YH.LSB + C	/Completed
mov A, R5
addc A, B
mov R5, A	;R5 = XH.YH.MSB + C	/Completed

mov DPL, R2
mov DPH, R3
mov B, R4
mov A, R5

ret

