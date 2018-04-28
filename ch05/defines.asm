; This code snippet demonstrates macro substitution evaluation order of
; %define, %xdefine and %assign.

; %define is used for dererred substitution. If a macro body contains other
; macros, they will be expanded after the substitution. The value may change
; between instantiations if parts of it were redefined.
%define i 1

%define d i * 3

; %xdefine performs substitutions when being defined. The resulting string will
; be used in substitutions.
%xdefine xd i * 3

; %assign behaves like %xdefine, but also forces the evaluation of arithmetic
; expressions and thrown an error if the computation result is not a number.
%assign a i * 3

  mov rax, d                    ; mov rax, 1 * 3
  mov rax, xd                   ; mov rax, 1 * 3
  mov rax, a                    ; mov rax, 3

; Redefining i
%define i 100

  mov rax, d                    ; mov rax, 100 * 3
  mov rax, xd                   ; mov rax, 1 * 3
  mov rax, a                    ; mov rax, 3
