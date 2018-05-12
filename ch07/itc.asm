; This program uses indirect threaded code to implement words in Forth. It uses
; the I/O library routines. The program reads a word from input and outputs it
; back to stdout.

extern read_word
extern print_string

global _start

; Forth registers are implemented in callee-saved registers so they are
; guaranteed to survive function calls unchanged.
%define pc r15                  ; pointer to memory cell that stores execution
                                ; token of a word.
%define w r14                   ; pointer to first word when word starts its
                                ; execution.
%define rstack r13              ; return stack used to save and restore pc
                                ; before and after a call.

section .bss                    ; read/write global variables
  resq 1023
rstack_start: resq 1
input_buf: resb 1024

section .text                   ; machine instructions

main_stub: dq xt_main           ; this one cell is the program

; The dictionary starts here. Each word stores the address of its assembly
; implementation.

; Drop the topmost element from the stack
w_drop:                         ; 'drop' native word header definition
  dq 0                          ; there is no previous node
  db "drop", 0                  ; Forth word name
  db 0                          ; flags
xt_drop: dq i_drop              ; execution token (address of implementation)
i_drop:                         ; word implementation
  add rsp, 8
  jmp next                      ; fetch next instruction

; Initialise registers
w_init:                         ; 'init' native word
  dq w_drop                     ; pointer to previous word
  db "init", 0                  ; Forth word name
  db 0                          ; flags (none)
xt_init: dq i_init              ; execution token (address of implementation)
i_init:                         ; word implementation
  mov rstack, rstack_start
  mov pc, main_stub
  jmp next                      ; fetch next instruction

; Save pc when the colon word starts. Implementation of all colon words.
w_docol:                        ; 'docol' native word
  dq w_init                     ; pointer to previous word
  db "docol", 0                 ; Forth word name
  db 0                          ; flags (none)
xt_docol: dq i_docol            ; execution token
i_docol:                        ; word implementation
  sub rstack, 8                 ; allocate space for return stack
  mov [rstack], pc              ; save pc in return stack
  add w, 8                      ; cell size is 8 bytes
  mov pc, w                     ; pc = first execution token inside current word
  jmp next                      ; fetch next instruction

; Return from the colon word, designed to end all colon words.
w_exit:                         ; 'exit' native word
  dq w_docol                    ; pointer to previous word
  db "exit", 0                  ; Forth word name
  db 0                          ; flags (none)
xt_exit: dq i_exit              ; execution token
i_exit:                         ; word implementation
  mov pc, [rstack]              ; restore pc from stack
  add rstack, 8
  jmp next                      ; fetch next instruction

; Take a buffer pointer from stack. Read a word from input and store it starting
; in the given buffer.
w_word:                         ; 'word' native word
  dq w_exit                     ; pointer to previous word
  db "word", 0                  ; Forth word name
  db 0                          ; flags (none)
xt_word: dq i_word              ; execution token
i_word:                         ; word implementation
  pop rdi
  call read_word
  push rdx
  jmp next                      ; fetch next instruction

; Take a pointer to a string from the stack and print it.
w_prints:                       ; 'prints' native word
  dq w_word                     ; pointer to previous word
  db "prints", 0                ; Forth word name
  db 0                          ; flags (none)
xt_prints: dq i_prints          ; execution token
i_prints:                       ; word implementation
  pop rdi
  call print_string
  jmp next                      ; fetch next instruction

; Exit program
w_bye:                          ; 'bye' native word
  dq w_prints                   ; pointer to previous word
  db "bye", 0                   ; Forth word name
  db 0                          ; flags (none)
xt_bye: dq i_bye                ; execution token
i_bye:                          ; word implementation
  mov rax, 60                   ; exit() syscall identifier
  xor rdi, rdi                  ; 0 exit status
  syscall

; Load the predefined buffer address.
w_inbuf:                        ; 'inbuf' word
  dq w_bye                      ; pointer to previous word
  db "inbuf", 0                 ; Forth word name
  db 0                          ; flags (none)
xt_inbuf: dq i_inbuf            ; execution token
i_inbuf:                        ; word implementation
  push qword input_buf
  jmp next                      ; fetch next instruction

; This is a colon word, it stores execution tokens. Each token corresponds to a
; Forth word to be executed.
w_main:                         ; colon word 'main'
  dq w_bye                      ; pointer to previous word
  db "main", 0                  ; Forth word name
  db 0                          ; flags (none)
xt_main: dq i_docol             ; execution token
  dq xt_inbuf
  dq xt_word
  dq xt_drop
  dq xt_inbuf
  dq xt_prints
  dq xt_bye

; The inner interpreter. This fetches the next instruction and starts its
; execution.
next:
  mov w, [pc]                   ; read memory contents starting at address of pc
  add pc, 8                     ; set command pointer to next instruction
  jmp [w]                       ; jump to implementation code

; The program starts execution from the init word.
_start: jmp i_init
