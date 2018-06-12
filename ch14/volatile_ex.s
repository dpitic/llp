	.file	"volatile_ex.c"
	.intel_syntax noprefix
	.text
.Ltext0:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB3:
	.file 1 "volatile_ex.c"
	.loc 1 6 16 view -0
	.cfi_startproc
	.loc 1 7 3 view .LVU1
.LVL0:
	.loc 1 8 3 view .LVU2
	.loc 1 6 16 is_stmt 0 view .LVU3
	sub	rsp, 24
	.cfi_def_cfa_offset 32
	.loc 1 11 3 view .LVU4
	mov	esi, 1
	lea	rdi, .LC0[rip]
	.loc 1 8 16 view .LVU5
	mov	DWORD PTR 12[rsp], 4
	.loc 1 9 3 is_stmt 1 view .LVU6
.LVL1:
	.loc 1 10 3 view .LVU7
	.loc 1 10 6 is_stmt 0 view .LVU8
	mov	eax, DWORD PTR 12[rsp]
	add	eax, 1
	mov	DWORD PTR 12[rsp], eax
	.loc 1 11 3 is_stmt 1 view .LVU9
	xor	eax, eax
	call	printf@PLT
.LVL2:
	.loc 1 12 3 view .LVU10
	mov	esi, DWORD PTR 12[rsp]
	lea	rdi, .LC0[rip]
	xor	eax, eax
	call	printf@PLT
