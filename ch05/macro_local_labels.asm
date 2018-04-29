; This code snippet demonstrates macro local labels, defined using %%
; prefixing the label name. This causes the macro preprocesser to generate a
; unique label for every macro instance, to ensure the label remains local to
; that macro instance.

%macro mymacro 0
%%labelname:
%%labelname:
%endmacro

mymacro

mymacro

mymacro
