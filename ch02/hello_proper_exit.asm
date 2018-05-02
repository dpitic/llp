; This program outputs a string on the terminal display and demonstrates how to
; cleanly terminate program execution using the exit() system call.

; Global variables section
section .data
message: db 'hello, world!', 10 ; output string buffer
.len: equ $ - message

section .text
global _start

_start:
  mov     rax, 1                ; write() system call number
  mov     rdi, 1                ; stdout file descriptor
  mov     rsi, message          ; start address of output string buffer
  mov     rdx, message.len      ; length of output string buffer in bytes
  syscall

  mov     rax, 60               ; exit() system call number
  xor     rdi, rdi              ; exit() argument: 0
  syscall
