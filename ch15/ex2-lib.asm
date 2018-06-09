;; This program implements a dynamic library function that outputs some text
;; to stdout. It is used to demonstrate how to access the message string 
;; defined in the main executable.
extern _GLOBAL_OFFSET_TABLE_
global sofun:function           ; exported dynamic library function

extern msg                      ; imported message string

section .text
sofun:
  mov rax, 1                    ; write() syscall identifier
  mov rdi, 1                    ; stdout file descriptor
  mov rsi, [rel msg wrt ..got]
  mov rdx, 50                   ; string length
  syscall
  ret
