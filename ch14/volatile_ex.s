	.file	"volatile_ex.c"
	.intel_syntax noprefix
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	sub	rsp, 24
	.cfi_def_cfa_offset 32
	mov	esi, 1
	lea	rdi, .LC0[rip]
	mov	DWORD PTR 12[rsp], 4
	mov	eax, DWORD PTR 12[rsp]
	add	eax, 1
	mov	DWORD PTR 12[rsp], eax
	xor	eax, eax
	call	printf@PLT
	mov	esi, DWORD PTR 12[rsp]
	lea	rdi, .LC0[rip]
	xor	eax, eax
	call	printf@PLT
	xor	eax, eax
	add	rsp, 24
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (GNU) 8.1.0"
	.section	.note.GNU-stack,"",@progbits
