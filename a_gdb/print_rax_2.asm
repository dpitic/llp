section .data

codes:
  db '0123456789ABCDEF'

section .text
global _start

_start:
  mov rax, 0x1122334455667788

  mov rdi, 1                    ; stdout file descriptor
  mov rdx, 1                    ; number of bytes to write()
  mov rcx, 64                   ; amount used in shifting rax
.loop:
  push rax
  sub rcx, 4
  sar rax, cl                   ; calculate offset: shit to 60, 56, 52, ... 4, 0
  and rax, 0xf                  ; clear all but lowest 4 bits

  lea rsi, [codes + rax]        ; address of character in 'codes'

  mov rax, 1                    ; write() syscall identifier
  push rcx                      ; preserve rcx before syscall
  syscall
  pop rcx

  pop rax
  test rcx, rcx                 ; rcx == 0 when all digits have been printed
  jnz .loop

  mov rax, 60                   ; exit() syscall identifier
  xor rdi, rdi                  ; argument: 0
  syscall
