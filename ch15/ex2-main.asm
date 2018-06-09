;; This program will demonstrate how a dynamic library function can access an
;; external variable. The message string will be defined in the main executable
;; file.
extern _GLOBAL_OFFSET_TABLE_
global _start

extern sofun                    ; import function from dynamic library

; It is important to make the dynamically shared data declaration with its
; size. Otherwise, the symbol will be treated as global by the static linker
; (visible to other modules during static linking phase), but will not be
; exported by the dynamic library.
global msg:data (msg.end - msg) ; export message string (with size)

section .rodata
msg:  db "SO function called -- message is stored in 'main'", 10
.end:

section .text
_start:
  call sofun wrt ..plt

  mov rdi, 0                    ; exit status
  mov rax, 60                   ; exit() syscall identifier
  syscall
