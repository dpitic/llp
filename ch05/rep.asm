; This code snippet demonstrates macro loops. This differs from using the times
; directive, which is executed after all macro definitions are fully expanded
; and cannot be used to repeat pieces of macros.

%assign x 1
%assign a 0
%rep 10                         ; loop 10 times
%assign a x + a
%assign x x + 1
%endrep

result: dq a                    ; a = 55
