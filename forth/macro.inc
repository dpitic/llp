;;
;; Forth macro definitions.
;;
%ifndef _MACRO_INC_
%define _MACRO_INC_

%define _lw 0                   ; pointer to previous word initialised to null 

;;
;; @brief      Define a native word.
;;
;; @details    This macro accepts three arguments and defines a native Forth. It
;;             fills in the header in .data and the execution token label in
;;             .text, which denotes the assembly code following the macro
;;             instance.
;;
;; @param      %1  Forth native word name as string constant.
;; @param      %2  Suffix part of the word identifier in wh_, xt_ and i_ labels.
;; @param      %3  Flags.
;;
%macro native 3
  section .data
  wh_ %+ %2:                    ; Forth word definition label (native word)
  dq _lw                        ; pointer to previous word
  %define _lw wh_ %+ %2         ; update previous word pointer to this word label
  db 0                          ; mark the name start
  db %1, 0                      ; word name
  db %3                         ; flags

  xt_ %+ %2:                    ; execution token for word, equal to address of
  dq i_ %+ %2                   ; its implementation
  section .text
  i_ %+ %2:                     ; word implementation label
;  %define _lw wh_%+ %2          ; previous word pointer in .text section set to
                                ; this word
%endmacro

;;
;; @brief      Define a native word with no flags.
;;
;; @details    This macro overloads the native macro to create a native Forth
;;             word with no flags.
;;
;; @param      %1  Forth native word name as string constant.
;; @param      %2  Part of the word identifier.
;;
%macro native 2
  native %1, %2, 0
%endmacro

;;
;; @brief      Define a Forth colon word.
;;
;; @details    This macro accepts three arguments and defines a Forth colon
;;             word.
;;
;; @param      %1  Forth colon word name as string constant.
;; @param      %2  Part of the word identifier.
;; @param      %3  Flags.
;;
%macro colon 3
  section .data
  wh_ %+ %2:                    ; Forth colon word definition label
  dq _lw                        ; pointer to previous word
  %define _lw wh_ %+ %2         ; update previous word pointer to this word label
  db 0                          ; make the name start
  db %1, 0                      ; word name
  db %3                         ; flags

  xt_ %+ %2:                    ; execution token for colon word, equal to
  dq i_docol                    ; address of docol implementation
%endmacro

;;
;; @brief      Define a Forth colon word with no flags.
;;
;; @details    This macro overloads the colon macro to define a Forth colon
;;             word that has no flags.
;;
;; @param      %1  Forth colon word name as string constant.
;; @param      %2  Part of the word identifier.
;;
%macro colon 2
  colon %1, %2, 0
%endmacro

;;
;; @brief      Push operand onto the return stack.
;;
;; @details    This macro allocates an 8 byte cell on the return stack and
;;             pushes the operand onto the return stack.
;;
;; @param      %1  Value to push onto the return stack.
;;
%macro rpush 1
  sub rstack, 8                 ; 8 byte cell size
  mov qword [rstack], %1
%endmacro

;;
;; @brief      Pop value from return stack into the operand.
;;
;; @details    This macro pops the value in the return stack and saves it into
;;             the operand. It removes the 8 byte cell memory from the return
;;             stack.
;;
;; @param      %1  Register into which the value from the rstack should be
;;                 copied into.
;;
%macro rpop 1
  mov %1, qword [rstack]
  add rstack, 8
%endmacro

%macro const 2
  %defstr %%__cnst_str %1
  native %%__cnst_str, %1
  push qword %2
  jmp next
%endmacro

;;
;; @brief      Jump to a location relative to the argument end.
;;
;; @details    Jump to a location that is an offset relative to the argument
;;             end.
;;
;; @param      %1  Offset relative to the argument end.
;;
%macro branch 1
  dq xt_branch
  dq %1 - $ - 8
%endmacro

;;
;; @brief      Jump to a location relative to the argument end.
;;
;; @details    Jump to a location if top of stack = 0.
;;
;; @param      %1  Offset relative to the argument end.
;;
%macro branch0 1
  dq xt_branch0
  dq %1 - $ - 8
%endmacro

%endif                          ; _MACRO_INC_
