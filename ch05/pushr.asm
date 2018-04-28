; This code snippet demonstrates the %ifidn preprocessor directive, which is
; used to test if two strings are identical. The macro defined here works like
; the push assembly instruction, but also accepts rip and rflags registers.
; %ifidn => if identical (case sensitive, %ifidni case insensitive)

%macro pushr 1
	%ifidn %1, rflags             ; check if %1 == 'rflags'
		pushf
	%else
		push %1
	%endif
%endmacro

; Example usage of the macro
	push rax                      ; push rax
	pushr rflags                  ; pushf
