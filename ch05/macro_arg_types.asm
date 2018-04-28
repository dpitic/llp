; This program demonstrates the use of a macro that prints either a number or
; a string (using an identifier). It uses the custom I/O library functions to
; calculate string length, output string and output integer.

;;
;; @brief      Output the argument to stdout.
;;
;; @details    This macro accepts either an identifier for a null-terminated
;;						 string or a number literal.
;;
;; @param      Either an identifier for a string or a number literal.
;;
%macro print 1
  %ifid %1                      ; check if argument is an identifier
    mov rdi, %1
    call print_string
  %else
    %ifnum %1                   ; check if argument is a number
      mov rdi, %1
      call print_uint
    %else
      %error "String literals are not supported yet"
    %endif
  %endif
%endmacro

section .data
myhello: db 'hello', 10, 0

section .text
extern print_string
extern print_uint
extern print_newline
global _start
_start:
  print myhello                 ; call print_string
  print 42                      ; call print_uint
  call print_newline
  mov rax, 60                   ; exit() system call identifier
  xor rdi, rdi                  ; 0 exit status
  syscall
