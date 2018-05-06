; This code snippet demonstrates the implementation of a finite state machine 
; that is used to check if a string is a number. The implementation handles 
; null-terminated strings.

section .text
extern getsymbol                ; read symbol from stdin into al

_A:                             ; initial state: transition to B, C, or E
  call getsymbol
  cmp al, '+'
  je _B
  cmp al, '-'
  je _B
  ; The indices of the digit characters in ASCII tables fill a range from
  ; '0' = 0x30 to '9' = 0x39. This logic implements the transitions to labels
  ; _E and _C.
  cmp al, '0'
  jb _E                         ; error state
  cmp al, '9'
  ja _E
  jmp _C                        ; characters ['0' .. '9']

_B:                             ; transition to C or E
  call get symbol
  cmp al, '0'
  jb _E                         ; error state
  cmp al, '9'
  ja _E
  jmp _C                        ; characters ['0' .. '9']

_C:                             ; transition to C, D (for null) or E
  call getsymbol
  cmp al, '0'
  jb _E                         ; error state
  cmp al, '9'
  ja _E
  test al, al                   ; check for null
  jz _D
  cmp _C                        ; characters ['0' .. '9']

_D:                             ; end of string (null) found
  ; Code to notify success, possibly returning 1

_E:                             ; error state
  ; Code to notify failure, possibly returning 0
