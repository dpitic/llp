; This program calls the function provided by the shared object libso.

global _start

extern func                     ; defined in shared library

_start:
  mov rdi, 10
  call func
  mov rdi, rax
  mov rax, 60
  syscall
