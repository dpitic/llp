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
