;; This program demonstrates the following features:
;;   1. Addressing dynamic library data inside the same library. Deonstrated
;;      in the ex1-lib.asm source file.
;;   2. Calling a function in a dynamic library from the main executable.
;;      Demonstrated in this main file.

; The GOT is usually imported in every file that is dynamically linked. This
; name is specific to ELF format.
extern _GLOBAL_OFFSET_TABLE_
global _start                   ; export program entry point

extern sofun                    ; imported function from dynamic library

section .text                   ; machine instructions
_start:                         ; program entry point
  call sofun wrt ..plt          ; forces linker to create a PLT entry

  mov rdi, 0                    ; exit status
  mov rax, 60                   ; exit() syscall identifier
  syscall

