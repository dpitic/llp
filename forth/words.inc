;;------------------------------------------------------------------------------
; Forthress - a Forth dialect. This file defines the Forth words. The stack
; diagrams show the effect of the words ( before -- after ) on the stack. This
; file is intended to be included in the Forth compiler or interpreter
; implementation. It uses macros defined in a separate include file to define
; the native and colon Forth words.
;;------------------------------------------------------------------------------

;;
;; @brief      Drop value from top of stack.
;;
;; @details    ( a -- )
;;
native "drop", drop
  add rsp, 8
  jmp next

;;
;; @brief      Swap top two elements on the stack
;;
;; @details    ( a b -- b a )
;;
native "swap", swap
  pop rax
  pop rdx
  push rax
  push rdx
  jmp next

;;
;; @brief      Duplicate the topmost element on the stack.
;;
;; @details    ( a -- a a )
;;
native "dup", dup
  push qword [rsp]
  jmp next

;;
;; @brief      Rotate top 3 elements on the stack.
;;
;; @details    This word rotates the top 3 elements on the stack so that the
;;             bottom element becomes the topmost element.
;;             ( a b c -- b c a )
;;
native "rot", rot
  pop rcx
  pop rdx
  pop rax
  push rdx
  push rcx
  push rax
  jmp next

;;
;; @brief      Add topmost two elements on the stack.
;;
;; @details    ( y x -- [ x + y] )
;;
;; @return     Value on the stack is the sum of the topmost two elements.
;;
native "+", plus
  pop rax
  add [rsp], rax
  jmp next

;;
;; @brief      Multiply topmost two elements on the stack.
;;
;; @details    ( y x -- [ x * y ] )
;;
;; @param      Operands are integers.
;;
;; @return     Value on the stack is the product of the topmost two elements.
;;
native "*", mul
  pop rax
  pop rdx
  imul rdx
  push rax
  jmp next

;;
;; @brief      Divide topmost element by the next element.
;;
;; @details    ( y x -- [ x / y] )
;;
;; @param      Operands are integers.
;;
;; @return     Result of division is returned on the stack.
;;
native "/", div
  pop rcx
  pop rax
  cqo
  idiv rcx
  push rax
  jmp next

;;
;; @brief      Modulo operator returns the remainder after division of topmost
;;             stack element by next element.
;;
;; @details    ( y x -- [ x mod y] )
;;
;; @param      Operands are integers.
;;
;; @return     Remainder after division.
;;
native "%", mod
  pop rcx
  pop rax
  cqo
  idiv rcx
  push rdx
  jmp next

;;
;; @brief      Subtraction operator returns the arithmetic difference between
;;             the topmost stack element and the next element.
;;
;; @details    ( y x -- [ x - y ] )
;;
;; @param      Operands are integers.
;;
;; @return     Arithmetic difference between topmost stack element and next
;;             element.
;;
native "-", minus
  pop rax
  sub [rsp], rax
  jmp next

