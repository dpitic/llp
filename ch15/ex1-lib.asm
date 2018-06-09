;; This source file implements a dynamic library function, and demonstrates
;; accessing dynamic library data inside the same library.

; GOT is imported in every file that is dynamically linked. This name is
; specific to ELF format.
extern _GLOBAL_OFFSET_TABLE_
global sofun:function           ; exported library function

section .rodata                 ; read only data
msg:  db "SO function called", 10
.end:

section .text
sofun:
  mov rax, 1                    ; write() syscall identifier
  mov rdi, 1                    ; stdout file descriptor
  lea rsi, [rel msg]            ; address of string to output
  mov rdx, msg.end - msg        ; length of string
  syscall
  ret
