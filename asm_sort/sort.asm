;Bubble Sort an array at 0x70

D_0 EQU 0x70
D_1 EQU 0x71
C_0 EQU 0x0070
ORG 0x70
DB 0xaa,0x09,0x05,0x07,0x33,0x08 
LEN EQU 10

ORG 0000
;Copy table from prog. mem to data mem.
mov R7, #00   ;Loop Counter
mov R0, #D_0  ;Data Mem. ptr
mov DPTR, #C_0;Prog. Mem. Base. ptr
copy:
    mov A, R7
	movc A, @A+DPTR
	mov @R0, A
	inc R0
	inc R7
	cjne R7, #LEN, copy


mov R7, #01
sort:
	mov R0, #D_0
	mov R1, #D_1
	mov A, R7
	mov R6, A
	lp:
		mov A, @R0
		clr C
		subb A, @R1
		jnc noxch	;jc: ascending. jnc: descending
			mov A, @R0
			xch A, @R1
			mov @R0, A
		noxch:
		inc R6
		inc R0
		inc R1
		cjne R6, #LEN, lp
	inc R7
    cjne R7, #LEN, sort

endlp: jmp endlp


