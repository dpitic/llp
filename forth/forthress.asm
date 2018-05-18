;;------------------------------------------------------------------------------
; Forthress, a Forth dialect.
; This is the main Forthress file which defines the entry point.
;;------------------------------------------------------------------------------

global _start
%include "libllp.inc"
%include "macro.inc"

; Forth registers are implemented in callee-saved registers, so they are
; guaranteed to survive function calls unchanged.
%define pc r15                  ; pointer to memory cell that stores execution
                                ; token of a word.
%define w r14                   ; pointer to first word when word starts its
                                ; execution.
%define rstack r13              ; return stack used to save and store pc before
                                ; and after a call.

section .text                   ; machine instructions
%include "words.inc"            ; Forthress word dictionary

section .bss                    ; read/write global variables
  resq	1023                    ; return stack 1024 * 8 byte cells
rstack_start: resq 1            ; starting at this address

input_buf: resb 1024
user_dict: resq 65536
user_mem: resq 65536

section .data                   ; initialised global variables
state: dq 0
last_word: dq _lw
here: dq user_dict

section .rodata                 ; read only data
msg_no_such_word: db ": no such word", 10, 0

section .text                   ; machine instructions
next:                           ; Forth engine inner interpreter.
  mov w, [pc]                   ; read memory contents starting at address of pc
  add pc, 8                     ; set command pointer to next instruction
  jmp [w]                       ; jump to implementation code

_start: jmp i_init              ; program starts execution from the init word
