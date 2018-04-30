; This file contains the code for a shared library function.

extern _GLOBAL_OFFSET_TABLE_

global func:function

section .rodata                 ; read only data
message: db "Shared object wrote this", 10, 0
.len: equ $ - message

section .text

;;
;; @brief      Write a null-terminated string to stdout.
;;
;; @details    This function is used to display a string on the termina.
;;
;; @param      rsi is the pointer to the string buffer.
;;
func:
  mov rax, 1                    ; write() system call identifier
  mov rdi, 1                    ; stdout
  mov rsi, message              ; pointer to string to write
  mov rdx, message.len          ; number of bytes in string
  syscall
  ret
