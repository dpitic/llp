;; This source file implements dynamic shared library functions. Used along with
;; the main executable, it demonstrates common features needed from a dynamic
;; library.

extern _GLOBAL_OFFSET_TABLE_

extern commonmsg                ; import common message string symbol from main
extern mainfun                  ; import function defined in main

global fun1:function            ; export dynamic library function

section .rodata                 ; read only data section
msg: db "fun1", 10              ; private message string

section .text                   ; machine instructions
;;
;; @brief      Output message string to stdout.
;;
;; @details    This function first outputs a message string defined locally in
;;             the dynamic library, and then calls a private function that
;;             outputs a message string defined in the main executable file.
;;             It then calls a function defined in the main executable which
;;             outputs the string defined locally in main.
;;             
fun1:
  mov rax, 1                    ; write() syscall identifier
  mov rdi, 1                    ; stdout file descriptor
  lea rsi, [rel msg]            ; address of local message string
  mov rdx, 6                    ; length of string
  syscall
  call fun2                     ; output common message string from main
  call mainfun wrt ..plt        ; call function defined in main
  ret

;;
;; @brief      Output message string to stdout.
;;
;; @details    Private function used to output a message string defined in the
;;             main executable file.
;;
fun2:                           ; local function, not exported
  mov rax, 1                    ; write() syscall identifier
  mov rdi, 1                    ; stdout file descriptor
  ; Common message string defined in main
  mov rsi, [rel commonmsg wrt ..got]
  mov rdx, 5                    ; string length
  syscall
  ret
