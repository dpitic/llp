global _start

; .data section is used for global variables.
section .data
message: db 'hello, world!', 10		; 10 is new line ASCII code

; .text section is used for for program instructions.
section .text
_start:						; Entry point. First instruction to be executed.
	mov		rax, 1			; system call number should be stored in rax
	mov		rdi, 1			; argument #1 in rdi: write file descriptor
	mov		rsi, message	; argument #2 in rsi: start of string buffer
	mov		rdx, 14			; argument #3 in rdx: number bytes to write
	syscall					; invokes a system call