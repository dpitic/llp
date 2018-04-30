; This code snippet is used to investigate an object file.
;   $ objdump -tf -m intel symbols.o
;   $ objdump -D -M intel-mnemonic symbols.o
;   $ readelf --relocs symbols.o
;   $ nm -als symbols.o

section .data                   ; initialised global variables
datavar1: dq 1488
datavar2: dq 42

section .bss                    ; r/w global variables
bssvar1: resq 4*1024*1024
bssvar2: resq 1

section .text

extern somewhere                ; defined in another (external) module
global _start
  mov rax, datavar1
  mov rax, bssvar1
  mov rax, bssvar2
  mov rdx, datavar2
_start:
  jmp _start
  ret
textlabel: dq 0
