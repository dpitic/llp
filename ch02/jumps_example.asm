; This snippet demonstrates order of execution. It writes 1 in rbx if
; rax < 42, and 0 otherwise.

	cmp		rax, 42
	jl		yes
	mov		rbx, 0
	jmp		ex
yes:
	mov		rbx, 1
ex:

; A common and fast way to test register value for being zero
	test	rax, rax

; There are at least two commands for each arithmetic flag F: jF and jnF
; For example, sign flag: js and jns

; Comparison of unsigned numbers with cmp
	ja		label		; jump if above
	jb		label		; jump if below

	jae		label		; jump if above or equal

; Comparison for signed numbers with cmp
	jg		label		; jump if greater
	jl		label		; jump if less

	jle		label		; jump if less or equal
