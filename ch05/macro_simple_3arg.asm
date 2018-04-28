; This code snippet demonstrates multi line macro definition.
; Parameters indexed starting at 1.

%macro test 3                   ; 3 parameters
  dq %1                         ; %1 is first parameter
  dq %2                         ; %2 is second parameter, %n is nth parameter
  dq %3
%endmacro

; Example usage:
  test 666, 555, 444
