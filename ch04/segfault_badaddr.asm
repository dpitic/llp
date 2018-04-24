; This program demonstrates what happens if you try to write into a forbidden
; memory location.

section .data
correct: dq -1

section .text
global _start
_start:
  mov rax, [0x400000-1]         ; access address 0x3fffff, which is one byte
                                ; before the code segment start.

  mov rax, 60                   ; exit()
  xor rdi, rdi                  ; exit status 0
  syscall
