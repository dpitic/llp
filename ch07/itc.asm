; This program uses indirect threaded code to implement words in Forth. It uses
; the I/O library.

extern read_word
extern print_string
global _start

%define pc r15                  ; pointer to memory cell that stores execution
                                ; token of a word.
%define w r14                   ; pointer to first word when word starts its
                                ; execution.
%define rstack r13              ; return stack used to save and restore pc
                                ; before and after a call.

section .bss
  resq 1023
rstack_start: resq 1
input_buf: resb 1024

section .text

main_stub: dq xt_main           ; this one cell is the program

; The dictionary starts here.

; Drop the topmost element from the stack
  dq 0                          ; there is no previous node
  db "drop", 0
  db 0                          ; flags
xt_drop: dq i_drop
i_drop:
  add rsp, 8
  jmp next

; Initialise registers
xt_init: dq i_init
i_init:
  mov rstack, rstack_start
  mov pc, main_stub
  jmp next

; Save pc when the colon word starts
xt_docol: dq i_docol
i_docol:
  sub rstack, 8
  mov [rstack], pc
  add w, 8
  mov pc, w
  jmp next

; Return from the colon word
xt_exit: dq i_exit
i_exit:
  mov pc, [rstack]
  add rstack, 8
  jmp next

; Take a buffer pointer from stack. Read a word from input and store it starting
; in the given buffer.
xt_word: dq i_word
i_word:
  pop rdi
  call read_word
  push rdx
  jmp next

; Take a pointer to a string from the stack and print it.
xt_prints: dq i_prints
i_prints:
  pop rdi
  call print_string
  jmp next

; Exit program
xt_bye: dq i_bye
i_bye:
  mov rax, 60
  xor rdi, rdi
  syscall

; Load the predefined buffer address.
xt_inbuf: dq i_inbuf
i_inbuf:
  push qword input_buf
  jmp next

; This is a colon word, it stores execution tokens. Each token corresponds to a
; Forth word to be executed.
xt_main: dq i_docol
  dq xt_inbuf
  dq xt_word
  dq xt_drop
  dq xt_inbuf
  dq xt_prints
  dq xt_bye

; The inner interpreter. This fetches the next instruction and starts its
; execution.
next:
  mov w, [pc]
  add pc, 8
  jmp [w]

; The program starts execution from the init word.
_start: jmp i_init