;;
;; @brief      Logical not operation.
;;
;; @details    ( a -- a' )
;;
;; @return     Logical not of the operand at the top of the stack.
;;             a' = 0 if a != 0
;;             a' = 1 if a == 0
;;
natiave "not", not
  pop rax
  test rax, rax
  setz al
  movzx rax, al
  push rax
  jmp next

;;
;; @brief      Test the equality of the two topmost stack elements.
;;
;; @details    ( a b -- c )
;;
;; @return     c = 1 if a == b
;;             c = 0 if a != b
;;
native "=", equals
  pop rax
  pop rdx
  cmp rax, rdx
  sete al
  movzx rax, al
  push rax
  jmp next

;;
;; @brief      Length of null-terminated string.
;;
;; @details    ( str -- len )
;;
;; @param      Null-terminated string.
;;
;; @return     Length of null-terminated string.
;;
native "count", count
  pop rdi
  call string_length
  push rax
  jmp next

;;
;; @brief      Pop element from stack and output it to stdout.
;;
;; @details    Remove the topmost integer element from the stack and output it
;;             to stdout, followed by newline.
;;
;; @param      Topmost integer element on stack.
;;
native ".", dot
  pop rdi
  call print_int
  call print_newline
  jmp next

;;
;; @brief      Print all stack contents.
;;
;; @details    Print all stack contents without modifying the stack followed by
;;             newline character.
;;
;; @param      Stack integer elements.
;;
native ".S", show_stack
  mov rcx, rsp
.loop:
  cmp rcx, [stack_base]
  jae next
  mov rdi, [rcx]
  push rcx
  call print_int
  call print_newline
  pop rcx
  add rcx, 8
  jmp .loop

  section .rodata
interpreter_stub: dq xt_interpreter

;;
;; @brief      function description
;;
;; @details    Detailed description
;;
;; @param      param
;;
;; @return     return
;;
section .data
stack_base: dq 0
native "init", init
  mov qword [state], 0
  mov rstack, rstack_start
  mov pc, interpreter_stub
  cmp qword [stack_base], 0
  je .first
  mov rsp, [stack_base]
  jmp next
.first:
  mov [stack_base], rsp
  jmp next

;;
;; @brief      Implementation of any colon word.
;;
;; @details    This is the implementation of any colon word. The execution token
;;             is not used, but the implementation (i_docol) is.
;;
native "docol", docol
  rpush pc
  add w, 8
  mov pc, w
  jmp next

;;
;; @brief      Exit from colon word.
;;
native "exit", exit
  rpop pc
  jmp next

;;
;; @brief      Pop element from data stack and push onto return stack.
;;
native ">r", to_r
  pop rax
  rpush rax
  jmp next

;;
;; @brief      Pop element from return stack and push onto data stack.
;;
native "r>", from_r
  rpop rax
  push rax
  jmp next

;;
;; @brief      Copy topmost element from return stack and push onto data stack.
;;
;; @details    Non-destructive copy that fetches the topmost element from the
;;             return stack and pushes it onto the data stack.
;;
native "r@", r_fetch
  push qword [rstack]
  jmp next

colon "constant", constant

;;
;; @brief      Find the given word in the Forth dictionary.
;;
;; @details    Accepts a pointer to a string representing a Forth word, and
;;             returns the pointer to the word header in the dictionary.
;;             ( str -- header address )
;;
;; @param      Pointer to a string representing a Forth word.
;;
;; @return     Address of the word header in the dictionary.
;;
native "find", find
  mov rsi, [last_word]
.loop:
  mov rdi, [rsp]
  push rsi
  add rsi, 9
  call string_equals
  pop rsi
  test rax, rax
  jnz .found

  mov rsi, [rsi]
  test rsi, rsi
  jnz .loop
.not_found:
  mov qword [rsp], 0
  push 0
  jmp next
.found:
  mov [rsp], rsi
  jmp next

;;
;; @brief      Convert word header start address to the execution token.
;;
;; @param      Address of word at top of stack.
;;
;; @return     Execution token for the word.
;;
native "cfa", cfa
  pop rsi
  add rsi, 9
.loop:
  mov al, [rsi]
  test al, al
  jz .end
  inc rsi
  jmp .loop

.end:
  add rsi, 2
  push rsi
  jmp next

;;
;; @brief      Output a single character from the stack to stdout.
;;
;; @details    This function pops the topmost character from the stack and
;;             outputs it to stdout.
;;             ( c -- )
;;
;; @param      Character element at the top of the stack.
;;
native "emit", emit
  pop rdi
  call print_char
  jmp next

;;
;; @brief      Read a word from stdin and store it starting at the given address.
;;
;; @details    Given the storage address on the stack, read a word from stdin
;;             and store it starting at the given address.
;;             ( addr -- len )
;;
;; @param      Address to store the word read from stdin.
;;
;; @return     Length of the word read from stdin is pushed onto the stack.
;;
native "word", word
  pop rdi
  call read_word
  push rdx
  jmp next

;;
;; @brief      Parse string as integer.
;;
;; @details    Pop the string from the top of the stack and parse its value as
;;             an integer, returning the number and length.
;;             ( str -- len num )
;;
;; @param      Null-terminated string representing an integer.
;;
;; @return     Length of string and numerical value as integer.
;;
native "number", number
  pop rdi
  call parse_int
  push rax
  push rdx
  jmp next
