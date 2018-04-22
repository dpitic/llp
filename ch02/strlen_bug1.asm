; Alternative version of program to strlen with some bugs.
global _start

section .data
test_string: db "abcdef", 0

section .text

strlen:
.loop:
  ; By convention, the first and the only argument is taken from rdi
  ; String length counter in r13
  ; r13 is a callee-saved register, so should be saved on stack before use.
  cmp byte [rdi+r13], 0         ; BUG: r13 not initialised
  je .end
  inc r13
  jmp .loop
.end:
  mov rax, r13                  ; return rax = length of string
  ret

_start:
  mov rdi, test_string
  call strlen                   ; return rax = length of string
  mov rdi, rax                  ; rdi = string length, use as exit code

  mov rax, 60                   ; exit() syscall number
  syscall
