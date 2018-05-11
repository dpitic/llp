; This code snippet demonstrates a sample dictionary. It contains two native
; words (starting at w_plus and w_dup) and a colon word (w_double). A dictionary
; is part of a Forth machine that stores word definitions. Each word is a header
; followed by a sequence of other words. The header stores the link to the
; previous word, the word name as a null-terminated string, and some flags. The
; implementation technique used here for Forth words is called indirect threaded
; code, which requires two special cells (called Forth registers):
; pc command pointer that points to the next Forth command. A Forth command is
;    an address of an address of the respective word's assembly implementation
;    code. This is a pointer to an executable assembly code with two levels of
;    indirection.
; w  word pointer is used in non-native words. When the word starts its
;    execution, this register points at its first word.
; These two registers can be implemented using real registers, or their
; contents can be stored in memory.
; Forth words consist of three types of words:
; 1. Integer words are integers pushed onto the data stack.
; 2. Native words are written in assembly. Every native word implementation ends
;    with the instruction jmp next, which ensures the next instruction will be
;    fetched.
; 3. Colon words are written in Forth as a sequence of other Forth words, e.g.
;    : sq dup * ;
;    The return stack is necessary to be able to return from the colon words.

section .data
w_plus:                         ; Forth word definition label (native word)
	dq 0                          ; first word's pointer to the previous word is 0
  db '+', 0                     ; Forth word name (null-terminated string)
  db 0                          ; no flags
xt_plus:                        ; execution token for 'plus', equal to address
  dq plus_impl                  ; of its implementation

w_dup:                          ; native word definition for 'dup'
  dq w_plus                     ; pointer to previous word
  db 'dup', 0                   ; word name
  db 0                          ; flags (none)
xt_dup:                         ; execution token for word is the address of
  db dup_impl                   ; its implementation

w_double:                       ; colon word definition for 'double'
  dq w_dup                      ; pointer to previous word
  db 'double', 0                ; word name
  db 0                          ; flags (none)
  dq docol                      ; 'docol' address -- one level of indirection
  dq xt_dup                     ; address of word 'dup'
  dq xt_plus
  dq xt_exit

last_word: dq w_double          ; last dictionary word

section .text                   ; machine instructions

plus_impl:                      ; '+' native word implementation
  pop rax
  add rax, [rsp]
  mov [rsp], rax
  jmp next                      ; fetch next instruction

dup_impl:                       ; 'dup' native word implementation
  push qword [rsp]
  jmp next                      ; fetch next instruction

; The core of the Forth engine is the inner interpreter. It is a simple assembly
; routine fetching code from memory.
; 1. It reads memory starting at pc and sets up pc for the next instruction,
;    where pc points to a memory cell which stores the execution token for a
;    word.
; 2. It sets up w to the execution token value. After next is executed, w stores
;    the address of a pointer to assembly implementation of the word.
; 3. Jumps to the implementation code.
next:
  mov w, pc                     ; store command pointer (cell size is 8 bytes)
  add pc, 8                     ; set command pointer to next instruction
  mov w, [w]                    ; read memory contents starting at address of pc
  jmp [w]                       ; jump to implementation code

; To implement colon words, we need to use a return stack in order to save and
; restore pc before and after a call. While w is not useful when executing
; native words, it is important for the colon words.
docol:                          ; implementation of all colon words
  sub rstack, 8                 ; allocate space for return stack
  mov [rstack], pc              ; save pc in return stack
  add w, 8                      ; cell size is 8 bytes
  mov pc, w                     ; pc = first execution token inside current word
  jmp next

exit:                           ; word designed to end all colon words
  mov pc, [rstack]              ; restore pc from stack
  add rstack, 8
  jmp next
