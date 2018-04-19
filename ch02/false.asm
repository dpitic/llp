; Program that mimics the shell false command
global _start

section .text
_start:
  mov rdi, 1                    ; exit code 1
  mov rax, 60                   ; exit() syscall number
  syscall
