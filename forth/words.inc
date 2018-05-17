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
  add rsp, 8                    ; cell size is 8 bytes
  jmp next

;;
;; @brief      Swap top two elements on the stack
;;
;; @details    ( a b -- b a )
;;
native "swap", swap
  pop rax                       ; b
  pop rdx                       ; a
  push rax                      ; b
  push rdx                      ; a on TOS
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
  pop rcx                       ; c
  pop rdx                       ; b
  pop rax                       ; a
  push rdx                      ; b
  push rcx                      ; c
  push rax                      ; a on TOS
  jmp next

;;
;; @brief      Add topmost two elements on the stack.
;;
;; @details    ( y x -- [ x + y ] )
;;
;; @return     Value on the stack is the sum of the topmost two elements.
;;
native "+", plus
  pop rax                       ; x
  add [rsp], rax                ; y + x on TOS
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
  pop rax                       ; x
  pop rdx                       ; y
  imul rdx                      ; x * y in rax
  push rax                      ; product at TOS
  jmp next

;;
;; @brief      Arithmetic integer division.
;;
;; @details    ( x y -- [ x / y ] )
;;
;; @param      Operands are integers.
;;
;; @return     Result of division is returned on the stack.
;;
native "/", div
  pop rcx                       ; second operand is popped first (divisor): y
  pop rax                       ; dividend: x
  cqo
  idiv rcx                      ; rdx:rax / rax <=> x / y => rax
  push rax                      ; quotient in rax at TOS
  jmp next

;;
;; @brief      Modulo operator returns the remainder of division.
;;
;; @details    ( x y -- [ x mod y] )
;;
;; @param      Operands are integers.
;;
;; @return     Remainder after division.
;;
native "%", mod
  pop rcx                       ; second operand is popped first (divisor): y
  pop rax                       ; dividend: x
  cqo
  idiv rcx                      ; rdx:rax / rax <=> x / y => rdx
  push rdx                      ; remainder in rdx at TOS
  jmp next

;;
;; @brief      Subtraction operator returns the arithmetic difference between
;;             the topmost stack element and the next element.
;;
;; @details    ( x y -- [ x - y ] )
;;
;; @param      Operands are integers.
;;
;; @return     Arithmetic difference between topmost stack element and next
;;             element.
;;
native "-", minus
  pop rax                       ; second operand is popped first: y
  sub [rsp], rax                ; [rsp] - rax <=> x - y
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
native "not", not
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
  pop rdi                       ; address of string storage buffer
  mov rsi, 254                  ; size of read buffer
  call read_word
  push rdx                      ; length of word read
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

;;
;; @brief      Print a null-terminated string on stdout.
;;
;; @details    Pop the null-terminated string from the top of the stack and
;;             write it to stdout.
;;             ( addr -- )
;;
;; @param      Null-terminated string at the top of the stack.
;;
native "prints", prints
  pop rdi
  call print_string
  jmp next

;;
;; @brief      Exit Forthress.
;;
native "bye", bye
  mov rax, 60                   ; exit() syscall identifier
  xor rdi, rdi                  ; 0 exit status
  syscall

;;
;; @brief      Execute system call.
;;
;; @details    The following registers store arguments according to ABI:
;;             rdi, rsi, rdx, r10, r8, r9. The syscall return code is pushed
;;             onto the stack.
;;
;; @param      ( num a1 a2 a3 a4 a5 a6 -- rax )
;;
;; @return     Syscall return code.
;;
native "syscall", syscall
  pop r9
  pop r8
  pop r10
  pop rdx
  pop rsi
  pop rdi
  pop rax                       ; syscall identifier
  syscall
  push rax                      ; syscall return value
  jmp next

;;
;; @brief      Jump to a location, defined as an offset relative to the
;;             argument end.
;;
;; @details    branch is a compile only word. It works as shown below:
;;             |xt_branch|     24 | <next command>
;;                                 ^ adds 24 to this address and stores it in pc
;;
;; @param      Offset
;;
native "branch", branch
  add pc, [pc]
  add pc, 8
  jmp next

;;
;; @brief      Jump to a location if TOS = 0.
;;
;; @details    0branch is a compile only word. It works as shown below:
;;             |xt_branch|     24 | <next command>
;;                                 ^ adds 24 to this address and stores it in pc
;;
;; @param      Offset
;;
native "0branch", branch0
  pop rax
  test rax, rax
  jnz .skip
  add pc, [pc]
.skip:
  add pc, 8
  jmp next

;;
;; @brief      Push a value immediately following this execution token.
;;
;; @details    lit <value>
;;
;; @param      Value to push.
;;
native "lit", lit
  push qword [pc]
  add pc, 8
  jmp next

; Address of the input buffer (used by interpreter/compiler)
const inbuf, input_buf

