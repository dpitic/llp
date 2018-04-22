; This program displays the value in rax in hexadecimal format.

section .data
codes:
	db		'0123456789ABCDEF'
newline:
	db		`\n`

section .text
global _start
_start:
	mov		rax, 0x1122334455667788 ; hexadecimal value to display

	mov		rdi, 1                  ; stdout file descriptor
	mov		rdx, 1                  ; number of bytes to output
	mov		rcx, 64                 ; value index counter
	; Each 4 bits should be output as one hexadecimal digit
	; Use shift and bitwise AND to isolate them
	; the result is the offset in 'codes' array
.loop:
	push	rax                     ; preserve value of rax
	sub		rcx, 4                  ; decrement index counter by 4
	; cl is a register, smallest part of rcx
	; rax -- eax -- ax -- ah + al
	; rcx -- ecx -- cx -- ch + cl

  ; Transform whole number in rax into one of its hexadecimal digits 0..15,
  ; use this as an index to look up the hex character in 'codes'.
	sar		rax, cl                 ; shift to 60, 56, 52, ... 4, 0
	and		rax, 0xf                ; clear all bits but the lowest four
	lea		rsi, [codes + rax]      ; look up hexadecimal digit character code
	mov		rax, 1                  ; write() syscall number
	push	rcx                     ; syscall leaves rcx and r11 changed
	syscall                       ; write() hex character to stdout

	pop		rcx
	pop		rax
	test	rcx, rcx                ; check if index is zero
	jnz		.loop

	; Print newline
	mov		rax, 1                  ; write() system call number
	mov		rsi, newline
	mov		rdx, 1
	syscall

	mov		rax, 60                 ; exit() system call number
	xor		rdi, rdi                ; exit() argument: 0
	syscall
