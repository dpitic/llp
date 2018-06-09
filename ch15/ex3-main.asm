;; This program demonstrates common features needed from dynamic library.

extern _GLOBAL_OFFSET_TABLE_

extern fun1                     ; import dynamic library function

; Exported symbols
global commonmsg:data commonmsg.end - commonmsg
global mainfun:function
global _start

section .rodata                 ; read only data
commonmsg: db "fun2", 10, 0     ; exported common message string
.end:

mainfunmsg: db "mainfun", 10, 0 ; private message string

section .text                   ; machine instructions
_start:
  call fun1 wrt ..plt           ; call dynamic library function to output
                                ; private string defined in library
  mov rax, 60                   ; exit() syscall identifier
  mov rdi, 0                    ; exit status
  syscall

;;
;; @brief      Output a string to stdout.
;;
;; @details    This function outputs a private string to stdout. It is called
;;             by the dynamic library to output the private string defined in
;;             the main executable file.
;;
mainfun:
  mov rax, 1                    ; write() syscall identifier
  mov rdi, 1                    ; stdout file descriptor
  mov rsi, mainfunmsg           ; address of string to output
  mov rdx, 8                    ; length of string
  syscall
  ret
