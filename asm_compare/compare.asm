	mov A, 0x70
	mov R0, 0x71
	subb A, R0
	jc mov_1
	mov 0x72, 0x71
	jmp end
mov_1:	mov 0x72, 0x70
end:	jmp end
