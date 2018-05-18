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
  resq 1023                     ; return stack 1024 * 8 byte cells
rstack_start: resq 1            ; starting at this address
input_buf: resb 1024            ; stack input buffer

section .text                   ; machine instructions

main_stub: dq xt_main           ; this one cell is the program entry point

; The dictionary starts here. Each word has an execution token that stores the 
; address of its assembly implementation.

; Drop the topmost element from the stack
w_drop:                         ; 'drop' native word header definition
  dq 0                          ; there is no previous node
  db "drop", 0                  ; Forth word name
  db 0                          ; flags
xt_drop: dq i_drop              ; execution token = address of implementation
i_drop:                         ; word implementation
  add rsp, 8                    ; cell size is 8 bytes
  jmp next                      ; fetch next instruction

; Initialise registers
w_init:                         ; 'init' native word
  dq w_drop                     ; pointer to previous word
  db "init", 0                  ; Forth word name
  db 0                          ; flags (none)
xt_init: dq i_init              ; execution token = address of implementation
i_init:                         ; word implementation
  mov rstack, rstack_start      ; initialise return stack pointer
  mov pc, main_stub             ; initialise command pointer to entry point
  jmp next                      ; fetch next instruction

; Save pc when the colon word starts. Implementation of all colon words.
w_docol:                        ; 'docol' native word
  dq w_init                     ; pointer to previous word
  db "docol", 0                 ; Forth word name
  db 0                          ; flags (none)
xt_docol: dq i_docol            ; execution token = address of implementation
i_docol:                        ; word implementation
  sub rstack, 8                 ; allocate space on return stack
  mov [rstack], pc              ; save pc in return stack
  add w, 8                      ; cell size is 8 bytes
  mov pc, w                     ; pc = first execution token inside current word
  jmp next                      ; fetch next instruction

; Return from the colon word, designed to end all colon words.
w_exit:                         ; 'exit' native word
  dq w_docol                    ; pointer to previous word
  db "exit", 0                  ; Forth word name
  db 0                          ; flags (none)
xt_exit: dq i_exit              ; execution token = address of implementation
i_exit:                         ; word implementation
  mov pc, [rstack]              ; restore pc from stack
  add rstack, 8                 ; drop return stack
  jmp next                      ; fetch next instruction

; Take a buffer pointer from stack. Read a word from input and store it starting
; in the given buffer.
w_word:                         ; 'word' native word
  dq w_exit                     ; pointer to previous word
  db "word", 0                  ; Forth word name
  db 0                          ; flags (none)
xt_word: dq i_word              ; execution token = address of implementation
i_word:                         ; word implementation
  pop rdi                       ; address of string storage buffer
  mov rsi, 254                  ; size of read buffer
  call read_word
  push rdx                      ; length of word read
  jmp next                      ; fetch next instruction

; Take a pointer to a string from the stack and print it.
w_prints:                       ; 'prints' native word
  dq w_word                     ; pointer to previous word
  db "prints", 0                ; Forth word name
  db 0                          ; flags (none)
xt_prints: dq i_prints          ; execution token = address of implementation
i_prints:                       ; word implementation
  pop rdi                       ; address of string to print
  call print_string
  jmp next                      ; fetch next instruction

; Exit program
w_bye:                          ; 'bye' native word
  dq w_prints                   ; pointer to previous word
  db "bye", 0                   ; Forth word name
  db 0                          ; flags (none)
xt_bye: dq i_bye                ; execution token = address of implementation
i_bye:                          ; word implementation
  mov rax, 60                   ; exit() syscall identifier
  xor rdi, rdi                  ; 0 exit status
  syscall

; Load the predefined buffer address.
w_inbuf:                        ; 'inbuf' word
  dq w_bye                      ; pointer to previous word
  db "inbuf", 0                 ; Forth word name
  db 0                          ; flags (none)
xt_inbuf: dq i_inbuf            ; execution token = address of implementation
i_inbuf:                        ; word implementation
  push qword input_buf          ; push address of input buffer on stack
  jmp next                      ; fetch next instruction

; This is a colon word, it stores execution tokens. Each token corresponds to a
; Forth word to be executed.
w_main:                         ; colon word 'main'
  dq w_bye                      ; pointer to previous word
  db "main", 0                  ; Forth word name
  db 0                          ; flags (none)
xt_main: dq i_docol             ; execution token
  dq xt_inbuf                   ; push address of input buffer on stack
  dq xt_word                    ; read word from stack
  dq xt_drop                    ; drop input word from stack
  dq xt_inbuf                   ; push address of stack buffer on stack
  dq xt_prints                  ; print word on stack
  dq xt_bye                     ; exit program

; The inner interpreter. This fetches the next instruction and starts its
; execution.
next:
  mov w, [pc]                   ; read memory contents starting at address of pc
  add pc, 8                     ; set command pointer to next instruction
  jmp [w]                       ; jump to implementation code

; The program starts execution from the init word.
_start: jmp i_init