.LVL3:
	.loc 1 13 3 view .LVU11
	.loc 1 14 1 is_stmt 0 view .LVU12
	xor	eax, eax
	add	rsp, 24
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.text
.Letext0:
	.file 2 "/usr/lib/gcc/x86_64-pc-linux-gnu/8.1.1/include/stddef.h"
	.file 3 "/usr/include/bits/types.h"
	.file 4 "/usr/include/bits/libio.h"
	.file 5 "/usr/include/stdio.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x385
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF52
	.byte	0x1
	.long	.LASF53
	.long	.LASF54
	.long	.Ldebug_ranges0+0
	.quad	0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF7
	.byte	0x2
	.byte	0xd8
	.byte	0x17
	.long	0x35
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF0
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF2
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF4
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.long	.LASF5
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x5
	.long	0x5f
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF6
	.uleb128 0x2
	.long	.LASF8
	.byte	0x3
	.byte	0x8c
	.byte	0x19
	.long	0x6b
	.uleb128 0x2
	.long	.LASF9
	.byte	0x3
	.byte	0x8d
	.byte	0x1b
	.long	0x6b
	.uleb128 0x6
	.byte	0x8
	.uleb128 0x7
	.byte	0x8
	.long	0x92
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF10
	.uleb128 0x8
	.long	.LASF40
	.byte	0xd8
	.byte	0x4
	.byte	0xf5
	.byte	0x8
	.long	0x237
	.uleb128 0x9
	.long	.LASF11
	.byte	0x4
	.byte	0xf6
	.byte	0x7
	.long	0x5f
	.byte	0
	.uleb128 0x9
	.long	.LASF12
	.byte	0x4
	.byte	0xfb
	.byte	0x9
	.long	0x8c
	.byte	0x8
	.uleb128 0x9
	.long	.LASF13
	.byte	0x4
	.byte	0xfc
	.byte	0x9
	.long	0x8c
	.byte	0x10
	.uleb128 0x9
	.long	.LASF14
	.byte	0x4
	.byte	0xfd
	.byte	0x9
	.long	0x8c
	.byte	0x18
	.uleb128 0x9
	.long	.LASF15
	.byte	0x4
	.byte	0xfe
	.byte	0x9
	.long	0x8c
	.byte	0x20
	.uleb128 0x9
	.long	.LASF16
	.byte	0x4
	.byte	0xff
	.byte	0x9
	.long	0x8c
	.byte	0x28
	.uleb128 0xa
	.long	.LASF17
	.byte	0x4
	.value	0x100
	.byte	0x9
	.long	0x8c
	.byte	0x30
	.uleb128 0xa
	.long	.LASF18
	.byte	0x4
	.value	0x101
	.byte	0x9
	.long	0x8c
	.byte	0x38
	.uleb128 0xa
	.long	.LASF19
	.byte	0x4
	.value	0x102
	.byte	0x9
	.long	0x8c
	.byte	0x40
	.uleb128 0xa
	.long	.LASF20
	.byte	0x4
	.value	0x104
	.byte	0x9
	.long	0x8c
	.byte	0x48
	.uleb128 0xa
	.long	.LASF21
	.byte	0x4
	.value	0x105
	.byte	0x9
	.long	0x8c
	.byte	0x50
	.uleb128 0xa
	.long	.LASF22
	.byte	0x4
	.value	0x106
	.byte	0x9
	.long	0x8c
	.byte	0x58
	.uleb128 0xa
	.long	.LASF23
	.byte	0x4
	.value	0x108
	.byte	0x16
	.long	0x274
	.byte	0x60
	.uleb128 0xa
	.long	.LASF24
	.byte	0x4
	.value	0x10a
	.byte	0x14
	.long	0x27a
	.byte	0x68
	.uleb128 0xa
	.long	.LASF25
	.byte	0x4
	.value	0x10c
	.byte	0x7
	.long	0x5f
	.byte	0x70
	.uleb128 0xa
	.long	.LASF26
	.byte	0x4
	.value	0x110
	.byte	0x7
	.long	0x5f
	.byte	0x74
	.uleb128 0xa
	.long	.LASF27
	.byte	0x4
	.value	0x112
	.byte	0xd
	.long	0x72
	.byte	0x78
	.uleb128 0xa
	.long	.LASF28
	.byte	0x4
	.value	0x116
	.byte	0x12
	.long	0x43
	.byte	0x80
	.uleb128 0xa
	.long	.LASF29
	.byte	0x4
	.value	0x117
	.byte	0xf
	.long	0x51
	.byte	0x82
	.uleb128 0xa
	.long	.LASF30
	.byte	0x4
	.value	0x118
	.byte	0x8
	.long	0x280
	.byte	0x83
	.uleb128 0xa
	.long	.LASF31
	.byte	0x4
	.value	0x11c
	.byte	0xf
	.long	0x290
	.byte	0x88
	.uleb128 0xa
	.long	.LASF32
	.byte	0x4
	.value	0x125
	.byte	0xf
	.long	0x7e
	.byte	0x90
	.uleb128 0xa
	.long	.LASF33
	.byte	0x4
	.value	0x12d
	.byte	0x9
	.long	0x8a
	.byte	0x98
	.uleb128 0xa
	.long	.LASF34
	.byte	0x4
	.value	0x12e
	.byte	0x9
	.long	0x8a
	.byte	0xa0
	.uleb128 0xa
	.long	.LASF35
	.byte	0x4
	.value	0x12f
	.byte	0x9
	.long	0x8a
	.byte	0xa8
	.uleb128 0xa
	.long	.LASF36
	.byte	0x4
	.value	0x130
	.byte	0x9
	.long	0x8a
	.byte	0xb0
	.uleb128 0xa
	.long	.LASF37
	.byte	0x4
	.value	0x132
	.byte	0xa
	.long	0x29
	.byte	0xb8
	.uleb128 0xa
	.long	.LASF38
	.byte	0x4
	.value	0x133
	.byte	0x7
	.long	0x5f
	.byte	0xc0
	.uleb128 0xa
	.long	.LASF39
	.byte	0x4
	.value	0x135
	.byte	0x8
	.long	0x296
	.byte	0xc4
	.byte	0
	.uleb128 0xb
	.long	.LASF55
	.byte	0x4
	.byte	0x9a
	.byte	0xe
	.uleb128 0x8
	.long	.LASF41
	.byte	0x18
	.byte	0x4
	.byte	0xa0
	.byte	0x8
	.long	0x274
	.uleb128 0x9
	.long	.LASF42
	.byte	0x4
	.byte	0xa1
	.byte	0x16
	.long	0x274
	.byte	0
	.uleb128 0x9
	.long	.LASF43
	.byte	0x4
	.byte	0xa2
	.byte	0x14
	.long	0x27a
	.byte	0x8
	.uleb128 0x9
	.long	.LASF44
	.byte	0x4
	.byte	0xa6
	.byte	0x7
	.long	0x5f
	.byte	0x10
	.byte	0
	.uleb128 0x7
	.byte	0x8
	.long	0x23f
	.uleb128 0x7
	.byte	0x8
	.long	0x99
	.uleb128 0xc
	.long	0x92
	.long	0x290
	.uleb128 0xd
	.long	0x35
	.byte	0
	.byte	0
	.uleb128 0x7
	.byte	0x8
	.long	0x237
	.uleb128 0xc
	.long	0x92
	.long	0x2a6
	.uleb128 0xd
	.long	0x35
	.byte	0x13
	.byte	0
	.uleb128 0xe
	.long	.LASF56
	.uleb128 0xf
	.long	.LASF45
	.byte	0x4
	.value	0x13f
	.byte	0x1d
	.long	0x2a6
	.uleb128 0xf
	.long	.LASF46
	.byte	0x4
	.value	0x140
	.byte	0x1d
	.long	0x2a6
	.uleb128 0xf
	.long	.LASF47
	.byte	0x4
	.value	0x141
	.byte	0x1d
	.long	0x2a6
	.uleb128 0x10
	.long	.LASF48
	.byte	0x5
	.byte	0x87
	.byte	0x19
	.long	0x27a
	.uleb128 0x10
	.long	.LASF49
	.byte	0x5
	.byte	0x88
	.byte	0x19
	.long	0x27a
	.uleb128 0x10
	.long	.LASF50
	.byte	0x5
	.byte	0x89
	.byte	0x19
	.long	0x27a
	.uleb128 0x11
	.long	.LASF57
	.byte	0x1
	.byte	0x6
	.byte	0x5
	.long	0x5f
	.quad	.LFB3
	.quad	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.long	0x37b
	.uleb128 0x12
	.long	.LASF51
	.byte	0x1
	.byte	0x7
	.byte	0x7
	.long	0x5f
	.long	.LLST0
	.long	.LVUS0
	.uleb128 0x13
	.string	"vol"
	.byte	0x1
	.byte	0x8
	.byte	0x10
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x14
	.quad	.LVL2
	.long	0x37b
	.long	0x35f
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x9
	.byte	0x3
	.quad	.LC0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.uleb128 0x16
	.quad	.LVL3
	.long	0x37b
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x9
	.byte	0x3
	.quad	.LC0
	.byte	0
	.byte	0
	.uleb128 0x17
	.long	.LASF58
	.long	.LASF58
	.byte	0x5
	.value	0x13e
	.byte	0xc
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x13
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.uleb128 0x2137
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x2111
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LVUS0:
	.uleb128 .LVU2
	.uleb128 .LVU7
	.uleb128 .LVU7
	.uleb128 0
