; This program calls the function provided by the shared object libso. It acts
; as a minimal launcher that calls the function in the shared object and exits
; cleanly.
; Examine the executable object using:
;   $ readelf -S libso_main

global _start

extern func                     ; defined in shared library

section .text
_start:
;  mov rdi, 10
  call func
;  mov rdi, rax
  mov rax, 60                   ; exit() syscall identifier
  xor rdi, rdi                  ; 0 exit status
  syscall