; Address of user memory.
const mem, user_mem

; Last word address
const last_word, last_word

; State call address
; The state cell stores either 1 (compilation mode) or 0 (interpreter mode)
const state, state

; here points to the last cell of the word currently being defined.
const here, [here]

;;
;; @brief      Execute word with this execution token on TOS.
;;
;; @details    ( xt -- )
;;
;; @param      Execution token.
;;
native "execute", execute
  pop rax
  mov w, rax
  jmp [rax]

;;
;; @brief      Fetch value from memory.
;;
;; @details    ( addr -- value )
;;
;; @param      Address
;;
;; @return     Value at address.
;;
native "@", fetch
  pop rax
  push qword [rax]
  jmp next

;;
;; @brief      Store value by address.
;;
;; @details    ( addr val -- )
;;
;; @param      Value and address where to store value.
;;
native "!", write
  pop rax                       ; value
  pop rdx                       ; address
  mov [rdx], rax
  jmp next

;;
;; @brief      Read one byte starting at given address.
;;
;; @details    ( addr -- char )
;;
;; @param      Address from where to read the byte from.
;;
;; @return     Character read from the address.
;;
native "@c", fetch_char
  pop rax
  movzx rax, byte [rax]
  push rax
  jmp next

;;
;; @brief      Add operand to the word being defined.
;;
;; @details    ( x -- )
;;
;; @param      param
;;
native ",", comma
  mov rax, [here]
  pop qword [rax]
  add qword [here], 8
  jmp next

;;
;; @brief      Add a single byte to the word being defined.
;;
;; @details    ( c -- )
;;
;; @param      Byte to be added to the word being defined.
;;
native "c,", char_comma
  mov rax, [here]
  pop rdx
  mov [rax], dl
  add qword [here], 1
  jmp next

;;
;; @brief      Create an entry in the dictionary whose name is the new name.
;;
;; @details    Take flag and name and create an entry in the dictionary. Only
;;             immediate flag is implemented currently.
;;
;; @param      ( flags name -- )
;;
native "create", create
  ; link
  mov rcx, [last_word]
  mov rsi, [here]
  mov [rsi], rcx
  mov [last_word], rsi
  add rsi, 8
  mov byte [rsi], 0
  inc rsi

  ; name
  pop rdi
  push rsi
  call str_cpy
  pop rsi
  push rsi
  mov rdi, rsi
  call string_length
  pop rsi
  add rsi, rax

  ; flags
  inc rsi
  pop rax
  mov [rsi], al
  inc rsi

  mov [here], rsi
  jmp next

;;
;; @brief      Read word from stdin and start defining it.
;;
colon ":", colon
.restart:
  dq xt_inbuf, xt_word
  branch0 .restart
  dq xt_lit, 0, xt_inbuf, xt_create
  dq xt_state, xt_lit, 1, xt_write
  dq xt_lit, i_docol, xt_comma
  dq xt_exit

;;
;; @brief      End the current word definition.
;;
colon ";", semicolon, 1
  dq xt_state, xt_lit, 0, xt_write
  dq xt_lit, xt_exit, xt_comma
  dq xt_exit

;;
;; @brief      Forthress interpreter/compiler.
;;
colon "interpreter", interpreter
.start:
  dq xt_inbuf, xt_word
  branch0 .end_of_input

  dq xt_inbuf, xt_find          ; find in dictionary

  dq xt_dup
  branch0 .number               ; if not found, try to parse as a number
  dq xt_cfa

  ; if compile
  dq xt_state, xt_fetch
  branch0 .interpreting

  ; if is immediate
  dq xt_dup
  dq  xt_lit, 1, xt_minus, xt_fetch_char, xt_not
  branch0 .interpreting

  ; compile
  dq xt_comma
  branch .start

.interpreting:
  dq xt_execute
  branch .start

.number:
  dq xt_drop
  dq xt_drop
  dq xt_inbuf
  dq xt_number
  branch0 .no_word

  dq xt_state, xt_fetch         ; if interpreting, that's it
  branch0 .start

  ; When compiling, check it was after a branch
  dq xt_here, xt_lit, 8, xt_minus
  dq xt_lit, xt_branch0
  dq xt_equals, xt_not
  branch0 .is_branch

  dq xt_here, xt_lit, 8, xt_minus
  dq xt_lit, xt_branch
  dq xt_equals, xt_not
  branch0 .is_branch

  dq xt_lit, xt_lit, xt_comma

.is_branch:
  dq xt_comma

  branch .start

.no_word:
  dq xt_drop, xt_inbuf, xt_prints
  dq xt_lit, msg_no_such_word, xt_prints
  branch .start

.end_of_input:
  dq xt_bye
  dq xt_exit
