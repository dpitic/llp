; This program us used to investigate executable object files. It depends on
; symbols.o object file. Dump the file using:
;   $ objdump -tf executable_object

global somewhere
global func

section .data
somewhere: dq 999
private: dq 666

section .text

func:
  mov rax, somewhere
  ret
