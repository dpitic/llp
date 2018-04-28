; This code snippet demonstrates conditional substitution in macros.

  BITS 64

%define x 5

%if x == 10
  mov rax, 100
%elif x == 15
  mov rax, 115
%elif x == 200
  mov rax, 0
%else
  mov rax, rbx                  ; this branch will be substituted (x=5)
%endif
