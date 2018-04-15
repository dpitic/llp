; This program displays the value in rax in hexadecimal format.

section .data
codes:
	db		'0123456789ABCDEF'
newline:
	db		`\n`

section .text
global _start
_start:
	mov		rax, 0x1122334455667788		; hexadecimal value to display

	mov		rdi, 1
	mov		rdx, 1
	mov		rcx, 64
	; Each 4 bits should be output as one hexadecimal digit
	; Use shift and bitwise AND to isolate them
	; the result is the offset in 'codes' array
.loop:
	push	rax
	sub		rcx, 4
	; cl is a register, smallest part of rcx
	; rax -- eax -- ax -- ah + al
	; rcx -- ecx -- cx -- ch + cl
	sar		rax, cl
	and		rax, 0xf

	lea		rsi, [codes + rax]
	mov		rax, 1

	; syscall leaves rcx and r11 unchanged
	push	rcx
	syscall
	pop		rcx

	pop		rax
	; Test can be used for the fasted 'is it a zero?' check
	test	rcx, rcx
	jnz		.loop

	; Print newline
	mov		rax, 1				; write() system call number
	mov		rsi, newline
	mov		rdx, 1
	syscall

	mov		rax, 60				; exit() system call number
	xor		rdi, rdi			; exit() argument: 0
	syscall