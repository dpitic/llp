; This file contains the code for a shared library function.

extern _GLOBAL_OFFSET_TABLE_

global func:function

section .rodata
message: db "Shared object wrote this", 10, 0

section .text
func:
  mov rax, 1                    ; write() system call identifier
  mov rdi, 1                    ; stdout
  mov rsi, message              ; pointer to string to write
  mov rdx, 14                   ; number of bytes in string
  syscall
  ret
