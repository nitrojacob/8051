	mov A, #0x0A
	call lp_fn
end:	jmp end

lp_fn:	push PSW
lp:	dec A
	jnz lp
	pop PSW
	ret
