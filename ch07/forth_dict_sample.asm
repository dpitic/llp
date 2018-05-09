; This code snippet demonstrates a sample dictionary. It contains two native
; words (starting at w_plus and w_dup) and a colon word (w_sq).
; pc points to the next Forth command. A Forth command is an address of an
; address of the respective word's assembly implementation code. This is a
; pointer to an executable assembly code with two levels of indirection.
; w is used in non-native words. When the word starts its execution, this
; register points at its firs word.
; These two registers can be implemented using real registers, or their
; contents can be stored in memory.

section .data
w_plus:
	dq 0                          ; first word's pointer to the previous word is 0
  db '+', 0
  db 0                          ; no flags
xt_plus:                        ; execution token for 'plus', equal to address
  dq plus_impl                  ; of its implementation

w_dup:
  dq w_plus                     ; pointer to previous word
  db 'dup', 0
  db 0
xt_dup:
  db dup_impl

w_double:
  dq w_dup
  db 'double', 0
  db 0
  dq docol                      ; 'docol' address -- one level of indirection
  dq xt_dup                     ; address of word 'dup'
  dq xt_plus
  dq xt_exit

last_word: dq w_double
section .text
plus_impl:
  pop rax
  add rax, [rsp]
  mov [rsp], rax
  jmp next

dup_impl:
  push qword [rsp]
  jmp next

; The core of the Forth engine is the inner interpreter. It is a simple assembly
; routine fetching code from memory.
; 1. It reads memory starting at pc and sets up pc for the next instruction,
;    where pc points to a memory cell which stores the execution token for a
;    word.
; 2. It sets up w to the execution token value. After next is executed, w stores
;    the address of a pointer to assembly implementation of the word.
; 3. Jumps to the implementation code.
next:
  mov w, pc
  add pc, 8                     ; cell size is 8 bytes
  mov w, [w]
  jmp [w]

; To implement colon words, we need to use a return stack in order to save and
; restore pc before and after a call. While w is not useful when executing
; native words, it is important for the colon words.
docol:
  sub rstack, 8
  mov [rstack], pc
  add w, 8                      ; cell size is 8 bytes
  mov pc, w
  jmp next

exit:
  mov pc, [rstack]
  add rstack, 8
  jmp next
