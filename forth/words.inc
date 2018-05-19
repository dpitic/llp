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
  jmp next                      ; fetch next instruction

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
  jmp next                      ; fetch next instruction

;;
;; @brief      Duplicate the topmost element on the stack.
;;
;; @details    ( a -- a a )
;;
native "dup", dup
  push qword [rsp]              ; push memory contents of stack onto stack
  jmp next                      ; fetch next instruction

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
  jmp next                      ; fetch next instruction

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
  jmp next                      ; fetch next instruction

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
  jmp next                      ; fetch next instruction

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
  jmp next                      ; fetch next instruction

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
  jmp next                      ; fetch next instruction

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
  jmp next                      ; fetch next instruction

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
  pop rax                       ; pop element from stack
  test rax, rax                 ; test if element is zero
  setz al                       ; if 0, then make al = 1
  movzx rax, al
  push rax                      ; push result onto stack
  jmp next                      ; fetch next instruction

;;
;; @brief      Test the equality of the two topmost stack elements.
;;
;; @details    ( a b -- c )
;;
;; @return     c = 1 if a == b
;;             c = 0 if a != b
;;
native "=", equals
  pop rax                       ; b
  pop rdx                       ; a
  cmp rax, rdx
  sete al                       ; al = 1 if a == b
  movzx rax, al
  push rax                      ; push result onto stack
  jmp next                      ; fetch next instruction

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
  pop rdi                       ; pointer to string at TOS
  call string_length            ; rax = length of string
  push rax                      ; push length of string onto stack
  jmp next                      ; fetch next instruction

;;
;; @brief      Pop number element from stack and output it to stdout.
;;
;; @details    Remove the topmost string element from the stack and output it
;;             to stdout as an integer, followed by newline.
;;
;; @param      Topmost string element on stack representing an integer.
;;
native ".", dot
  pop rdi                       ; pop topmost element from stack (string)
  call print_int
  call print_newline
  jmp next                      ; fetch next instruction

;;
;; @brief      Print all stack contents.
;;
;; @details    Print all stack contents without modifying the stack followed by
;;             newline character.
;;
;; @param      Stack integer elements.
;;
native ".S", show_stack
  mov rcx, rsp                  ; use rcx as stack index
.loop:
  cmp rcx, [stack_base]         ; check if reached stack base
  jae next                      ; reached stack base, nothing else to output
                                ; fetch next instruction
  mov rdi, [rcx]
  push rcx
  call print_int                ; print contents of stack top element
  call print_newline
  pop rcx
  add rcx, 8                    ; move to stack index to next element
  jmp .loop

section .rodata                 ; read only data
; This is the Forthress program execution token
interpreter_stub: dq xt_interpreter

;;
;; @brief      Store the data stack base.
;;
section .data                   ; initialised global variables
stack_base: dq 0
native "init", init
  mov qword [state], 0          ; set state to interpreter mode (0)
  mov rstack, rstack_start      ; initialise return stack
  mov pc, interpreter_stub      ; initialise command pointer to interpreter
                                ; entry point
  cmp qword [stack_base], 0     ; check if there is anything on the stack
  je .first                     ; nothing on stack
  mov rsp, [stack_base]         ; copy contents of stack base
  jmp next                      ; fetch next instruction
.first:
  mov [stack_base], rsp
  jmp next                      ; fetch next instruction

;;
;; @brief      Implementation of any colon word.
;;
;; @details    This is the implementation of any colon word. The execution token
;;             is not used, but the implementation (i_docol) is. Together with
;;             the exit word, docol is used to implement call/ret behaviour.
;;
native "docol", docol
  rpush pc                      ; save command pointer on return stack
  add w, 8                      ; cell size 8 bytes
  mov pc, w                     ; pc = first execution token inside current word
  jmp next                      ; fetch next instruction

;;
;; @brief      Exit from colon word.
;;
;; @details    This word is designed to end all colon words. Together with
;;             docol, it is used to implement call/ret behaviour.
;;
native "exit", exit
  rpop pc                       ; restore command pointer from return stack
  jmp next                      ; fetch next instruction

;;
;; @brief      Pop element from data stack and push onto return stack.
;;
native ">r", to_r
  pop rax                       ; pop element from stack
  rpush rax                     ; push element onto return stack
  jmp next                      ; fetch next instruction

;;
;; @brief      Pop element from return stack and push onto data stack.
;;
native "r>", from_r
  rpop rax                      ; pop element from return stack
  push rax                      ; push element onto data stack
  jmp next                      ; fetch next instruction

;;
;; @brief      Copy topmost element from return stack and push onto data stack.
;;
;; @details    Non-destructive copy that fetches the topmost element from the
;;             return stack and pushes it onto the data stack.
;;
native "r@", r_fetch
  push qword [rstack]           ; push contents of return stack onto data stack
  jmp next                      ; fetch next instruction

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
;; @return     Address of the word header in the dictionary on the stack.
;;
native "find", find
  mov rsi, [last_word]          ; rsi = dictionary word pointer
.loop:
  mov rdi, [rsp]                ; rdi = pointer to word on stack
  push rsi
  add rsi, 9
  call string_equals            ; rax = 1 if equal, 0 otherwise
  pop rsi
  test rax, rax
  jnz .found

  mov rsi, [rsi]
  test rsi, rsi                 ; check if end of dictionary
  jnz .loop
.not_found:
  mov qword [rsp], 0
  push 0
  jmp next
.found:
  mov [rsp], rsi                ; write address of word header on the stack
  jmp next                      ; fetch next instruction