.LLST0:
	.quad	.LVL0
	.quad	.LVL1
	.value	0x2
	.byte	0x30
	.byte	0x9f
	.quad	.LVL1
	.quad	.LFE3
	.value	0x2
	.byte	0x31
	.byte	0x9f
	.quad	0
	.quad	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.LFB3
	.quad	.LFE3-.LFB3
	.quad	0
	.quad	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.quad	.LFB3
	.quad	.LFE3
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF19:
	.string	"_IO_buf_end"
.LASF27:
	.string	"_old_offset"
.LASF22:
	.string	"_IO_save_end"
.LASF5:
	.string	"short int"
.LASF7:
	.string	"size_t"
.LASF32:
	.string	"_offset"
.LASF52:
	.string	"GNU C89 8.1.1 20180531 -masm=intel -mtune=generic -march=x86-64 -g -O2 -ansi"
.LASF54:
	.string	"/home/dpitic/prg/asm/llp/ch14"
.LASF16:
	.string	"_IO_write_ptr"
.LASF11:
	.string	"_flags"
.LASF18:
	.string	"_IO_buf_base"
.LASF23:
	.string	"_markers"
.LASF13:
	.string	"_IO_read_end"
.LASF50:
	.string	"stderr"
.LASF31:
	.string	"_lock"
.LASF6:
	.string	"long int"
.LASF58:
	.string	"printf"
.LASF28:
	.string	"_cur_column"
.LASF47:
	.string	"_IO_2_1_stderr_"
.LASF56:
	.string	"_IO_FILE_plus"
.LASF44:
	.string	"_pos"
.LASF43:
	.string	"_sbuf"
.LASF40:
	.string	"_IO_FILE"
.LASF1:
	.string	"unsigned char"
.LASF51:
	.string	"ordinary"
.LASF4:
	.string	"signed char"
.LASF45:
	.string	"_IO_2_1_stdin_"
.LASF3:
	.string	"unsigned int"
.LASF41:
	.string	"_IO_marker"
.LASF30:
	.string	"_shortbuf"
.LASF15:
	.string	"_IO_write_base"
.LASF39:
	.string	"_unused2"
.LASF12:
	.string	"_IO_read_ptr"
.LASF2:
	.string	"short unsigned int"
.LASF10:
	.string	"char"
.LASF57:
	.string	"main"
.LASF42:
	.string	"_next"
.LASF33:
	.string	"__pad1"
.LASF34:
	.string	"__pad2"
.LASF35:
	.string	"__pad3"
.LASF36:
	.string	"__pad4"
.LASF37:
	.string	"__pad5"
.LASF0:
	.string	"long unsigned int"
.LASF17:
	.string	"_IO_write_end"
.LASF9:
	.string	"__off64_t"
.LASF8:
	.string	"__off_t"
.LASF24:
	.string	"_chain"
.LASF21:
	.string	"_IO_backup_base"
.LASF48:
	.string	"stdin"
.LASF26:
	.string	"_flags2"
.LASF38:
	.string	"_mode"
.LASF14:
	.string	"_IO_read_base"
.LASF53:
	.string	"volatile_ex.c"
.LASF29:
	.string	"_vtable_offset"
.LASF20:
	.string	"_IO_save_base"
.LASF25:
	.string	"_fileno"
.LASF49:
	.string	"stdout"
.LASF46:
	.string	"_IO_2_1_stdout_"
.LASF55:
	.string	"_IO_lock_t"
	.ident	"GCC: (GNU) 8.1.1 20180531"
	.section	.note.GNU-stack,"",@progbits
