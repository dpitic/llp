;; Dynamic library that defines a function and a string. The function calls
;; the standard C library function puts() to output a private string defined in
;; the dynamic library. The exported string is output by the main program.

extern _GLOBAL_OFFSET_TABLE_

extern puts                     ; puts() from C standard library

global sostr:data (sostr.end - sostr)
global sofun:function

section .rodata
sostr: db "sostring", 10, 0
.end:

localstr: db "localstr", 10, 0

section .text
sofun:
  lea rdi, [rel localstr]
  call puts wrt ..plt           ; call standard C library puts()
  mov rax, 42                   ; return value, alway 42
  ret