;;
;; @brief      Code from address.
;;
;; @details    Convert word header start address to the execution token.
;;
;; @param      Address of word at top of stack.
;;
;; @return     Execution token for the word.
;;
native "cfa", cfa
  pop rsi                       ; word header address
  add rsi, 9                    ; skip to execution token
.loop:                          ; find word null terminator
  mov al, [rsi]
  test al, al
  jz .end                       ; found word terminator
  inc rsi
  jmp .loop

.end:
  add rsi, 2                    ; skip null terminator and flag
  push rsi                      ; address of word execution token
  jmp next                      ; fetch next instruction

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
  pop rdi                       ; address of string to print
  call print_char
  jmp next                      ; fetch next instruction

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
  jmp next                      ; fetch next instruction

;;
;; @brief      Parse string as integer.
;;
;; @details    Pop the string from the top of the stack and parse its value as
;;             an integer, returning the number and length.
;;             ( str -- num len )
;;
;; @param      Null-terminated string representing an integer.
;;
;; @return     Numerical value as integer and length of string on data stack.
;;
native "number", number
  pop rdi                       ; pop string from data stack
  call parse_int                ; rax = integer value
  push rax                      ; push number onto data stack
  push rdx                      ; push length of string onto data stack
  jmp next                      ; fetch next instruction

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
  pop rdi                       ; pop string element from data stack
  call print_string
  jmp next                      ; fetch next instruction

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
  push rax                      ; push syscall return value onto data stack
  jmp next                      ; fetch next instruction

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
  add pc, 8                     ; increment command pointer to next cell
  jmp next                      ; fetch next instruction

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
  pop rax                       ; pop topmost element from stack
  test rax, rax                 ; check if topmost element is zero
  jnz .skip                     ; TOS != 0
  add pc, [pc]                  ; TOS = 0: add pc contents to pc address
.skip:
  add pc, 8                     ; advance command pointer to next cell
  jmp next                      ; fetch next instruction

;;
;; @brief      Push a value immediately following this execution token.
;;
;; @details    lit <value>
;;             Read the next integer that the command pointer points to and
;;             advance pc by one cell so that pc will never point at the
;;             embedded operand.
;;
;; @param      Value to push.
;;
native "lit", lit
  push qword [pc]               ; push command pointer contents on stack
  add pc, 8                     ; advance command pointer by one cell
  jmp next                      ; fetch next instruction

; Address of the input buffer (used by interpreter/compiler)
const inbuf, input_buf

; Address of user memory. This word pushes the memory starting address of the
; user memory allocation onto the top of the stack.
const mem, user_mem

; Last word address
const last_word, last_word

; State call address.
; The state cell stores either 1 (compilation mode) or 0 (interpreter mode)
const state, state

; here points to the last cell of the word currently being defined. It stores
; the address of the current position to write words in compile mode. Each
; write advances here by one cell.
const here, [here]

;;
;; @brief      Execute word with this execution token on TOS.
;;
;; @details    ( xt -- )
;;
;; @param      Execution token.
;;
native "execute", execute
  pop rax                       ; pop execution token from data stack
  mov w, rax
  jmp [rax]                     ; jump to execution token

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
  pop rax                       ; pop address from stack
  push qword [rax]              ; push memory contents of address on stack
  jmp next                      ; fetch next instruction

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
  mov [rdx], rax                ; write value into memory contents of address
  jmp next                      ; fetch next instruction

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
  pop rax                       ; pop address from stack
  movzx rax, byte [rax]         ; read one byte of memory contents from address
  push rax                      ; push the byte read onto stack
  jmp next                      ; fetch next instruction

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
  pop rdi                       ; pop source string from stack
  push rsi                      ; rsi will be modified by str_cpy
  call str_cpy                  ; rsi = ptr. to destination string buffer
  pop rsi                       ; restore rsi
  push rsi                      ; rsi is caller-saved register
  mov rdi, rsi                  ; rdi = pointer to null terminated string
  call string_length            ; rax = length of string (word)
  pop rsi                       ; restore rsi
  add rsi, rax                  ; add length of word (string)

  ; flags
  inc rsi
  pop rax
  mov [rsi], al
  inc rsi

  mov [here], rsi
  jmp next                      ; fetch next instruction

;;
;; @brief      Read word from stdin and start defining it.
;;
;; @details    Causes Forth to switch into compiler mode. It reads the next
;;             word and uses it to create a new entry in the dictionary with
;;             docol as its implementation. It then reads words, finds them in
;;             the dictionary, and adds them to the current word being defined.
;;
colon ":", colon
.restart:
  dq xt_inbuf, xt_word          ; read word from stack
  branch0 .restart              ; restart if TOS is 0
  dq xt_lit, 0, xt_inbuf, xt_create
  dq xt_state, xt_lit, 1, xt_write
  dq xt_lit, i_docol, xt_comma
  dq xt_exit

;;
;; @brief      End the current word definition.
;;
;; @details    This is an immediate word used to quit compiler mode.
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
  dq xt_inbuf, xt_word          ; read word from stack
  branch0 .end_of_input         ; if word is empty, then exit

  dq xt_inbuf, xt_find          ; find word in dictionary (word address on stack)

  dq xt_dup                     ; word address on stack
  branch0 .number               ; if not found, try to parse as a number
  dq xt_cfa                     ; get execution token from word address on stack

  ; if compile
  dq xt_state, xt_fetch
  branch0 .interpreting

  ; if is immediate
  dq xt_dup                     ; push number on stack
  dq xt_lit, 1, xt_minus, xt_fetch_char, xt_not
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
